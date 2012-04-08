//! \file mgpnt.h
//! \brief 定义二维点类 Point2d
// Copyright (c) 2004-2012, Zhang Yungui
// License: LGPL, https://github.com/rhcad/touchdraw

#ifndef __GEOMETRY_POINT_H_
#define __GEOMETRY_POINT_H_

#include "mgvec.h"

//! 二维点类
/*!
    本类用于描述二维平面上任意位置的点，具有x和y两个坐标分量
    \ingroup GEOM_CLASS
*/
class Point2d : public POINT2D
{
public:
    //! 原点(0,0)
    static const Point2d& kOrigin()
    {
        static const Point2d pnt (0.0, 0.0);
        return pnt;
    }
    
    //! 构造为原点
    Point2d()
    {
        x = y = 0.0;
    }
    
    //! 构造为点(x, y)
    Point2d(double xx, double yy)
    {
        x = xx; y = yy;
    }
    
    //! 拷贝构造函数
    Point2d(const POINT2D& src)
    {
        x = src.x; y = src.y;
    }

    //! 矩阵变换, 点 * 矩阵
    Point2d operator*(const Matrix2d& m) const;

    //! 矩阵变换, 点 *= 矩阵
    Point2d& operator*=(const Matrix2d& m);
    
    //! 矩阵变换, 矩阵 * 点
    friend Point2d operator*(const Matrix2d& m, const Point2d& pnt)
    {
        return pnt * m;
    }
    
    //! 数 * 点
    friend Point2d operator*(double s, const Point2d& pnt)
    {
        return Point2d(pnt.x * s, pnt.y * s);
    }
    
    //! 点 * 数
    Point2d operator*(double s) const
    {
        return Point2d(x * s, y * s);
    }
    
    //! 点 *= 数
    Point2d& operator*=(double s)
    {
        x *= s; y *= s; return *this;
    }
    
    //! 点 / 数
    Point2d operator/(double s) const
    {
        s = 1.0 / s;
        return Point2d(x * s, y * s);
    }
    
    //! 点 /= 数
    Point2d& operator/=(double s)
    {
        s = 1.0 / s;
        x *= s; y *= s; return *this;
    }

    //! 比例放缩
    Point2d& scaleBy(double sx, double sy)
    {
        x *= sx; y *= sy; return *this;
    }
    
    //! 点累加
    Point2d operator+(const Point2d& pnt) const
    {
        return Point2d(x + pnt.x, y + pnt.y);
    }
    
    //! 点累加
    Point2d& operator+=(const Point2d& pnt)
    {
        x += pnt.x; y += pnt.y; return *this;
    }

    //! 用矢量平移, 矢量 + 点 = 点
    friend Point2d operator+(const Vector2d& vec, const Point2d& pnt)
    {
        return Point2d(pnt.x + vec.x, pnt.y + vec.y);
    }
    
    //! 用矢量平移, 点 + 矢量 = 点
    Point2d operator+(const Vector2d& vec) const
    {
        return Point2d(x + vec.x, y + vec.y);
    }
    
    //! 用矢量平移, 点 += 矢量
    Point2d& operator+=(const Vector2d& vec)
    {
        x += vec.x; y += vec.y; return *this;
    }
    
    //! 用矢量平移, 点 - 矢量 = 点
    Point2d operator-(const Vector2d& vec) const
    {
        return Point2d(x - vec.x, y - vec.y); 
    }
    
    //! 用矢量平移, 点 -= 矢量
    Point2d& operator-=(const Vector2d& vec)
    {
        x -= vec.x; y -= vec.y; return *this;
    }
    
    //! 平移
    void offset(double dx, double dy)
    {
        x += dx; y += dy;
    }
    
    //! 得到两点之间的矢量, 点 - 点 = 矢量
    Vector2d operator-(const Point2d& pnt) const
    {
        return Vector2d(x - pnt.x, y - pnt.y);
    }
    
    //! 返回负矢量
    Vector2d operator-() const
    {
        return Vector2d(-x, -y);
    }
    
    //! 转换为矢量
    Vector2d asVector() const
    {
        return Vector2d(x, y);
    }

    //! 到原点的距离
    double length() const
    {
        return mgHypot(x, y);
    }
    
    //! 两点距离
    double distanceTo(const Point2d& pnt) const
    {
        return mgHypot(x - pnt.x, y - pnt.y);
    }
    
    //! 判断两个点是否相等
    bool operator==(const Point2d& pnt) const
    {
        return isEqualTo(pnt);
    }
    
    //! 判断两个点是否不相等
    bool operator!=(const Point2d& pnt) const
    {
        return !isEqualTo(pnt);
    }
    
    //! 用欧拉规则判断两个点是否相等
    /*! 如果两个点的距离小于长度容差，则相等
        \param pnt 比较的另一个点
        \param tol 判断的容差，用到其长度容差
        \return 如果相等，则返回true，否则返回false
    */
    bool isEqualTo(const Point2d& pnt, const Tol& tol = Tol::gTol()) const
    {
        return mgHypot(x - pnt.x, y - pnt.y) <= tol.equalPoint();
    }
    
    //! 设置为点(xx, yy)
    Point2d& set(double xx, double yy)
    {
        x = xx; y = yy; return *this;
    }
    
    //! 得到四舍五入后的坐标
    /*! 利用该函数可以将矢量转换为POINT、CPoint值
        \param[out] xx 四舍五入后的X坐标分量
        \param[out] yy 四舍五入后的Y坐标分量
    */
    void get(long& xx, long& yy) const
    {
        xx = mgRound(x); yy = mgRound(y);
    }
    
    //! 极坐标法计算坐标
    /*! 
        \param angle 极角，弧度
        \param dist 极径长度
        \return 计算出的坐标
    */
    Point2d polarPoint(double angle, double dist) const
    {
        return Point2d(x + dist * cos(angle), y + dist * sin(angle));
    }
    
    //! 移动直尺法
    /*! 相对于起始点(本点)和方向点，在垂直沿线方向(→↑)偏移指定距离计算坐标
        \param dir 方向点，本点→方向点
        \param yoff 垂直沿线方向偏移，方向点↑偏移
        \return 计算出的坐标
    */
    Point2d rulerPoint(const Point2d& dir, double yoff) const;

    //! 移动直尺法
    /*! 相对于起始点(本点)和方向点，在沿线方向和垂直沿线方向分别偏移计算坐标
        \param dir 方向点，本点→方向点
        \param xoff 在沿线方向(→)偏移
        \param yoff 垂直沿线方向(↑)偏移
        \return 计算出的坐标
    */
    Point2d rulerPoint(const Point2d& dir, double xoff, double yoff) const;
};

#endif // __GEOMETRY_POINT_H_
