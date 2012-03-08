// mglnrel.cpp: ʵ��ֱ��λ�ù�ϵ����
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#include "mglnrel.h"

_GEOM_BEGIN

// �жϵ�pt�Ƿ�������ֱ��a->b����� (������)
GEOMAPI bool mgIsLeft(const Point2d& a, const Point2d& b, const Point2d& pt)
{
    return (b-a).crossProduct(pt-a) > 0.0;
}

// �жϵ�pt�Ƿ�������ֱ��a->b�����
GEOMAPI bool mgIsLeft2(
    const Point2d& a, const Point2d& b, const Point2d& pt, const Tol& tol)
{
    double dist = (b-a).distanceToVector(pt-a);
    return dist > tol.equalPoint();
}

// �жϵ�pt�Ƿ�������ֱ��a->b����߻����� (������)
GEOMAPI bool mgIsLeftOn(const Point2d& a, const Point2d& b, const Point2d& pt)
{
    return (b-a).crossProduct(pt-a) >= 0.0;
}

// �жϵ�pt�Ƿ�������ֱ��a->b����߻�����
GEOMAPI bool mgIsLeftOn2(
    const Point2d& a, const Point2d& b, const Point2d& pt, const Tol& tol)
{
    double dist = (b-a).distanceToVector(pt-a);
    return dist > -tol.equalPoint();
}

// �жϵ�pt�Ƿ���ֱ��a->b������
GEOMAPI bool mgIsColinear(const Point2d& a, const Point2d& b, const Point2d& pt)
{
    return mgIsZero((b-a).crossProduct(pt-a));
}

// �жϵ�pt�Ƿ���ֱ��a->b������
GEOMAPI bool mgIsColinear2(
    const Point2d& a, const Point2d& b, const Point2d& pt, const Tol& tol)
{
    double dist = (b-a).crossProduct(pt-a);
    return fabs(dist) < tol.equalPoint();
}

// �ж������߶�ab��cd�Ƿ��ཻ���߶��ڲ�
GEOMAPI bool mgIsIntersectProp(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d)
{
    // Eliminate improper cases
    if (mgIsColinear(a,b,c) || mgIsColinear(a,b,d) 
        || mgIsColinear(c,d,a) || mgIsColinear(c,d,b))
        return false;
    
    return (mgIsLeft(a,b,c) ^ mgIsLeft(a,b,d)) 
        && (mgIsLeft(c,d,a) ^ mgIsLeft(c,d,b));
}

// �жϵ�pt�Ƿ����߶�ab��(������)
GEOMAPI bool mgIsBetweenLine(const Point2d& a, const Point2d& b, const Point2d& pt)
{
    if (!mgIsColinear(a, b, pt))
        return false;
    
    // If ab not vertical, check betweenness on x; else on y.
    if (a.x != b.x) 
        return  (a.x <= pt.x && pt.x <= b.x) || (a.x >= pt.x && pt.x >= b.x);
    else
        return  (a.y <= pt.y && pt.y <= b.y) || (a.y >= pt.y && pt.y >= b.y);
}

// �жϵ�pt�Ƿ����߶�ab��
GEOMAPI bool mgIsBetweenLine2(
    const Point2d& a, const Point2d& b, const Point2d& pt, const Tol& tol)
{
    if (!mgIsColinear2(a, b, pt, tol))
        return false;
    
    // If ab not vertical, check betweenness on x; else on y.
    if (a.x != b.x) 
    {
        return ((a.x <= pt.x + tol.equalPoint()) 
            && (pt.x <= b.x + tol.equalPoint())) 
            || ((a.x >= pt.x - tol.equalPoint()) 
            && (pt.x >= b.x - tol.equalPoint()));
    }
    else
    {
        return ((a.y <= pt.y + tol.equalPoint()) 
            && (pt.y <= b.y + tol.equalPoint())) 
            || ((a.y >= pt.y - tol.equalPoint()) 
            && (pt.y >= b.y - tol.equalPoint()));
    }
}

// ��֪��pt��ֱ��ab��, �жϵ�pt�Ƿ����߶�ab��(������)
GEOMAPI bool mgIsBetweenLine3(
    const Point2d& a, const Point2d& b, const Point2d& pt, Point2d* ptNear)
{
    bool ret;
    if (a.x != b.x) 
    {
        ret = (a.x <= pt.x && pt.x <= b.x) || (a.x >= pt.x && pt.x >= b.x);
        if (ptNear != NULL)
            *ptNear = fabs(pt.x - a.x) < fabs(pt.x - b.x) ? a : b;
    }
    else
    {
        ret = (a.y <= pt.y && pt.y <= b.y) || (a.y >= pt.y && pt.y >= b.y);
        if (ptNear != NULL)
            *ptNear = fabs(pt.y - a.y) < fabs(pt.y - b.y) ? a : b;
    }
    return ret;
}

// �ж������߶�ab��cd�Ƿ��ཻ(�������߶α�������)
GEOMAPI bool mgIsIntersect(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d)
{
    if (mgIsIntersectProp(a, b, c, d))
        return true;
    else if (mgIsBetweenLine(a, b, c) || mgIsBetweenLine(a, b, d) 
        || mgIsBetweenLine(c, d, a) || mgIsBetweenLine(c, d, b))
        return true;
    else
        return false;
}

// �����pt������ֱ��ab�ľ���
GEOMAPI double mgPtToBeeline(const Point2d& a, const Point2d& b, const Point2d& pt)
{
    double dist = (b-a).crossProduct(pt-a);
    return dist;
}

// �����pt������ֱ��ab�ľ���
GEOMAPI double mgPtToBeeline2(
    const Point2d& a, const Point2d& b, const Point2d& pt, Point2d& ptPerp)
{
    // �����غ�
    if (a == b)
    {
        ptPerp = a;
        return a.distanceTo(pt);
    }
    // ��ֱ��
    else if (mgIsZero(a.x - b.x))
    {
        ptPerp.set(a.x, pt.y);
        return fabs(a.x - pt.x);
    }
    // ˮƽ��
    else if (mgIsZero(a.y - b.y))
    {
        ptPerp.set(pt.x, a.y);
        return fabs(a.y - pt.y);
    }
    else
    {
        double t1 = ( b.y - a.y ) / ( b.x - a.x );
        double t2 = -1.0 / t1;
        ptPerp.x = ( pt.y - a.y + a.x * t1 - pt.x * t2 ) / ( t1 - t2 );
        ptPerp.y = a.y + (ptPerp.x - a.x) * t1;
        return pt.distanceTo(ptPerp);
    }
}

// �����pt���߶�ab���������
GEOMAPI double mgPtToLine(
    const Point2d& a, const Point2d& b, const Point2d& pt, Point2d& ptNear)
{
    Point2d ptTemp;
    double dist = mgPtToBeeline2(a, b, pt, ptNear);
    if (!mgIsBetweenLine3(a, b, ptNear, &ptTemp))
    {
        ptNear = ptTemp;
        dist = pt.distanceTo(ptNear);
    }
    return dist;
}

// ������ֱ��(ax+by+c=0)�Ľ���
GEOMAPI bool mgCrossLineAbc(
    double a1, double b1, double c1, double a2, double b2, double c2,
    Point2d& ptCross, const Tol& tolVec)
{
    double sinnum, cosnum;
    
    sinnum = a1*b2 - a2*b1;
    if (mgIsZero(sinnum))
        return false;
    cosnum = a1*a2 + b1*b2;
    if (!mgIsZero(cosnum) && fabs(sinnum / cosnum) < tolVec.equalVector())
        return false;
    
    ptCross.x = (b1*c2 - b2*c1) / sinnum;
    ptCross.y = (a2*c1 - a1*c2) / sinnum;
    
    return true;
}

// ����������ֱ�ߵĽ���
GEOMAPI bool mgCross2Beeline(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d, 
    Point2d& ptCross, double* pu, double* pv, const Tol& tolVec)
{
    double u, v, denom, cosnum;
    
    denom = (c.x-d.x)*(b.y-a.y)-(c.y-d.y)*(b.x-a.x);
    if (mgIsZero(denom))            // ƽ�л��غ�
        return false;
    
    cosnum = (b.x-a.x)*(d.x - c.x) + (b.y-a.y)*(d.y-c.y);
    if (!mgIsZero(cosnum) && fabs(denom / cosnum) < tolVec.equalVector())
        return false;
    
    u = ((c.x-a.x)*(d.y-c.y)-(c.y-a.y)*(d.x-c.x)) / denom;
    v = ((c.x-a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x)) / denom;
    
    if (pu != NULL) *pu = u;
    if (pv != NULL) *pv = v;
    
    ptCross.x = (1 - u) * a.x + u * b.x;
    ptCross.y = (1 - u) * a.y + u * b.y;
    
    return true;
}

// �������߶εĽ���
// ����: (a.x,a.y),(b.x,b.y) ��һ���߶��ϵ�������
//         (c.x,c.y),(d.x,d.y) �ڶ����߶��ϵ�������
// ���: (px, py) ��������
// ����: ���޽���
GEOMAPI bool mgCross2Line(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d,
    Point2d& ptCross, const Tol& tolVec)
{
    double u, v, denom, cosnum;
    
    if (mgMin(a.x,b.x) - mgMax(c.x,d.x) > _MGZERO 
        || mgMin(c.x,d.x) - mgMax(a.x,b.x) > _MGZERO
        || mgMin(a.y,b.y) - mgMax(c.y,d.y) > _MGZERO 
        || mgMin(c.y,d.y) - mgMax(a.y,b.y) > _MGZERO)
        return false;
    
    denom = (c.x-d.x)*(b.y-a.y)-(c.y-d.y)*(b.x-a.x);
    if (mgIsZero(denom))
        return false;
    
    cosnum = (b.x-a.x)*(d.x - c.x) + (b.y-a.y)*(d.y-c.y);
    if (!mgIsZero(cosnum) && fabs(denom / cosnum) < tolVec.equalVector())
        return false;
    
    u = ((c.x-a.x)*(d.y-c.y)-(c.y-a.y)*(d.x-c.x)) / denom;
    if (u < _MGZERO || u > 1.0 - _MGZERO)
        return false;
    
    v = ((c.x-a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x)) / denom;
    if (v < _MGZERO || v > 1.0 - _MGZERO)
        return false;
    
    ptCross.x = (1 - u) * a.x + u * b.x;
    ptCross.y = (1 - u) * a.y + u * b.y;
    
    return true;
}

// ���߶κ�ֱ�ߵĽ���
GEOMAPI bool mgCrossLineBeeline(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d,
    Point2d& ptCross, double* pv, const Tol& tolVec)
{
    double u, denom, cosnum;
    
    denom = (c.x-d.x)*(b.y-a.y)-(c.y-d.y)*(b.x-a.x);
    if (mgIsZero(denom))
        return false;
    
    cosnum = (b.x-a.x)*(d.x - c.x) + (b.y-a.y)*(d.y-c.y);
    if (!mgIsZero(cosnum) && fabs(denom / cosnum) < tolVec.equalVector())
        return false;
    
    u = ((c.x-a.x)*(d.y-c.y)-(c.y-a.y)*(d.x-c.x)) / denom;
    if (u < _MGZERO || u > 1.0 - _MGZERO)
        return false;
    
    if (pv != NULL)
        *pv = ((c.x-a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x)) / denom;
    
    ptCross.x = (1 - u) * a.x + u * b.x;
    ptCross.y = (1 - u) * a.y + u * b.y;
    
    return true;
}

// �߶ζ˵���������:
// 1001  |  1000  |  1010
// 0001  |  0000  |  0010
// 0101  |  0100  |  0110
static inline unsigned ClipCode(Point2d& pt, const Box2d& box)
{
    unsigned code = 0;
    if (pt.y > box.ymax)
        code |= 0x1000;
    else if (pt.y < box.ymin)
        code |= 0x0100;
    if (pt.x < box.xmin)
        code |= 0x0001;
    else if (pt.x > box.xmax)
        code |= 0x0010;
    return code;
}

// ����: �þ��μ����߶�
// ����: [in, out] pt1 �߶��������
//       [in, out] pt2 �߶��յ�����
//       [in] box ���þ���
// ����: ���ú��Ƿ��д��ڼ��þ����ڵ��߶β���
GEOMAPI bool mgClipLine(Point2d& pt1, Point2d& pt2, const Box2d& _box)
{
    Box2d box (_box);
    box.normalize();
    
    unsigned code1, code2;
    code1 = ClipCode(pt1, box);
    code2 = ClipCode(pt2, box);
    
    for ( ; ; )
    {
        if (!(code1 | code2))       // ��ȫ�ھ�����
            return true;
        if (code1 & code2)          // ��ȫ�ھ�����
            return false;
        
        double x = 0.0, y = 0.0;
        unsigned code;
        
        if (code1)                  // ��㲻�ھ�����
            code = code1;
        else                        // �յ㲻�ھ�����
            code = code2;
        if (code & 0x1000)          // ��
        {
            x = pt1.x + (pt2.x - pt1.x) * (box.ymax - pt1.y) / (pt2.y - pt1.y);
            y = box.ymax;
        }
        else if (code & 0x0100)     // ��
        {
            x = pt1.x + (pt2.x - pt1.x) * (box.ymin - pt1.y) / (pt2.y - pt1.y);
            y = box.ymin;
        }
        else if (code & 0x0001)     // ��
        {
            y = pt1.y + (pt2.y - pt1.y) * (box.xmin - pt1.x) / (pt2.x - pt1.x);
            x = box.xmin;
        }
        else if (code & 0x0010)     // ��
        {
            y = pt1.y + (pt2.y - pt1.y) * (box.xmax - pt1.x) / (pt2.x - pt1.x);
            x = box.xmax;
        }
        
        if (code == code1)
        {
            pt1.x = x;
            pt1.y = y;
            code1 = ClipCode(pt1, box);
        }
        else
        {
            pt2.x = x;
            pt2.y = y;
            code2 = ClipCode(pt2, box);
        }
    }
}

static bool PtInArea_Edge(int &odd, const Point2d& pt, const Point2d& p1, 
                          const Point2d& p2, const Point2d& p0)
{
    // �����X������P���ڱ�[P1,P2)�ϣ���û�н���. ��ֱ��Ҳû��
    if (!((p2.x > p1.x) && (pt.x >= p1.x) && (pt.x < p2.x)) &&
        !((p1.x > p2.x) && (pt.x <= p1.x) && (pt.x > p2.x)) )
    {
        return false;
    }
    
    // ���Y����������ϵ�P�����ߺ͸ñߵĽ���(pt.x, yy)
    double yy = p1.y + (pt.x - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
    if (pt.y > yy)      // �ཻ
    {
        if (mgIsZero(pt.x - p1.x))    // �����Ƕ���, ��Ƚ�P[i+1]��P[i-1]�Ƿ���pt.xͬ��
        {
            if (((p0.x > pt.x) && (p2.x > pt.x)) ||
                ((p0.x < pt.x) && (p2.x < pt.x)) )      // ͬ��
            {
                return false;
            }
        }
        odd = 1 - odd;      // ����һ������, ��ż�л�
    }
    
    return true;
}

// ����: �ж�һ���Ƿ���һ����η�Χ��
GEOMAPI int mgPtInArea(
    const Point2d& pt, Int32 count, const Point2d* vertexs, 
    Int32& order, const Tol& tol)
{
    Int32 i;
    int odd = 1;    // 1: ������Ϊż��, 0: ������Ϊ����
    
    for (i = 0; i < count; i++)
    {
        // P��ĳ�����غ�. ���� kPtAtVertex, order = ����� [0, count-1]
        if (pt.isEqualTo(vertexs[i], tol))
        {
            order = i;
            return kPtAtVertex;
        }
    }
    
    for (i = 0; i < count; i++)
    {
        const Point2d& p1 = vertexs[i];
        const Point2d& p2 = (i+1 < count) ? vertexs[i+1] : vertexs[0];
        
        // P��ĳ������. ���� kPtOnEdge, order = �ߺ� [0, count-1]
        if (mgIsBetweenLine2(p1, p2, pt, tol))
        {
            order = i;
            return kPtOnEdge;
        }

        if (!PtInArea_Edge(odd, pt, p1, p2, 
            i > 0 ? vertexs[i-1] : vertexs[count-1]))
            continue;
    }

    // ������ߺͶ���εĽ�����Ϊż��, �� p==1, P������, ���� kPtOutArea
    // Ϊ������p==0, P������, ���� kPtInArea
    return 0 == odd ? kPtInArea : kPtOutArea;
}

// �ж϶�����Ƿ�Ϊ͹�����
GEOMAPI bool mgIsConvex(Int32 count, const Point2d* vs, bool* pACW)
{
    if (count < 3 || vs == NULL)
        return true;
    bool z0 = (vs[count-1].x - vs[count-2].x) * (vs[1].y - vs[0].y)
            > (vs[count-1].y - vs[count-2].y) * (vs[1].x - vs[0].x);
    for (int i = 0; i < count; i++)
    {
        if (z0 != ((vs[i].x - vs[i-1].x) * (vs[i+1].y - vs[i].y)
                 > (vs[i].y - vs[i-1].y) * (vs[i+1].x - vs[i].x)))
            return false;
    }
    if (pACW != NULL)
        *pACW = z0;
    return true;
}

_GEOM_END