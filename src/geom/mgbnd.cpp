// mgbnd.cpp: ʵ�ְ󶨿���BoundBox
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#include "mgbnd.h"

_GEOM_BEGIN

// ���󵽰���һ����
BoundBox& BoundBox::extend(const Point2d& pnt)
{
    Vector2d vec = pnt - m_base;
    
    // ����󶨿�Ϊ�㣬�������߶�
    if (m_dir1.isZeroVector() && m_dir2.isZeroVector())
        m_dir1 = vec;
    // ����õ�Ͱ󶨿�ԭ���غ�
    else if (vec.isZeroVector())
        return *this;
    // ����󶨿�����ƽ�л�һ��Ϊ��
    else if (m_dir1.isParallelTo(m_dir2))
    {
        // m_dir1ȡΪ�ǿձ�
        if (m_dir1.isZeroVector())
        {
            Vector2d v = m_dir1;
            m_dir1 = m_dir2;
            m_dir2 = v;
        }
        
        // ����������m_dir1�ϵ�ͶӰ
        double proj1 = 1.0;
        double proj2 = m_dir2.projectScaleToVector(m_dir1);
        if (proj2 > 0.0)
        {
            if (proj2 > proj1)
                proj1 = proj2;
            proj2 = 0.0;
        }
        
        // ��vec��m_dir1�ϵ�ͶӰ
        Vector2d vecProj, vecPerp;
        double projv = vec.projectResolveVector(m_dir1, vecProj, vecPerp);
        
        // ������������m_dir1�ϵ�ͶӰ�԰���ָ����
        if (projv > proj1)
            proj1 = projv;
        else if (projv < proj2)
            proj2 = projv;
        
        // ����������
        m_dir2 = m_dir1 * proj2 + vecPerp;
        if (proj1 > 1.0)
            m_dir1 *= proj1;
    }
    else
    {
        double x, y;
        vec.resolveVector(m_dir1, m_dir2, x, y);
        if (x > 1.0)
            m_dir1 *= x;
        if (y > 1.0)
            m_dir2 *= y;
        if (x < 0.0)
        {
            m_base += m_dir1 * x;
            m_dir1 *= (1.0 - x);
        }
        if (y < 0.0)
        {
            m_base += m_dir2 * y;
            m_dir2 *= (1.0 - y);
        }
    }
    return *this;
}

// ���������������
BoundBox& BoundBox::swell(double distance)
{
    if (m_dir1.isZeroVector() && m_dir2.isZeroVector())
    {
        distance = fabs(distance);
        m_base.x -= distance;
        m_base.y -= distance;
        m_dir1.set(2.0 * distance, 0.0);
        m_dir2.set(0.0, 2.0 * distance);
    }
    else if (m_dir1.isParallelTo(m_dir2))
    {
        // m_dir1ȡΪ�ǿձ�
        if (m_dir1.isZeroVector())
        {
            Vector2d v = m_dir1;
            m_dir1 = m_dir2;
            m_dir2 = v;
        }
        distance = fabs(distance) / m_dir1.length();
        
        // ����������m_dir1�ϵ�ͶӰ
        double proj1 = 1.0;
        double proj2 = m_dir2.projectScaleToVector(m_dir1);
        if (proj2 > 0.0)
        {
            if (proj2 > proj1)
                proj1 = proj2;
            proj2 = 0.0;
        }
        proj1 += distance;
        proj2 -= distance;
        
        m_base.x += proj2 * m_dir1.x + distance * m_dir1.y;
        m_base.y += proj2 * m_dir1.y - distance * m_dir1.x;
        m_dir2.x = -2.0 * distance * m_dir1.y;
        m_dir2.y =  2.0 * distance * m_dir1.x;
        m_dir1 *= proj1 - proj2;
    }
    else
    {
        double len1 = m_dir1.length();
        double len2 = m_dir2.length();
        if (len1 + distance < 0.0)
            distance = -len1;
        else if (len2 + distance < 0.0)
            distance = -len2;
        
        m_base -= m_dir1 * (distance / len1);
        m_base -= m_dir2 * (distance / len2);
        m_dir1 *= 1.0 + 2.0 * distance / len1;
        m_dir2 *= 1.0 + 2.0 * distance / len2;
    }
    return *this;
}

// �ж��Ƿ����һ����
bool BoundBox::contains(const Point2d& pnt) const
{
    double x, y;
    Vector2d vec (pnt - m_base);
    
    if (m_dir1.isZeroVector() && m_dir2.isZeroVector())
        return vec.isZeroVector();
    else if (m_dir1.isParallelTo(m_dir2))
    {
        x = vec.projectScaleToVector(m_dir1);
        if (x < -_MGZERO || x > 1.0 + _MGZERO)
            return false;
        y = vec.projectScaleToVector(m_dir2);
        return y > -_MGZERO && y < 1.0 + _MGZERO;
    }
    else
    {
        vec.resolveVector(m_dir1, m_dir2, x, y);
        return x > -_MGZERO && x < 1.0 + _MGZERO
            && y > -_MGZERO && y < 1.0 + _MGZERO;
    }
}

// �ж��Ƿ����һ���󶨿��ཻ
bool BoundBox::isDisjoint(const BoundBox& box) const
{
    if (box.m_dir1.isZeroVector() && box.m_dir2.isZeroVector())
        return !contains(box.m_base);
    else if (box.m_dir1.isParallelTo(box.m_dir2))
    {
        return !contains(box.m_base)
            && !contains(box.m_base + box.m_dir1)
            && !contains(box.m_base + box.m_dir2);
    }
    else if (m_dir1.isZeroVector() && m_dir2.isZeroVector())
        return !box.contains(m_base);
    else if (m_dir1.isParallelTo(m_dir2))
    {
        return !box.contains(m_base)
            && !box.contains(m_base + m_dir1)
            && !box.contains(m_base + m_dir2);
    }
    else
    {
        // TODO:
    }
    return false;
}

_GEOM_END