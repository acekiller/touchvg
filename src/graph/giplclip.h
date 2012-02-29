// giplclip.h: �������μ����� PolygonClip
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_POLYGONCLIP_H_
#define __GEOMETRY_POLYGONCLIP_H_

#include <vector>
using std::vector;

// ����STL����(vector)������Ԫ�ظ���
template<class T> inline static int getSize(T& arr)
{
    return static_cast<int>(arr.size());
}

_GEOM_BEGIN

//! ����μ�����
class PolygonClip
{
    const Box2d     m_rect;         //!< ���þ���
    vector<Point2d> m_vs1;          //!< ���ý��㻺��
    vector<Point2d> m_vs2;          //!< ���ý��㻺��
    bool            m_closed;       //!< �Ƿ�պ�
    
public:
    
    //! ���캯��
    /*!
        \param rect ���þ��Σ�����Ϊ�淶���ľ���
        \param closed ��Ҫ��������������Ƕ���λ�������
    */
    PolygonClip(const Box2d& rect, bool closed = true)
        : m_rect(rect), m_closed(closed)
    {
    }
    
    //! ����һ�������
    /*!
        \param count �������
        \param points ������������, ����Ϊcount
        \param mat ��ָ��Ҫ�Ը��������������任�ľ���
        \return ���ý�����Ƿ���������
    */
    bool clip(int count, const Point2d* points, const Matrix2d* mat = NULL)
    {
        if (count < 2 || points == NULL)
            return false;
        
        if (mat != NULL)
        {
            m_vs1.resize(2+count/2);
            m_vs2.resize(count);
            Point2d* p = &m_vs2.front();
            for (int i=0; i < count; i++)
                p[i] = points[i] * (*mat);
            points = p;
        }
        else
        {
            m_vs1.resize(2+count/2);
            m_vs2.resize(2+count/2);
        }
        if (!clipEdge(m_vs1, count, points, LEFT) ||
            !clipEdge(m_vs2, getSize(m_vs1), &m_vs1.front(), TOP) ||
            !clipEdge(m_vs1, getSize(m_vs2), &m_vs2.front(), RIGHT) ||
            !clipEdge(m_vs2, getSize(m_vs1), &m_vs1.front(), BOTTOM))
        {
            return false;
        }

        m_vs1.clear();

        return true;
    }
    
    //! ���ؼ��ý���еĶ������
    int getCount() const
    {
        return getSize(m_vs2);
    }
    
    //! ���ؼ��ý���еĶ�������
    const Point2d* getPoints() const
    {
        return &m_vs2.front();
    }
    
    //! ���ؼ��ý���е�ָ����ŵĶ�������
    /*!
        \param index ��������, >=0, �Զ�ȡ�����������Χ��
        \return ��Ӧ�Ķ�������
    */
    const Point2d& getPoint(int index) const
    {
        return m_vs2[index % m_vs2.size()];
    }
    
    //! �жϼ��ú������ڶ����Ƿ񹹳�������
    /*!
        \param index ���ú�ı�(�ɼ��򲻿ɼ���)�����, �Զ�ȡ��[0, getCount()-1]��Χ��, 
            Ϊ( getCount()-1 )ʱ�൱������β���������
        \return �ñ��Ƿ񹹳�������, ���ɼ���
    */
    bool isLinked(int index) const
    {
        const Point2d& p1 = getPoint(index);
        const Point2d& p2 = getPoint(index+1);
        
        // �ͼ��ñ��غ�
        if (mgIsZero(p1.x - p2.x) && (mgIsZero(p1.x - m_rect.xmin) || mgIsZero(p1.x - m_rect.xmax)))
            return false;
        if (mgIsZero(p1.y - p2.y) && (mgIsZero(p1.y - m_rect.ymin) || mgIsZero(p1.y - m_rect.ymax)))
            return false;

        return true;
    }
    
private:
    
    void operator=(const PolygonClip&);

    enum kSideType { LEFT, TOP, RIGHT, BOTTOM };
    
    bool clipEdge(vector<Point2d>& arr, int count, const Point2d* points, kSideType side)
    {
        if (count < 2 || points == NULL)
            return false;

        arr.clear();
        output(arr, points[m_closed ? count-1 : 0], points[0], side);

        for (int i=1; i < count; i++)
        {
            output(arr, points[i-1], points[i], side);
        }

        return (arr.size() >= 2);
    }
    
    void output(vector<Point2d>& arr, const Point2d& p1, const Point2d& p2, kSideType side)
    {
        switch (side)
        {
        case LEFT:      clipLeft(arr, p1, p2); break;
        case TOP:       clipTop(arr, p1, p2); break;
        case RIGHT:     clipRight(arr, p1, p2); break;
        case BOTTOM:    clipBottom(arr, p1, p2); break;
        }
    }
    
    void clipLeft(vector<Point2d>& arr, const Point2d& p1, const Point2d& p2)
    {
        double y;
        
        // ����߶���������ཻ�����������
        if ((p1.x < m_rect.xmin) != (p2.x < m_rect.xmin))
        {
            y = p1.y + (m_rect.xmin - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            arr.push_back(Point2d(m_rect.xmin, y));
        }
        
        // ����յ��ڿɼ��࣬������յ�
        if (p2.x >= m_rect.xmin)
        {
            arr.push_back(p2);
        }
    }
    
    void clipTop(vector<Point2d>& arr, const Point2d& p1, const Point2d& p2)
    {
        double x;
        
        if ((p1.y < m_rect.ymin) != (p2.y < m_rect.ymin))
        {
            x = p1.x + (m_rect.ymin - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            arr.push_back(Point2d(x, m_rect.ymin));
        }
        if (p2.y >= m_rect.ymin)
        {
            arr.push_back(p2);
        }
    }
    
    void clipRight(vector<Point2d>& arr, const Point2d& p1, const Point2d& p2)
    {
        double y;
        
        if ((p1.x > m_rect.xmax) != (p2.x > m_rect.xmax))
        {
            y = p1.y + (m_rect.xmax - p1.x) * (p2.y - p1.y) / (p2.x - p1.x);
            arr.push_back(Point2d(m_rect.xmax, y));
        }
        if (p2.x <= m_rect.xmax)
        {
            arr.push_back(p2);
        }
    }
    
    void clipBottom(vector<Point2d>& arr, const Point2d& p1, const Point2d& p2)
    {
        double x;
        
        if ((p1.y > m_rect.ymax) != (p2.y > m_rect.ymax))
        {
            x = p1.x + (m_rect.ymax - p1.y) * (p2.x - p1.x) / (p2.y - p1.y);
            arr.push_back(Point2d(x, m_rect.ymax));
        }
        if (p2.y <= m_rect.ymax)
        {
            arr.push_back(p2);
        }
    }
};

_GEOM_END
#endif // __GEOMETRY_POLYGONCLIP_H_