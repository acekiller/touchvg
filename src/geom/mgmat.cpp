// mgmat.cpp: ʵ�ֶ�ά��α任������Matrix2d
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#include "mgmat.h"

_GEOM_BEGIN

// ����Ϊ��λ����
Matrix2d::Matrix2d()
{
    m11 = 1.0; m12 = 0.0; m21 = 0.0;
    m22 = 1.0; dx = 0.0; dy = 0.0;
}

// �������캯��
Matrix2d::Matrix2d(const MATRIX2D& src)
{
    m11 = src.m11; m12 = src.m12;
    m21 = src.m21; m22 = src.m22;
    dx  = src.dx;  dy  = src.dy;
}

// ����Ԫ�ع���
Matrix2d::Matrix2d(double _m11, double _m12, double _m21, double _m22, 
                   double _dx, double _dy)
{
    m11 = _m11; m12 = _m12;
    m21 = _m21; m22 = _m22;
    dx  = _dx;  dy  = _dy;
}

// ������������ʸ����ԭ�㹹��
Matrix2d::Matrix2d(const Vector2d& e0, const Vector2d& e1, const Point2d& origin)
{
    setCoordSystem(e0, e1, origin);
}

// ����任, ʸ�� * ����
Vector2d Vector2d::operator*(const Matrix2d& m) const
{
    return Vector2d(x * m.m11 + y * m.m21, x * m.m12 + y * m.m22);
}

// ����任, ʸ�� *= ����
Vector2d& Vector2d::operator*=(const Matrix2d& m)
{
    return set(x * m.m11 + y * m.m21, x * m.m12 + y * m.m22);
}

// ����任, �� * ����
Point2d Point2d::operator*(const Matrix2d& m) const
{
    return Point2d(x * m.m11 + y * m.m21 + m.dx, 
        x * m.m12 + y * m.m22 + m.dy);
}

// ����任, �� *= ����
Point2d& Point2d::operator*=(const Matrix2d& m)
{
    return set(x * m.m11 + y * m.m21 + m.dx, 
        x * m.m12 + y * m.m22 + m.dy);
}

// �Զ������о���任
void Matrix2d::TransformPoints(Int32 count, Point2d* points) const
{
    for (Int32 i = 0; i < count; i++)
        points[i] *= (*this);
}

// �Զ��ʸ�����о���任
void Matrix2d::TransformVectors(Int32 count, Vector2d* vectors) const
{
    for (Int32 i = 0; i < count; i++)
        vectors[i] *= (*this);
}

// ����˷�
Matrix2d Matrix2d::operator*(const Matrix2d& mat) const
{
    Matrix2d result;
    result.setToProduct(*this, mat);
    return result;
}

// ����˷�
Matrix2d& Matrix2d::operator*=(const Matrix2d& mat)
{
    return setToProduct(*this, mat);
}

// ���һ������leftSide * (*this)
Matrix2d& Matrix2d::preMultBy(const Matrix2d& leftSide)
{
    return setToProduct(leftSide, *this);
}

// �ҳ�һ������(*this) * rightSide
Matrix2d& Matrix2d::postMultBy(const Matrix2d& rightSide)
{
    return setToProduct(*this, rightSide);
}

// ����Ϊ��������ĳ˻�
Matrix2d& Matrix2d::setToProduct(const Matrix2d& m1, const Matrix2d& m2)
{
    return set(m1.m11 * m2.m11 + m1.m12 * m2.m21,
        m1.m11 * m2.m12 + m1.m12 * m2.m22,
        m1.m21 * m2.m11 + m1.m22 * m2.m21,
        m1.m21 * m2.m12 + m1.m22 * m2.m22,
        m1.dx  * m2.m11 + m1.dy  * m2.m21 + m2.dx,
        m1.dx  * m2.m12 + m1.dy  * m2.m22 + m2.dy);
}

// ����ʽֵ
double Matrix2d::det() const
{
    return m11 * m22 - m12 * m21;
}

// ����Ϊ�����
bool Matrix2d::invert()
{
    double d = m11 * m22 - m12 * m21;
    if (mgIsZero(d))
    {
        setToIdentity();
        return false;
    }
    
    d = 1.0 / d;
    set(m22 * d, -m12 * d, 
        -m21 * d, m11 * d,
        (m21 * dy - m22 * dx) * d, 
        (m12 * dx - m11 * dy) * d);
    return true;
}

// ���������
Matrix2d Matrix2d::inverse() const
{
    Matrix2d mat (*this);
    mat.invert();
    return mat;
}

// �жϾ����Ƿ����
bool Matrix2d::isInvertible() const
{
    return fabs(m11 * m22 - m12 * m21) > _MGZERO;
}

// ������С
double Matrix2d::scale() const
{
    double sx = scaleX();
    double sy = scaleY();
    return fabs(sx - sy) < _MGZERO ? sx : mgHypot(sx, sy);
}

// X������С
double Matrix2d::scaleX() const
{
    return mgIsZero(m12) ? fabs(m11) : mgHypot(m11, m12);
}

// Y������С
double Matrix2d::scaleY() const
{
    return mgIsZero(m21) ? fabs(m22) : mgHypot(m21, m22);
}

// �ж����������Ƿ����
bool Matrix2d::operator==(const Matrix2d& mat) const
{
    return isEqualTo(mat);
}

// �ж����������Ƿ����
bool Matrix2d::operator!=(const Matrix2d& mat) const
{
    return !isEqualTo(mat);
}

// ��ŷ�������ж����������Ƿ���ȣ����жϾ������ʸ���Ƿ����
bool Matrix2d::isEqualTo(const Matrix2d& mat, const Tol& tol) const
{
    return mgHypot(m11 - mat.m11, m12 - mat.m12) <= tol.equalVector()
        && mgHypot(m21 - mat.m21, m22 - mat.m22) <= tol.equalVector()
        && mgHypot(dx - mat.dx, dy - mat.dy) <= tol.equalVector();
}

// �ж��Ƿ�Ϊ��λ����
bool Matrix2d::isIdentity() const
{
    return mgIsZero(m11 - 1.0) && mgIsZero(m12)
        && mgIsZero(m22 - 1.0) && mgIsZero(m21)
        && mgIsZero(dx) && mgIsZero(dy);
}

// �жϾ����������ʸ���Ƿ�ֱ�ˮƽ�ʹ�ֱ
bool Matrix2d::isOrtho() const
{
    return mgIsZero(m12) && mgIsZero(m21);
}

// �õ���������ת������ɷ�
bool Matrix2d::isConformal(double& scaleX, double& scaleY, double& angle, 
                           bool& isMirror, Vector2d& reflex) const
{
    Vector2d e0 (m11, m12);
    Vector2d e1 (m21, m22);
    if (!e0.isPerpendicularTo(e1))
        return false;
    
    scaleX = e0.length();
    scaleY = e1.length();
    e0 /= scaleX;
    e1 /= scaleY;
    
    if (mgIsZero(e0.x - e1.y) && mgIsZero(e0.y + e1.x))
    {
        isMirror = false;
        angle = e0.angle();
    }
    else
    {
        isMirror = true;
        angle = e0.angle() / 2.0;
        reflex.x = cos(angle);
        reflex.y = sin(angle);
        angle = 0.0;
    }
    
    return true;
}

// ����Ϊԭ��origin��������ʸ��Ϊe0��e1������ϵ
Matrix2d& Matrix2d::setCoordSystem(const Vector2d& e0, const Vector2d& e1, 
                                   const Point2d& origin)
{
    m11 = e0.x;      m12 = e0.y;
    m21 = e1.x;      m22 = e1.y;
    dx  = origin.x;  dy  = origin.y;
    return *this;
}

// �õ�����ϵ��ԭ��origin��������ʸ��e0��e1
void Matrix2d::getCoordSystem(Vector2d& e0, Vector2d& e1, Point2d& origin) const
{
    e0.set(m11, m12);
    e1.set(m21, m22);
    origin.set(dx, dy);
}

// ����ԭ��Ϊorigin��������ʸ��Ϊe0��e1������ϵ
Matrix2d Matrix2d::coordSystem(const Vector2d& e0, const Vector2d& e1, 
                               const Point2d& origin)
{
    return Matrix2d(e0, e1, origin);
}

// ���ظ���ԭ�㡢��������ת�Ƕȵ�����ϵ
Matrix2d Matrix2d::coordSystem(const Point2d& origin, double scaleX, 
                               double scaleY, double angle)
{
    if (mgIsZero(scaleY)) scaleY = scaleX;
    double s = sin(angle);
    double c = cos(angle);
    return Matrix2d(c*scaleX, s*scaleX, -s*scaleY, c*scaleY, origin.x, origin.y);
}

// ���õ�λ����
Matrix2d& Matrix2d::setToIdentity()
{
    return set(1, 0, 0, 1, 0, 0);
}

// ���þ���Ԫ��
Matrix2d& Matrix2d::set(double _m11, double _m12, double _m21, double _m22,
                        double _dx, double _dy)
{
    m11 = _m11; m12 = _m12;
    m21 = _m21; m22 = _m22;
    dx  = _dx;  dy  = _dy;
    return *this;
}

// ����Ϊƽ�Ʊ任����
Matrix2d& Matrix2d::setToTranslation(const Vector2d& vec)
{
    return set(1.0, 0.0, 0.0, 1.0, vec.x, vec.y);
}

// ����Ϊ��һ��Ϊ���ĵ���ת�任����
Matrix2d& Matrix2d::setToRotation(double angle, 
                                  const Point2d& center)
{
    double c = cos(angle);
    double s = sin(angle);
    return set(c, s, -s, c, (1 - c) * center.x + s * center.y, 
        (1 - c) * center.y - s * center.x);
}

// ����Ϊ��һ��Ϊ���ĵķ����任����
Matrix2d& Matrix2d::setToScaling(double scale, 
                                 const Point2d& center)
{
    return setToScaling(scale, scale, center);
}

// ����Ϊ��һ��Ϊ���ĵķ����任����
Matrix2d& Matrix2d::setToScaling(double scaleX, double scaleY, 
                                 const Point2d& center)
{
    if (mgIsZero(scaleY)) scaleY = scaleX;
    return set(scaleX, 0, 0, scaleY,
        (1 - scaleX) * center.x, (1 - scaleY) * center.y);
}

// ����Ϊ����һ��ԳƵı任����
Matrix2d& Matrix2d::setToMirroring(const Point2d& pnt)
{
    return set(-1.0, 0.0, 0.0, -1.0, 2.0 * pnt.x, 2.0 * pnt.y);
}

// ����Ϊ��ֱ��{pnt,dir}Ϊ�����ߵĶԳƱ任����
Matrix2d& Matrix2d::setToMirroring(const Point2d& pnt, const Vector2d& dir)
{
    double d2 = dir.lengthSqrd();
    if (mgIsZero(d2))
        setToIdentity();
    else
    {
        double s2 = 2.0 * dir.x * dir.y / d2;
        double c2 = (dir.x * dir.x - dir.y * dir.y) / d2;
        set(c2, s2, s2, -c2, (1 - c2) * pnt.x - s2 * pnt.y, 
            (1 + c2) * pnt.y - s2 * pnt.x);
    }
    return *this;
}

// ����Ϊ���б任����
Matrix2d& Matrix2d::setToShearing(double sx, double sy, const Point2d& pnt)
{
    if (mgIsZero(sy)) sy = sx;
    return set(1.0, sx, sy, 1.0, -sy * pnt.y, -sx * pnt.x);
}

// �õ�ƽ�Ʊ任����
Matrix2d Matrix2d::translation(const Vector2d& vec)
{
    Matrix2d mat;
    mat.setToTranslation(vec);
    return mat;
}

// �õ���һ��Ϊ���ĵ���ת�任����
Matrix2d Matrix2d::rotation(double angle, const Point2d& center)
{
    Matrix2d mat;
    mat.setToRotation(angle, center);
    return mat;
}

// �õ���һ��Ϊ���ĵķ����任����
Matrix2d Matrix2d::scaling(double scale, const Point2d& center)
{
    Matrix2d mat;
    mat.setToScaling(scale, scale, center);
    return mat;
}

// �õ���һ��Ϊ���ĵķ����任����
Matrix2d Matrix2d::scaling(double scaleX, double scaleY, const Point2d& center)
{
    Matrix2d mat;
    mat.setToScaling(scaleX, scaleY, center);
    return mat;
}

// �õ�����һ��ԳƵı任����
Matrix2d Matrix2d::mirroring(const Point2d& pnt)
{
    Matrix2d mat;
    mat.setToMirroring(pnt);
    return mat;
}

// �õ���ֱ��{pnt,dir}Ϊ�����ߵĶԳƱ任����
Matrix2d Matrix2d::mirroring(const Point2d& pnt, const Vector2d& dir)
{
    Matrix2d mat;
    mat.setToMirroring(pnt, dir);
    return mat;
}

// �õ����б任����
Matrix2d Matrix2d::shearing(double sx, double sy, const Point2d& pnt)
{
    Matrix2d mat;
    mat.setToShearing(sx, sy, pnt);
    return mat;
}

_GEOM_END