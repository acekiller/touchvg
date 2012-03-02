// _gigraph.h: ����GiGraphics����ڲ���Ա
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#include "gigraph.h"

_GEOM_BEGIN

//! GiGraphics���ڲ�ʵ����
class GiGraphicsImpl
{
public:
    enum { CLIP_INFLATE = 10 };

    GiGraphics*  pThis;             //!< ͼ��ϵͳ
    GiTransform& xform;             //!< ����ϵ�������

    UInt8       maxPenWidth;        //!< ��������߿�
    bool        antiAlias;          //!< ��ǰ�Ƿ��Ƿ�����ģʽ

    long        lastZoomTimes;      //!< ���µķ�������ı����
    long        drawRefcnt;         //!< ��ͼ��������
    bool        isPrint;            //!< �Ƿ��ӡ���ӡԤ��
    int         drawColors;         //!< ��ͼDC��ɫ��
    int         colorMode;          //!< ��ɫģʽ, enum kColorMode
    RECT        clipBox0;           //!< ��ʼ��ͼʱ�ļ��ÿ�(LP)

    RECT        clipBox;            //!< ���ÿ�(LP)
    Box2d       rectDraw;           //!< ���þ��Σ���clipBox�Դ�
    Box2d       rectDrawM;          //!< ���þ��Σ�ģ������
    Box2d       rectDrawW;          //!< ���þ��Σ���������
    Box2d       rectDrawMaxM;       //!< �����þ��Σ�ģ������
    Box2d       rectDrawMaxW;       //!< �����þ��Σ���������

    static long& screenDPI()
    {
        static long dpi = 0;
        return dpi;
    }

    GiGraphicsImpl(GiGraphics* gs, GiTransform& x) : pThis(gs), xform(x)
    {
        drawRefcnt = 0;
        drawColors = 0;
        colorMode = GiGraphics::kColorReal;
        isPrint = false;
        maxPenWidth = 50;
        antiAlias = true;
    }

    ~GiGraphicsImpl()
    {
    }
    
    void zoomChanged()
    {
        rectDrawM = rectDraw * xform.displayToModel();
        Box2d rect (0, 0, xform.getWidth(), xform.getHeight());
        rectDrawMaxM = rect * xform.displayToModel();
        rectDrawW = rectDrawM * xform.modelToWorld();
        rectDrawMaxW = rectDrawMaxM * xform.modelToWorld();
        pThis->clearCachedBitmap();
    }

private:
    GiGraphicsImpl();
    void operator=(const GiGraphicsImpl&);
};

//! ͼ��ϵͳ�Ļ�ͼ��������������
class GiLock
{
    long*  m_refcount;
public:
    GiLock(long* refcount) : m_refcount(refcount)
    {
        giInterlockedIncrement(m_refcount);
    }
    ~GiLock()
    {
        giInterlockedDecrement(m_refcount);
    }
};

_GEOM_END