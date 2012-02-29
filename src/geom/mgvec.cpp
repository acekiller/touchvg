// mgvec.cpp: ʵ�ֶ�άʸ����Vector2d
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#include "mgpnt.h"

_GEOM_BEGIN

// �ƶ�ֱ�߷����Ա�����dir���������Ϊֱ�߱ߣ��ڴ�ֱ���߷���ƫ��yoff
Point2d Point2d::rulerPoint(const Point2d& dir, double yoff) const
{
    double len = distanceTo(dir);
    if (len < _MGZERO)
        return Point2d(x, y + yoff);
    else
    {
        yoff /= len;
        return Point2d(x - (dir.y - y) * yoff, y + (dir.x - x) * yoff);
    }
}

// �ƶ�ֱ�߷���dir����㣬�����߷���ƫ��xoff����ֱ���߷���ƫ��yoff
Point2d Point2d::rulerPoint(const Point2d& dir, double xoff, double yoff) const
{
    double len = distanceTo(dir);
    if (len < _MGZERO)
        return Point2d(x + xoff, y + yoff);
    else
    {
        double dcos = (dir.x - x) / len;
        double dsin = (dir.y - y) / len;
        return Point2d(x + xoff * dcos - yoff * dsin, 
            y + xoff * dsin + yoff * dcos);
    }
}

// �ж�����ʸ���Ƿ�ƽ��
bool Vector2d::isParallelTo(const Vector2d& vec, const Tol& tol) const
{
    double cosfz = dotProduct(vec);
    double sinfz = crossProduct(vec);
    return (fabs(sinfz) <= fabs(cosfz) * tol.equalVector());
}

// �ж�����ʸ���Ƿ�ƽ��
bool Vector2d::isParallelTo(const Vector2d& vec, 
                            const Tol& tol, bool& nonzero) const
{
    bool ret = false;
    nonzero = true;
    double cosfz = dotProduct(vec);
    double sinfz = crossProduct(vec);
    if (fabs(sinfz) <= fabs(cosfz) * tol.equalVector())
    {
        if (mgIsZero(cosfz))
            nonzero = false;
        ret = true;
    }
    return ret;
}

// �ж�����ʸ���Ƿ�ͬ��
bool Vector2d::isCodirectionalTo(const Vector2d& vec, const Tol& tol) const
{
    double cosfz = dotProduct(vec);
    if (cosfz < -_MGZERO)          // ͬ����cos(�н�)�ӽ�1.0
        return false;
    double sinfz = crossProduct(vec);
    return (fabs(sinfz) <= cosfz * tol.equalVector());
}

// �ж�����ʸ���Ƿ�ͬ��
bool Vector2d::isCodirectionalTo(const Vector2d& vec, 
                                 const Tol& tol, bool& nonzero) const
{
    bool ret = false;
    nonzero = true;
    double cosfz = dotProduct(vec);
    double sinfz = crossProduct(vec);
    if (fabs(sinfz) <= fabs(cosfz) * tol.equalVector())
    {
        if (fabs(cosfz) < _MGZERO)
        {
            nonzero = false;
            ret = true;
        }
        else
            ret = (cosfz >= -_MGZERO);
    }
    return ret;
}

// �ж�����ʸ���Ƿ���
bool Vector2d::isOppositeTo(const Vector2d& vec, const Tol& tol) const
{
    double cosfz = dotProduct(vec);
    if (cosfz > -_MGZERO)          // ������cos(�н�)�ӽ�-1.0
        return false;
    double sinfz = crossProduct(vec);
    return (fabs(sinfz) <= (-cosfz) * tol.equalVector());
}

// �ж�����ʸ���Ƿ���
bool Vector2d::isOppositeTo(const Vector2d& vec, 
                            const Tol& tol, bool& nonzero) const
{
    bool ret = false;
    nonzero = true;
    double cosfz = dotProduct(vec);
    double sinfz = crossProduct(vec);
    if (fabs(sinfz) <= fabs(cosfz) * tol.equalVector())
    {
        if (fabs(cosfz) < _MGZERO)
        {
            nonzero = false;
            ret = false;
        }
        else
            ret = cosfz < -_MGZERO;
    }
    return ret;
}

// �ж�����ʸ���Ƿ�ֱ
bool Vector2d::isPerpendicularTo(const Vector2d& vec, const Tol& tol) const
{
    double sinfz = fabs(crossProduct(vec));
    if (sinfz < _MGZERO)
        return false;
    double cosfz = fabs(dotProduct(vec));
    return (cosfz <= sinfz * tol.equalVector());
}

// �ж�����ʸ���Ƿ�ֱ
bool Vector2d::isPerpendicularTo(const Vector2d& vec, 
                                 const Tol& tol, bool& nonzero) const
{
    bool ret = false;
    nonzero = true;
    double sinfz = fabs(crossProduct(vec));
    double cosfz = fabs(dotProduct(vec));
    if (cosfz <= sinfz * tol.equalVector())
    {
        ret = (sinfz >= _MGZERO);
        nonzero = ret;
    }
    return ret;
}

// ��ʸ��ͶӰ��ʸ��xAxis�ϵĴ�ֱ����
// ��xAxis����ʱ�뷽��ʱ������ֵ��˳ʱ���򷵻ظ�ֵ
double Vector2d::distanceToVector(const Vector2d& xAxis) const
{
    double len = xAxis.length();
    if (len < _MGZERO)
        return length();
    return xAxis.crossProduct(*this) / len;
}

// ��ʸ����ʸ��xAxis�ϵ�ͶӰ����, ͶӰʸ�� = xAxis * ͶӰ����
double Vector2d::projectScaleToVector(const Vector2d& xAxis) const
{
    double d2 = xAxis.lengthSqrd();
    if (d2 < _MGZERO)
        return 0.0;
    return dotProduct(xAxis) / d2;
}

// ��ʸ����ʸ��xAxis�ϵ�ͶӰʸ���ʹ�ֱʸ��
double Vector2d::projectResolveVector(const Vector2d& xAxis, 
                                      Vector2d& proj, Vector2d& perp) const
{
    double s = projectScaleToVector(xAxis);
    proj = xAxis * s;
    perp = *this - proj;
    return s;
}

// ����ʸ�������������ߵķ���ʸ���Ͻ���ʸ���ֽ�, vec = u*uAxis+v*vAxis
bool Vector2d::resolveVector(const Vector2d& uAxis, const Vector2d& vAxis, 
                             double& u, double& v) const
{
    double denom = uAxis.crossProduct(vAxis);
    if (mgIsZero(denom))
    {
        u = 0.0; v = 0.0;
        return false;
    }
    u = crossProduct(vAxis) / denom;
    v = uAxis.crossProduct(*this) / denom;
    return true;
}

_GEOM_END