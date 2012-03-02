//! \file mgpnt.h
//! \brief �����ά���� Point2d
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_POINT_H_
#define __GEOMETRY_POINT_H_

#include "mgvec.h"

_GEOM_BEGIN

//! ��ά����
/*!
    ��������������άƽ��������λ�õĵ㣬����x��y�����������
    \ingroup _GEOM_CLASS_
*/
class Point2d : public POINT2D
{
public:
    //! ԭ��(0,0)
    static const Point2d& kOrigin()
    {
        static const Point2d pnt (0.0, 0.0);
        return pnt;
    }
    
    //! ����Ϊԭ��
    Point2d()
    {
        x = y = 0.0;
    }
    
    //! ����Ϊ��(x, y)
    Point2d(double xx, double yy)
    {
        x = xx; y = yy;
    }
    
    //! �������캯��
    Point2d(const POINT2D& src)
    {
        x = src.x; y = src.y;
    }

    //! ����任, �� * ����
    Point2d operator*(const Matrix2d& m) const;

    //! ����任, �� *= ����
    Point2d& operator*=(const Matrix2d& m);
    
    //! ����任, ���� * ��
    friend Point2d operator*(const Matrix2d& m, const Point2d& pnt)
    {
        return pnt * m;
    }
    
    //! �� * ��
    friend Point2d operator*(double s, const Point2d& pnt)
    {
        return Point2d(pnt.x * s, pnt.y * s);
    }
    
    //! �� * ��
    Point2d operator*(double s) const
    {
        return Point2d(x * s, y * s);
    }
    
    //! �� *= ��
    Point2d& operator*=(double s)
    {
        x *= s; y *= s; return *this;
    }
    
    //! �� / ��
    Point2d operator/(double s) const
    {
        s = 1.0 / s;
        return Point2d(x * s, y * s);
    }
    
    //! �� /= ��
    Point2d& operator/=(double s)
    {
        s = 1.0 / s;
        x *= s; y *= s; return *this;
    }

    //! ��������
    Point2d& scaleBy(double sx, double sy)
    {
        x *= sx; y *= sy; return *this;
    }
    
    //! ���ۼ�
    Point2d operator+(const Point2d& pnt) const
    {
        return Point2d(x + pnt.x, y + pnt.y);
    }
    
    //! ���ۼ�
    Point2d& operator+=(const Point2d& pnt)
    {
        x += pnt.x; y += pnt.y; return *this;
    }

    //! ��ʸ��ƽ��, ʸ�� + �� = ��
    friend Point2d operator+(const Vector2d& vec, const Point2d& pnt)
    {
        return Point2d(pnt.x + vec.x, pnt.y + vec.y);
    }
    
    //! ��ʸ��ƽ��, �� + ʸ�� = ��
    Point2d operator+(const Vector2d& vec) const
    {
        return Point2d(x + vec.x, y + vec.y);
    }
    
    //! ��ʸ��ƽ��, �� += ʸ��
    Point2d& operator+=(const Vector2d& vec)
    {
        x += vec.x; y += vec.y; return *this;
    }
    
    //! ��ʸ��ƽ��, �� - ʸ�� = ��
    Point2d operator-(const Vector2d& vec) const
    {
        return Point2d(x - vec.x, y - vec.y); 
    }
    
    //! ��ʸ��ƽ��, �� -= ʸ��
    Point2d& operator-=(const Vector2d& vec)
    {
        x -= vec.x; y -= vec.y; return *this;
    }
    
    //! ƽ��
    void offset(double dx, double dy)
    {
        x += dx; y += dy;
    }
    
    //! �õ�����֮���ʸ��, �� - �� = ʸ��
    Vector2d operator-(const Point2d& pnt) const
    {
        return Vector2d(x - pnt.x, y - pnt.y);
    }
    
    //! ���ظ�ʸ��
    Vector2d operator-() const
    {
        return Vector2d(-x, -y);
    }
    
    //! ת��Ϊʸ��
    Vector2d asVector() const
    {
        return Vector2d(x, y);
    }

    //! ��ԭ��ľ���
    double length() const
    {
        return mgHypot(x, y);
    }
    
    //! �������
    double distanceTo(const Point2d& pnt) const
    {
        return mgHypot(x - pnt.x, y - pnt.y);
    }
    
    //! �ж��������Ƿ����
    bool operator==(const Point2d& pnt) const
    {
        return isEqualTo(pnt);
    }
    
    //! �ж��������Ƿ����
    bool operator!=(const Point2d& pnt) const
    {
        return !isEqualTo(pnt);
    }
    
    //! ��ŷ�������ж��������Ƿ����
    /*! ���������ľ���С�ڳ����ݲ�����
        \param pnt �Ƚϵ���һ����
        \param tol �жϵ��ݲ�õ��䳤���ݲ�
        \return �����ȣ��򷵻�true�����򷵻�false
    */
    bool isEqualTo(const Point2d& pnt, const Tol& tol = Tol::gTol()) const
    {
        return mgHypot(x - pnt.x, y - pnt.y) <= tol.equalPoint();
    }
    
    //! ����Ϊ��(xx, yy)
    Point2d& set(double xx, double yy)
    {
        x = xx; y = yy; return *this;
    }
    
    //! �õ���������������
    /*! ���øú������Խ�ʸ��ת��ΪPOINT��CPointֵ
        \param[out] xx ����������X�������
        \param[out] yy ����������Y�������
    */
    void get(long& xx, long& yy) const
    {
        xx = mgRound(x); yy = mgRound(y);
    }
    
    //! �����귨��������
    /*! 
        \param angle ���ǣ�����
        \param dist ��������
        \return �����������
    */
    Point2d polarPoint(double angle, double dist) const
    {
        return Point2d(x + dist * cos(angle), y + dist * sin(angle));
    }
    
    //! �ƶ�ֱ�߷�
    /*! �������ʼ��(����)�ͷ���㣬�ڴ�ֱ���߷���ƫ��ָ�������������
        \param dir �����
        \param yoff ��ֱ���߷���ƫ��
        \return �����������
    */
    Point2d rulerPoint(const Point2d& dir, double yoff) const;

    //! �ƶ�ֱ�߷�
    /*! �������ʼ��(����)�ͷ���㣬�����߷���ʹ�ֱ���߷���ֱ�ƫ�Ƽ�������
        \param dir �����
        \param xoff �����߷���ƫ��
        \param yoff ��ֱ���߷���ƫ��
        \return �����������
    */
    Point2d rulerPoint(const Point2d& dir, double xoff, double yoff) const;
};

_GEOM_END
#endif // __GEOMETRY_POINT_H_