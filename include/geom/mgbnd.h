//! \file mgbnd.h
//! \brief ����󶨿��� BoundBox
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_BOUNDBOX_H_
#define __GEOMETRY_BOUNDBOX_H_

#include "mgpnt.h"

_GEOM_BEGIN

//! �󶨿��࣬ƽ���ı���
/*!
    \ingroup _GEOM_CLASS_
*/
class BoundBox
{
public:
    //! ����������ԭ��İ󶨿�
    BoundBox()
        : m_base(Point2d::kOrigin())
        , m_dir1(Vector2d::kIdentity()), m_dir2(Vector2d::kIdentity())
    {
    }
    
    //! �����������߶εİ󶨿�
    BoundBox(const Point2d& pnt1, const Point2d& pnt2)
        : m_base(pnt1), m_dir1(pnt2 - pnt1), m_dir2(Vector2d::kIdentity())
    {
    }
    
    //! ����һ������������߹���ƽ���ı���
    BoundBox(const Point2d& base,
        const Vector2d& dir1, const Vector2d& dir2)
        : m_base(base), m_dir1(dir1), m_dir2(dir2)
    {
    }
    
    //! �������캯��
    BoundBox(const BoundBox& box)
        : m_base(box.m_base), m_dir1(box.m_dir1), m_dir2(box.m_dir2)
    {
    }
    
    //! �õ��󶨿����귶Χ�������Խǵ�����
    void getMinMaxPoints(Point2d& pnt1, Point2d& pnt2) const
    {
        pnt1.x = mgMin(m_base.x, mgMin(m_base.x + m_dir1.x, m_base.x + m_dir2.x));
        pnt1.y = mgMin(m_base.y, mgMin(m_base.y + m_dir1.y, m_base.y + m_dir2.y));
        pnt2.x = mgMax(m_base.x, mgMax(m_base.x + m_dir1.x, m_base.x + m_dir2.x));
        pnt2.y = mgMax(m_base.y, mgMax(m_base.y + m_dir1.y, m_base.y + m_dir2.y));
    }
    
    //! �õ��󶨿��һ�������������
    void get(Point2d& base, Vector2d& dir1, Vector2d& dir2) const
    {
        base = m_base;
        dir1 = m_dir1;
        dir2 = m_dir2;
    }
    
    //! ����Ϊ�������߶εİ󶨿�
    BoundBox& set(const Point2d& pnt1, const Point2d& pnt2)
    {
        m_base = pnt1;
        m_dir1 = pnt2 - pnt1;
        m_dir2 = Vector2d::kIdentity();
        return *this;
    }
    
    //! ����һ������������ߣ�����Ϊƽ���ı���
    BoundBox& set(const Point2d& base, 
        const Vector2d& dir1, const Vector2d& dir2)
    {
        m_base = base;
        m_dir1 = dir1;
        m_dir2 = dir2;
        return *this;
    }
    
    //! ���󵽰���һ����
    BoundBox& extend(const Point2d& pnt);
    
    //! ���������������
    BoundBox& swell(double distance);
    
    //! �ж��Ƿ����һ����
    bool contains(const Point2d& pnt) const;
    
    //! �ж��Ƿ����һ���󶨿���룬�����ཻ
    bool isDisjoint(const BoundBox& box) const;
    
    //! �ж��Ƿ�Ϊ�������
    bool isRect() const
    {
        return mgIsZero(m_dir1.y) && mgIsZero(m_dir2.x);
    }
    
    //! ��ƽ���ı�������Ϊ�������
    BoundBox& setToRect()
    {
        Point2d pt1, pt2;
        getMinMaxPoints(pt1, pt2);
        m_base = pt1;
        m_dir1.set(pt2.x - pt1.x, 0.0);
        m_dir2.set(0.0, pt2.y - pt1.y);
        return *this;
    }
    
private:
    Point2d     m_base;
    Vector2d    m_dir1;
    Vector2d    m_dir2;
};

_GEOM_END
#endif // __GEOMETRY_BOUNDBOX_H_