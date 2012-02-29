//! \file mgrect.h
//! \brief ������ο��� Box2d
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_RECT_H_
#define __GEOMETRY_RECT_H_

#include "mgmat.h"

_GEOM_BEGIN

//! ���ο���
/*!
    \ingroup _GEOM_CLASS_
    ��������������άƽ����ˮƽ���ο򣬻����귶Χ
*/
class Box2d : public BOX2D
{
public:
    //! ������ԭ��Ŀվ��ο�
    static const Box2d& kIdentity()
    {
        static const Box2d rect;
        return rect;
    }

    //! ����������ԭ��ľ��ο�
    Box2d()
    {
        xmin = ymin = xmax = ymax = 0.0;
    }

    //! �������캯����Ĭ�ϲ��Զ��淶��
    Box2d(const BOX2D& src, bool bNormalize = false);
    
    //! ���������Խǵ㹹�죬�Զ��淶��
    Box2d(const Point2d& pnt1, const Point2d& pnt2)
    {
        set(pnt1, pnt2);
    }
    
    //! �����Խǵ����깹�죬Ĭ�ϲ��Զ��淶��
    Box2d(double l, double t, double r, double b, bool bNormalize = false)
    {
        xmin = l; ymin = t; xmax = r; ymax = b;
        if (bNormalize)
            normalize();
    }

    //! �����Խǵ��������깹�죬Ĭ�ϲ��Զ��淶��
    Box2d(long l, long t, long r, long b, bool bNormalize = false)
    {
        xmin = (double)l; ymin = (double)t;
        xmax = (double)r; ymax = (double)b;
        if (bNormalize)
            normalize();
    }
    
    //! �����ĸ����㹹��
    Box2d(const Point2d& pnt1, const Point2d& pnt2,
        const Point2d& pnt3, const Point2d& pnt4)
    {
        set(pnt1, pnt2, pnt3, pnt4);
    }
    
    //! ����������㹹��
    Box2d(Int32 count, const Point2d* points)
    {
        set(count, points);
    }
    
    //! ������������Ϳ�߹���
    /*!
        \param center ���ε���������
        \param width ���ο�ȣ�Ϊ�������ǹ淶������
        \param height ���θ߶ȣ�Ϊ�������ǹ淶������
    */
    Box2d(const Point2d& center, double width, double height)
    {
        set(center, width, height);
    }
    
    //! �õ������Խǵ�
    void get(Point2d& p1, Point2d& p2) const
    {
        p1.set(xmin, ymin);
        p2.set(xmax, ymax);
    }
    
    //! �õ����������ľ���(RECT)�������¶Ե�
    /*! ���������Ϊ�淶�����Σ���ȡ����RECTҲ����Windows�淶������Ҫ��
        �� CRect::NormalizeRect() �Ľ����
        \param[out] l RECT.left����Ӧ��xmin
        \param[out] t RECT.top����Ӧ��ymin
        \param[out] r RECT.right����Ӧ��xmax
        \param[out] b RECT.bottom����Ӧ��ymax
    */
    void get(long& l, long& t, long& r, long& b) const
    {
        l = mgRound(xmin); t = mgRound(ymin);
        r = mgRound(xmax); b = mgRound(ymax);
    }

    //! ���ƾ��Σ�Ĭ�ϲ��Զ��淶��
    Box2d& set(const BOX2D& src, bool bNormalize = false);
    
    //! ���������Խǵ㣬�Զ��淶��
    Box2d& set(const Point2d& p1, const Point2d& p2);
    
    //! ���������Խǵ����꣬�Զ��淶��
    Box2d& set(double x1, double y1, double x2, double y2);
    
    //! ����Ϊ�ĸ�����İ��ݿ�
    Box2d& set(const Point2d& p1, const Point2d& p2, 
        const Point2d& p3, const Point2d& p4);
    
    //! ����Ϊ�������İ��ݿ�
    Box2d& set(Int32 count, const Point2d* points);
    
    //! ������������Ϳ��
    /*!
        \param center ���ε���������
        \param width ���ο�ȣ�Ϊ�������ǹ淶������
        \param height ���θ߶ȣ�Ϊ�������ǹ淶������
        \return �����ε�����
    */
    Box2d& set(const Point2d& center, double width, double height)
    {
        xmin = center.x - width * 0.5;
        ymin = center.y - height * 0.5;
        xmax = center.x + width * 0.5;
        ymax = center.y + height * 0.5;
        return *this;
    }
    
    //! ���ؿ�ȣ��Ǹ���
    double width() const
    {
        return fabs(xmax - xmin);
    }
    
    //! ���ظ߶ȣ��Ǹ���
    double height() const
    {
        return fabs(ymax - ymin);
    }
    
    //! ���ؾ��ο��С���Ǹ���
    Vector2d size() const
    {
        return Vector2d(fabs(xmax - xmin), fabs(ymax - ymin));
    }
    
    //! ������������
    Point2d center() const
    {
        return Point2d((xmin + xmax) * 0.5, (ymin + ymax) * 0.5);
    }
    
    //! ������������
    Point2d leftTop() const
    {
        return Point2d(xmin, ymax);
    }
    
    //! ������������
    Point2d rightTop() const
    {
        return Point2d(xmax, ymax);
    }
    
    //! ������������
    Point2d leftBottom() const
    {
        return Point2d(xmin, ymin);
    }
    
    //! ������������
    Point2d rightBottom() const
    {
        return Point2d(xmax, ymin);
    }
    
    //! �淶����ʹxmin<=xmax��ymin<=ymax
    Box2d& normalize()
    {
        if (xmin > xmax)
            mgSwap(xmin, xmax);
        if (ymin > ymax)
            mgSwap(ymin, ymax);
        return *this;
    }
    
    //! ������������
    Box2d& swapTopBottom()
    {
        mgSwap(ymin, ymax);
        return *this;
    }
    
    //! ����Ϊ�վ��ο�
    Box2d& empty()
    {
        xmin = ymin = xmax = ymax = 0.0;
        return *this;
    }
    
    //! �ж��Ƿ�淶��
    bool isNormalized() const
    {
        return xmin <= xmax && ymin <= ymax;
    }
    
    //! �жϿ�͸��Ƿ�Ϊ����λ��ԭ��
    bool isNull() const
    {
        return mgIsZero(xmin) && mgIsZero(ymin)
            && mgIsZero(xmax) && mgIsZero(ymax);
    }
    
    //! �жϿ��ߵľ���ֵ�Ƿ�Ϊ��
    bool isEmpty(const Tol& tol = Tol::gTol()) const
    {
        return fabs(xmax - xmin) < tol.equalPoint()
            || fabs(ymax - ymin) < tol.equalPoint();
    }
    
    //! �жϿ����Ƿ�ӽ���С����
    bool isEmptyMinus(const Tol& tol = Tol::gTol()) const
    {
        return (xmax - xmin) < tol.equalPoint()
            || (ymax - ymin) < tol.equalPoint();
    }
    
    //! �ж�һ�����Ƿ��ڱ����ο��ڣ������䣬���ο����淶��
    /*! �ж����ڱ����ο��ڻ�λ�ھ��ο���ϡ�\n�����ο����淶����
        \param pt �����Ĳ��Ե�
        \return ����ڱ����ο��ڻ��ı��ϣ��򷵻�true�����򷵻�false
    */
    bool isInside(const Point2d& pt) const
    {
        return pt.x >= xmin && pt.y >= ymin
            && pt.x <= xmax && pt.y <= ymax;
    }
    
    //! �ж�һ�����Ƿ��ڱ����ο��ڣ�������
    /*! �������ο��������󳤶��ݲ�ľ�������жϡ�\n�����ο����淶����
        \param pt �����Ĳ��Ե�
        \param tol �жϵ��ݲ�õ��䳤���ݲ�
        \return ����ڱ����ο��ڻ��ı��ϣ��򷵻�true�����򷵻�false
    */
    bool isInside(const Point2d& pt, const Tol& tol) const
    {
        return pt.x >= xmin - tol.equalPoint()
            && pt.y >= ymin - tol.equalPoint()
            && pt.x <= xmax + tol.equalPoint()
            && pt.y <= ymax + tol.equalPoint();
    }
    
    //! �ж�һ�����ο��Ƿ��ڱ����ο��ڣ�������
    /*! �ж����ڱ����ο��ڻ�ͱ����ο�ı����غϡ�\n
        ���������ο����淶����
        \param box ��һ�����ο�
        \return ����ڱ����ο��ڻ����غϣ��򷵻�true�����򷵻�false
    */
    bool isInside(const Box2d& box) const
    {
        return box.xmin >= xmin && box.ymin >= ymin
            && box.xmax <= xmax && box.ymax <= ymax;
    }
    
    //! �ж�һ�����ο��Ƿ��ڱ����ο��ڣ�������
    /*! �������ο��������󳤶��ݲ�ľ�������жϣ��в����غ�Ҳ����true��\n
        ���������ο����淶����
        \param box ��һ�����ο�
        \param tol �жϵ��ݲ�õ��䳤���ݲ�
        \return ����ڱ����ο��ڻ����غϣ��򷵻�true�����򷵻�false
    */
    bool isInside(const Box2d& box, const Tol& tol) const
    {
        return box.xmin >= xmin - tol.equalPoint()
            && box.ymin >= ymin - tol.equalPoint()
            && box.xmax <= xmax + tol.equalPoint()
            && box.ymax <= ymax + tol.equalPoint();
    }
    
    //! ���Ĳ��䣬������ο�
    /*!
        \param d ������ƫ�ƾ���
        \return �����������
    */
    Box2d& inflate(double d)
    {
        return inflate(d, d);
    }
    
    //! ���Ĳ��䣬������ο�
    /*!
        \param x ������X�����ƫ�ƾ���
        \param y ������Y�����ƫ�ƾ���
        \return �����������
    */
    Box2d& inflate(double x, double y)
    {
        xmin -= x; ymin -= y; xmax += x; ymax += y;
        return *this;
    }
    
    //! ���Ĳ��䣬������ο�
    /*!
        \param vec ������ƫ�ƣ�vec.xΪX�����ƫ�ƾ��룬vec.yΪY�����ƫ�ƾ���
        \return �����������
    */
    Box2d& inflate(const Vector2d& vec)
    {
        return inflate(vec.x, vec.y);
    }
    
    //! ���Ĳ��䣬������ο�
    /*!
        \param box ������ƫ�ƣ�
            box.xminΪ����ƫ�ƾ��룬box.yminΪ�ײ��ƫ�ƾ��룬
            box.xmaxΪ�Ҳ��ƫ�ƾ��룬box.ymaxΪ�ϲ��ƫ�ƾ���
        \return �����������
    */
    Box2d& inflate(const Box2d& box)
    {
        return inflate(box.xmin, box.ymin, box.xmax, box.ymax);
    }
    
    //! ���Ĳ��䣬������ο�
    /*!
        \param l ���ο�����ƫ�ƾ���
        \param b ���ο�ײ��ƫ�ƾ���
        \param r ���ο��Ҳ��ƫ�ƾ���
        \param t ���ο��ϲ��ƫ�ƾ���
        \return �����������
    */
    Box2d& inflate(double l, double b, double r, double t)
    {
        xmin -= l; ymin -= b; xmax += r; ymax += t;
        return *this;
    }
    
    //! ���Ĳ��䣬��С���ο�
    /*!
        \param d ���ڲ��ƫ�ƾ���
        \return �����������
    */
    Box2d& deflate(double d)
    {
        return deflate(d, d);
    }
    
    //! ���Ĳ��䣬��С���ο�
    /*!
        \param x ���ڲ��X�����ƫ�ƾ���
        \param y ���ڲ��Y�����ƫ�ƾ���
        \return �����������
    */
    Box2d& deflate(double x, double y)
    {
        xmin += x; ymin += y; xmax -= x; ymax -= y;
        return *this;
    }
    
    //! ���Ĳ��䣬��С���ο�
    /*!
        \param vec ���ڲ��ƫ�ƣ�vec.xΪX�����ƫ�ƾ��룬vec.yΪY�����ƫ�ƾ���
        \return �����������
    */
    Box2d& deflate(const Vector2d& vec)
    {
        return deflate(vec.x, vec.y);
    }
    
    //! ���Ĳ��䣬��С���ο�
    /*!
        \param box ���ڲ��ƫ�ƣ�
            box.xminΪ�Ҳ��ƫ�ƾ��룬box.yminΪ�ϲ��ƫ�ƾ��룬
            box.xmaxΪ����ƫ�ƾ��룬box.ymaxΪ�ײ��ƫ�ƾ���
        \return �����������
    */
    Box2d& deflate(const Box2d& box)
    {
        return deflate(box.xmin, box.ymin, box.xmax, box.ymax);
    }
    
    //! ���Ĳ��䣬��С���ο�
    /*!
        \param l ���ο��Ҳ��ƫ�ƾ���
        \param b ���ο��ϲ��ƫ�ƾ���
        \param r ���ο�����ƫ�ƾ���
        \param t ���ο�ײ��ƫ�ƾ���
        \return �����������
    */
    Box2d& deflate(double l, double b, double r, double t)
    {
        xmin += l; ymin += b; xmax -= r; ymax -= t;
        return *this;
    }
    
    //! ƽ��
    Box2d& offset(double x, double y)
    {
        xmin += x; ymin += y; xmax += x; ymax += y;
        return *this;
    }
    
    //! ƽ��
    Box2d& offset(const Vector2d& vec)
    {
        return offset(vec.x, vec.y);
    }
    
    //! ������������ԭ��Ϊ����
    /*!
        \param sx X�����������
        \param sy Y�������������Ϊ0��ȡΪsx
        \return �����ε�����
    */
    Box2d& scaleBy(double sx, double sy = 0.0)
    {
        if (mgIsZero(sy)) sy = sx;
        xmin *= sx; xmax *= sx;
        ymin *= sy; ymax *= sy;
        return *this;
    }
    
    //! �ж��Ƿ��һ�����ο��ཻ�����߶��ǹ淶�����Σ�
    /*! �������һ������Ϊ�վ��λ�ǹ淶�����Σ��򷵻�false��
        \param box ��һ�����ο򣬱���淶��
        \return �Ƿ��ཻ��ʧ��ʱ����false
    */
    bool isIntersect(const Box2d& box) const;
    
    //! ����Ϊ�������ο�Ľ��������߶��ǹ淶�����Σ�
    /*! ���ñ����ο�Ϊ�������������ο�Ľ�����
        �������һ��Ϊ�վ��Σ�������Ϊ�վ��Ρ�
        \param r1 ��һ�����ο򣬱���淶����������Ϊ�վ���
        \param r2 �ڶ������ο򣬱���淶����������Ϊ�վ���
    */
    Box2d& intersectWith(const Box2d& r1, const Box2d& r2);
    
    //! ����Ϊ��һ�����ο�Ľ��������߶��ǹ淶�����Σ�
    /*! ���ñ����ο�Ϊ�����ο����һ�����ο�Ľ�����
        �������һ��Ϊ�վ��Σ�������Ϊ�վ��Ρ�
        \param box ��һ�����ο򣬱���淶����������Ϊ�վ���
    */
    Box2d& intersectWith(const Box2d& box)
    {
        return intersectWith(*this, box);
    }
    
    //! ����Ϊ�������ο�Ĳ��������߶��ǹ淶�����Σ�
    /*! ���ñ����ο�Ϊ�������������ο�Ĳ�����\n
        �������һ��Ϊ�վ��Σ���ֱ������Ϊ��һ�����ο�
        \param r1 ��һ�����ο򣬱���淶����������Ϊ�վ���
        \param r2 �ڶ������ο򣬱���淶����������Ϊ�վ���
        \return �����ε����ã��������淶������
    */
    Box2d& unionWith(const Box2d& r1, const Box2d& r2);
    
    //! �ϲ�һ�����ο����߶��ǹ淶�����Σ�
    /*! ���ñ����ο�Ϊ�����ο����һ�����ο�Ĳ�����\n
        �������һ��Ϊ�վ��Σ���ֱ������Ϊ��һ�����ο�
        �ǹ淶�����ν���Ϊ�վ��Ρ�
        \param box ��һ�����ο򣬱���淶����������Ϊ�վ���
        \return �����ε����ã��������淶������
    */
    Box2d& unionWith(const Box2d& box)
    {
        return unionWith(*this, box);
    }
    
    //! �ϲ�һ����
    /*! �Ŵ󱾾��ο���ʹ�ø����ĵ�����ڱ����ο��ڣ���ʹ�Ŵ�����С
        \param x Ҫ�����ĵ��X����
        \param y Ҫ�����ĵ��Y����
        \return �����ε����ã��淶������
    */
    Box2d& unionWith(double x, double y)
    {
        if (xmin > x) xmin = x;
        if (ymin > y) ymin = y;
        if (xmax < x) xmax = x;
        if (ymax < y) ymax = y;
        return *this;
    }
    
    //! �ϲ�һ����
    /*! �Ŵ󱾾��ο���ʹ�ø����ĵ�����ڱ����ο��ڣ���ʹ�Ŵ�����С
        \param pt Ҫ�����ĵ�
        \return �����ε����ã��淶������
    */
    Box2d& unionWith(const Point2d& pt)
    {
        return unionWith(pt.x, pt.y);
    }
    
    //! ����ƽ�ƾ��ο�
    /*!
        \param box ָ���ĸ�����ƫ�����ľ��ο�
        \return �µľ��ο�
    */
    Box2d operator+(const Box2d& box) const
    {
        return Box2d(xmin + box.xmin, ymin + box.ymin, 
            xmax + box.xmax, ymax + box.ymax);
    }
    
    //! ����ƽ�ƾ��ο�
    /*!
        \param box ָ���ĸ�����ƫ�����ľ��ο�
        \return �����������
    */
    Box2d& operator+=(const Box2d& box)
    {
        return set(xmin + box.xmin, ymin + box.ymin, 
            xmax + box.xmax, ymax + box.ymax);
    }
    
    //! ����ƽ�ƾ��ο�
    /*!
        \param box ָ���ĸ�����ƫ�����ľ��ο�
        \return �µľ��ο�
    */
    Box2d operator-(const Box2d& box) const
    {
        return Box2d(xmin - box.xmin, ymin - box.ymin, 
            xmax - box.xmax, ymax - box.ymax);
    }
    
    //! ����ƽ�ƾ��ο�
    /*!
        \param box ָ���ĸ�����ƫ�����ľ��ο�
        \return �����������
    */
    Box2d& operator-=(const Box2d& box)
    {
        return set(xmin - box.xmin, ymin - box.ymin, 
            xmax - box.xmax, ymax - box.ymax);
    }
    
    //! ����ƽ�ƾ��ο�
    Box2d operator+(const Vector2d& vec) const
    {
        return Box2d(xmin + vec.x, ymin + vec.y, 
            xmax + vec.x, ymax + vec.y);
    }
    
    //! ����ƽ�ƾ��ο�
    Box2d& operator+=(const Vector2d& vec)
    {
        return set(xmin + vec.x, ymin + vec.y, 
            xmax + vec.x, ymax + vec.y);
    }
    
    //! ����ƽ�ƾ��ο�
    Box2d operator-(const Vector2d& vec) const
    {
        return Box2d(xmin - vec.x, ymin - vec.y, 
            xmax - vec.x, ymax - vec.y);
    }
    
    //! ����ƽ�ƾ��ο�
    Box2d& operator-=(const Vector2d& vec)
    {
        return set(xmin - vec.x, ymin - vec.y, 
            xmax - vec.x, ymax - vec.y);
    }
    
    //! ���ο򽻼��Ĳ���������
    Box2d operator&(const Box2d& box) const
    {
        return Box2d().intersectWith(*this, box);
    }
    
    //! ���ο򽻼��Ĳ���������
    Box2d& operator&=(const Box2d& box)
    {
        return intersectWith(box);
    }
    
    //! �ϲ����ο�Ĳ���������
    Box2d operator|(const Box2d& box) const
    {
        return Box2d().unionWith(*this, box);
    }
    
    //! �ϲ����ο�Ĳ���������
    Box2d& operator|=(const Box2d& box)
    {
        return unionWith(box);
    }
    
    //! �õ��������������һ��������¾��ο�
    Box2d operator*(double s) const
    {
        return Box2d(xmin * s, ymin * s, xmax * s, ymax * s);
    }
    
    //! �������������һ����
    Box2d& operator*=(double s)
    {
        return set(xmin * s, ymin * s, xmax * s, ymax * s);
    }
    
    //! �õ��������������һ��������¾��ο�
    Box2d operator/(double s) const
    {
        s = 1.0 / s;
        return Box2d(xmin * s, ymin * s, xmax * s, ymax * s);
    }
    
    //! �������������һ����
    Box2d& operator/=(double s)
    {
        s = 1.0 / s;
        return set(xmin * s, ymin * s, xmax * s, ymax * s);
    }
    
    //! ����任�����Ϊ�淶������
    Box2d operator*(const Matrix2d& m) const;
    
    //! ����任�����Ϊ�淶������
    Box2d& operator*=(const Matrix2d& m);
    
    //! �ж��������ο��Ƿ����
    bool operator==(const Box2d& box) const
    {
        return mgIsZero(xmin - box.xmin)
            && mgIsZero(ymin - box.ymin)
            && mgIsZero(xmax - box.xmax)
            && mgIsZero(ymax - box.ymax);
    }
    
    //! �ж��������ο��Ƿ����
    bool operator!=(const Box2d& box) const
    {
        return !operator==(box);
    }
    
    //! �ж��������ο��Ƿ����
    /*!
        \param box ��һ�����ο�
        \param tol �жϵ��ݲ�õ��䳤���ݲ�
        \return �����ȣ��򷵻�true�����򷵻�false
    */
    bool isEqualTo(const Box2d& box, const Tol& tol = Tol::gTol()) const
    {
        return mgHypot(xmin - box.xmin, ymin - box.ymin) <= tol.equalPoint()
            && mgHypot(xmax - box.xmax, ymax - box.ymax) <= tol.equalPoint();
    }
};

_GEOM_END
#endif // __GEOMETRY_RECT_H_