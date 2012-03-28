// mgdrawlines.cpp: 实现折线绘图命令类
// Copyright (c) 2004-2012, Zhang Yungui
// License: LGPL, https://github.com/rhcad/graph2d

#include "mgdrawlines.h"
#include <mgshapet.h>
#include <mgbasicsp.h>
#include <mgbase.h>

MgCmdDrawLines::MgCmdDrawLines()
{
}

MgCmdDrawLines::~MgCmdDrawLines()
{
}

bool MgCmdDrawLines::initialize(const MgMotion* sender)
{
    return _initialize(MgShapeT<MgLines>::create, sender);
}

bool MgCmdDrawLines::undo(bool &enableRecall, const MgMotion* sender)
{
    enableRecall = true;
    if (m_step > 1) {                   // 去掉倒数第二个点，倒数第一点是临时动态点
        ((MgBaseLines*)m_shape->shape())->removePoint(m_step - 1);
        m_shape->shape()->update();
    }
    return MgCommandDraw::_undo(sender);
}

bool MgCmdDrawLines::draw(const MgMotion* sender, GiGraphics* gs)
{
    if (m_step > 1) {
        GiContext ctxaux(0, GiColor(64, 64, 64, 128), kLineSolid, GiColor(0, 64, 64, 168));
        double radius = gs->xf().displayToModel(3);
        
        for (UInt32 i = 0; i < m_shape->shape()->getPointCount(); i++) {
            gs->drawEllipse(&ctxaux, m_shape->shape()->getPoint(i), radius);
        }
    }
    
    return MgCommandDraw::draw(sender, gs);
}

bool MgCmdDrawLines::touchBegan(const MgMotion* sender)
{
    ((MgBaseLines*)m_shape->shape())->resize(2);
    m_step = 1;
    m_shape->shape()->setPoint(0, sender->startPointM);
    m_shape->shape()->setPoint(1, sender->pointM);
    m_shape->shape()->update();

    return _touchBegan(sender);
}

bool MgCmdDrawLines::touchMoved(const MgMotion* sender)
{
    MgBaseLines* lines = (MgBaseLines*)m_shape->shape();
    bool closed = (m_step > 2 && sender->pointM.distanceTo(m_shape->shape()->getPoint(0))
                   < sender->view->xform()->displayToModel(20));
    
    if (m_step > 2 && m_shape->shape()->isClosed() != closed) {
        lines->setClosed(closed);
        if (closed)
            lines->removePoint(m_step);
        else
            lines->addPoint(sender->pointM);
    }
    if (!closed) {
        m_shape->shape()->setPoint(m_step, sender->pointM);
        if (m_step > 0 && canAddPoint(sender, false)) {
            m_step++;
            if (m_step >= m_shape->shape()->getPointCount()) {
                ((MgBaseLines*)m_shape->shape())->addPoint(sender->pointM);
            }
        }
    }
    m_shape->shape()->update();

    return _touchMoved(sender);
}

bool MgCmdDrawLines::touchEnded(const MgMotion* sender)
{
    MgBaseLines* lines = (MgBaseLines*)m_shape->shape();
    bool closed = (m_step > 2 && sender->pointM.distanceTo(m_shape->shape()->getPoint(0))
                   < sender->view->xform()->displayToModel(20));
    
    if (m_step > 2 && m_shape->shape()->isClosed() != closed) {
        lines->setClosed(closed);
        if (closed)
            lines->removePoint(m_step);
        else
            lines->addPoint(sender->pointM);
    }
    if (!closed) {
        m_shape->shape()->setPoint(m_step, sender->pointM);
        if (m_step > 0 && !canAddPoint(sender, true))
            lines->removePoint(m_step);
    }
    m_shape->shape()->update();
    
    if (m_step > 2) {
        _addshape(sender);
    }

    m_shape->shape()->clear();
    m_step = 0;

    return _touchEnded(sender);
}

bool MgCmdDrawLines::canAddPoint(const MgMotion* sender, bool ended)
{
    double minDist = sender->view->xform()->displayToModel(10);
    Point2d endPt  = m_shape->shape()->getPoint(m_step - 1);
    double distToEnd = endPt.distanceTo(sender->pointM);
    double turnAngle = 90;
    
    if (m_step > 1)
    {
        Point2d lastPt = m_shape->shape()->getPoint(m_step - 2);
        turnAngle = (endPt - lastPt).angleTo(sender->pointM - endPt);
        turnAngle = mgRad2Deg(fabs(turnAngle));
    }
    
    if (distToEnd < minDist * (ended ? 0.25 : 1))
        return false;
    if (!ended && sin(turnAngle) * distToEnd < 5)
        return false;
    
    return true;
}
