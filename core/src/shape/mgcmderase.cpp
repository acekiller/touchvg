// mgcmderase.cpp: 实现橡皮擦命令类
// Copyright (c) 2004-2012, Zhang Yungui
// License: LGPL, https://github.com/rhcad/touchvg

#include "mgcmderase.h"
#include <algorithm>
#include <functional>

float mgDisplayMmToModel(float mm, const MgMotion* sender);

MgCommandErase::MgCommandErase()
{
}

MgCommandErase::~MgCommandErase()
{
}

bool MgCommandErase::cancel(const MgMotion* sender)
{
    bool recall;
    m_boxsel = false;
    bool ret = undo(recall, sender);
    ret = undo(recall, sender) || ret;
    return undo(recall, sender) || ret;
}

bool MgCommandErase::initialize(const MgMotion* /*sender*/)
{
    m_boxsel = false;
    return true;
}

bool MgCommandErase::undo(bool &enableRecall, const MgMotion* sender)
{
    enableRecall = true;
    if (!m_deleted.empty()) {
        m_deleted.pop_back();
        sender->view->redraw(false);
        return true;
    }
    if (m_boxsel) {
        m_boxsel = false;
        return true;
    }
    return false;
}

bool MgCommandErase::draw(const MgMotion* sender, GiGraphics* gs)
{
    GiContext ctx(-4, GiColor(64, 64, 64, 128));
    
    if (m_boxsel) {
        GiContext ctxshap(0, GiColor(0, 0, 255, 128), 
                          isIntersectMode(sender) ? kLineDash : kLineSolid, GiColor(0, 0, 255, 32));
        bool antiAlias = gs->isAntiAliasMode();
        
        gs->setAntiAliasMode(false);
        gs->drawRect(&ctxshap, Box2d(sender->startPointM, sender->pointM));
        gs->setAntiAliasMode(antiAlias);
    }
    for (std::vector<MgShape*>::const_iterator it = m_deleted.begin();
         it != m_deleted.end(); ++it) {
        (*it)->draw(*gs, &ctx);
    }
    
    return true;
}

MgShape* MgCommandErase::hitTest(const MgMotion* sender)
{
    Box2d limits(sender->startPointM, mgDisplayMmToModel(6, sender), 0);
    Point2d nearpt;
    Int32 segment;
    
    return sender->view->shapes()->hitTest(limits, nearpt, segment);
}

bool MgCommandErase::click(const MgMotion* sender)
{
    MgShape* shape = hitTest(sender);
    if (shape) {
        MgShapesLock locker(sender->view->shapes());
        shape = sender->view->shapes()->removeShape(shape->getID());
        shape->release();
        sender->view->regen();
    }
    
    return true;
}

bool MgCommandErase::doubleClick(const MgMotion* /*sender*/)
{
    return false;
}

bool MgCommandErase::longPress(const MgMotion* /*sender*/)
{
    return false;
}

bool MgCommandErase::touchBegan(const MgMotion* sender)
{
    m_boxsel = true;
    sender->view->redraw(false);
    return true;
}

bool MgCommandErase::isIntersectMode(const MgMotion* sender)
{
    return (sender->startPoint.x < sender->point.x
            && sender->startPoint.y < sender->point.y);
}

bool MgCommandErase::touchMoved(const MgMotion* sender)
{
    Box2d snap(sender->startPointM, sender->pointM);
    void *it;
    MgShape* shape = m_boxsel ? sender->view->shapes()->getFirstShape(it) : NULL;
    
    m_deleted.clear();
    for (; shape; shape = sender->view->shapes()->getNextShape(it)) {
        if (isIntersectMode(sender) ? shape->shape()->hitTestBox(snap)
            : snap.contains(shape->shape()->getExtent())) {
            m_deleted.push_back(shape);
        }
    }
    sender->view->redraw(false);
    
    return true;
}

bool MgCommandErase::touchEnded(const MgMotion* sender)
{
    if (!m_deleted.empty()) {
        MgShapesLock locker(sender->view->shapes());
        
        for (std::vector<MgShape*>::iterator it = m_deleted.begin();
             it != m_deleted.end(); ++it) {
            MgShape* shape = *it;
            shape = sender->view->shapes()->removeShape(shape->getID());
            shape->release();
        }
        
        sender->view->regen();
        m_deleted.clear();
    }
    
    m_boxsel = false;
    sender->view->redraw(false);
    
    return true;
}
