// mgline.cpp: 实现线段图形类 MgLine
// Copyright (c) 2004-2012, Zhang Yungui
// License: LGPL, https://github.com/rhcad/graph2d

#include "mgbasicsp.h"
#include <_mgshape.h>
#include <mgnear.h>

MGSHAPE_IMPLEMENT(MgLine, MgShape)

MgLine::MgLine()
{
}

MgLine::~MgLine()
{
}

UInt32 MgLine::_getPointCount() const
{
    return 2;
}

Point2d MgLine::_getPoint(UInt32 index) const
{
    return _points[index ? 1 : 0];
}

void MgLine::_setPoint(UInt32 index, const Point2d& pt)
{
    _points[index ? 1 : 0] = pt;
}

bool MgLine::_isClosed() const
{
    return false;
}

void MgLine::_copy(const MgLine& src)
{
    _points[0] = src._points[0];
    _points[1] = src._points[1];
    __super::_copy(src);
}

bool MgLine::_equals(const MgLine& src) const
{
    return _points[0] == src._points[0]
        && _points[1] == src._points[1]
        && __super::_equals(src);
}

void MgLine::_update()
{
    _extent.set(_points[0], _points[1]);
    __super::_update();
}

void MgLine::_transform(const Matrix2d& mat)
{
    _points[0] *= mat;
    _points[1] *= mat;
    __super::_transform(mat);
}

void MgLine::_clear()
{
    _points[1] = _points[0];
    __super::_clear();
}

double MgLine::_hitTest(const Point2d& pt, double tol, 
                        Point2d& ptNear, Int32& segment) const
{
    return mgLinesHit(2, _points, false, pt, tol, ptNear, segment);
}

bool MgLine::_draw(GiGraphics& gs, const GiContext& ctx) const
{
    bool ret = gs.drawLine(&ctx, _points[0], _points[1]);
    return __super::_draw(gs, ctx) || ret;
}
