//! \file gicontxt.h
//! \brief �����ͼ������ GiContext
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_DRAWCONTEXT_H_
#define __GEOMETRY_DRAWCONTEXT_H_

#include "gidef.h"
#include "gicolor.h"

_GEOM_BEGIN

//! ����
enum kLineStyle {
    kLineSolid = 0,
    kLineDash,          //!< -------
    kLineDot,           //!< .......
    kLineDashDot,       //!< _._._._
    kLineDashDotdot,    //!< _.._.._
    kLineNull
};

//! ��ͼ������������
/*! ������ͼ��ϵͳ�Ļ�ͼ�����д����ͼ����
    \ingroup _GRAPH_INTERFACE_
*/
class GiContext
{
public:
    //! Ĭ�Ϲ��캯��
    /*! ��ͼ����Ϊ1���ؿ�ĺ�ʵ�ߡ������
    */
    GiContext() : m_type(0), m_lineStyle(kLineSolid), m_lineWidth(0)
        , m_lineColor(GiColor::Black()), m_fillColor(GICOLOR_INVALID)
    {
    }
    
    //! ָ����������������
    /*! ������Ϊ�����
        \param width �߿�������ʾ��λΪ0.01mm�����ʾ1���ؿ�����ʱ��ʾ��λΪ����
        \param color ������ɫ�� GICOLOR_INVALID ��ʾ��������
        \param style ���ͣ�ȡֵΪ kLineSolid ��
    */
    GiContext(Int16 width, GiColor color = GiColor::Black(), kLineStyle style = kLineSolid)
        : m_type(0), m_lineStyle(style), m_lineWidth(width)
        , m_lineColor(color), m_fillColor(GICOLOR_INVALID)
    {
    }

    //! �������캯��
    GiContext(const GiContext& src)
    {
        m_lineStyle = src.m_lineStyle;
        m_lineWidth = src.m_lineWidth;
        m_lineColor = src.m_lineColor;
        m_fillColor = src.m_fillColor;
    }

    //! ��ֵ����������
    GiContext& operator=(const GiContext& src)
    {
        if (this != &src)
        {
            m_lineStyle = src.m_lineStyle;
            m_lineWidth = src.m_lineWidth;
            m_lineColor = src.m_lineColor;
            m_fillColor = src.m_fillColor;
        }
        return *this;
    }

    //! ��������
    kLineStyle getLineStyle() const
    {
        return m_lineColor.invalid() ? kLineNull : m_lineStyle;
    }

    //! ��������
    void setLineStyle(kLineStyle style)
    {
        m_lineStyle = style;
    }

    //! �����߿�
    /*! ������ʾ��λΪ0.01mm�����ʾ1���ؿ�����ʱ��ʾ��λΪ����
    */
    Int16 getLineWidth() const
    {
        return m_lineWidth;
    }

    //! �����߿�
    /*!
        \param width �߿�������ʾ��λΪ0.01mm�����ʾ1���ؿ�����ʱ��ʾ��λΪ����
    */
    void setLineWidth(Int16 width)
    {
        m_lineWidth = width;
    }

    //! �����Ƿ�Ϊ���ߣ���������
    bool isNullLine() const
    {
        return m_lineStyle == kLineNull || m_lineColor.invalid();
    }

    //! ����Ϊ���ߣ���������
    /*! ���Ҫ�ָ�����ͨ����״̬���ɵ�setLineStyle(kLineSolid)
    */
    void setNullLine()
    {
        m_lineStyle = kLineNull;
    }

    //! ����������ɫ
    GiColor getLineColor() const
    {
        return m_lineColor;
    }

    //! ����������ɫ�� GICOLOR_INVALID ��ʾ��������
    void setLineColor(const GiColor& color)
    {
        m_lineColor = color;
    }

    //! ��������͸����
    UInt8 getLineAlpha() const
    {
        return m_lineColor.a;
    }

    //! ��������͸���ȣ�0��255��0��ʾȫ͸����255��ʾ��͸��
    void setLineAlpha(UInt8 alpha)
    {
        m_lineColor.a = alpha;
    }

    //! �����Ƿ����
    bool hasFillColor() const
    {
        return !m_fillColor.invalid();
    }

    //! ����Ϊ�����
    void setNoFillColor()
    {
        m_fillColor = GICOLOR_INVALID;
    }

    //! ���������ɫ
    GiColor getFillColor() const
    {
        return m_fillColor;
    }

    //! ���������ɫ�� GICOLOR_INVALID ��ʾ�����
    void setFillColor(const GiColor& color)
    {
        m_fillColor = color;
    }

    //! �������͸����
    UInt8 getFillAlpha() const
    {
        return m_fillColor.a;
    }

    //! �������͸���ȣ�0��255��0��ʾȫ͸����255��ʾ��͸��
    void setFillAlpha(UInt8 alpha)
    {
        m_fillColor.a = alpha;
    }

    //! ���ػ�ͼ�������ͣ�����������
    /*! ����ʼ�շ���1������������� m_type Ϊ����ֵ
    */
    int getType() const
    {
        return m_type;
    }

protected:
    int         m_type;            //!< �������ָ������ֵ����ʾ��ͬ����
private:
    kLineStyle  m_lineStyle;       //!< ����
    Int16       m_lineWidth;       //!< �߿�, >0: 0.01mm, =0: 1px, <0:px
    GiColor     m_lineColor;
    GiColor     m_fillColor;
};

_GEOM_END
#endif // __GEOMETRY_DRAWCONTEXT_H_