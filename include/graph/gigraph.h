//! \file gigraph.h
//! \brief ����ͼ��ϵͳ�� GiGraphics
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_GRAPHSYS_H_
#define __GEOMETRY_GRAPHSYS_H_

#include "gixform.h"
#include "gicontxt.h"

_GEOM_BEGIN

class GiGraphicsImpl;

//! ͼ��ϵͳ��
/*! ����������ʾ����ͼ�Σ�ͼԪ��ʾԭ����������ʵ�֣��������GDI/GDI+/SVG/PDF��ʵ�֣�
    ��ʾͼ�����õ�������������ϵת������ GiTransform �ж���ġ�
    \ingroup _GRAPH_INTERFACE_
*/
class GiGraphics
{
public:
    GiGraphics(GiTransform& xform);
    GiGraphics(const GiGraphics& src);
    virtual ~GiGraphics();
    GiGraphics& operator=(const GiGraphics& src);

protected:
    void beginPaint();
    void endPaint();

public:
    //! ��������ϵ�������
    const GiTransform& xf() const;

    //! �����Ƿ����ڻ��ƣ��������� beginPaint() ��δ���� endPaint()
    bool isDrawing() const;

public:
    //! �õ�ǰ����ɫ�������
    /*! �ñ���ɫ���ȫ����ʾ���򡣴�ӡ���ӡԤ��ʱ������Ч��
        \see getBkColor
    */
    virtual void clearWnd() = 0;

    //! ��ʾ�󱸻���λͼ
    /*! �󱸻���λͼ���ɺ��� saveCachedBitmap ���洴����
        \param x ��ʾƫ��X������
        \param y ��ʾƫ��Y������
        \param secondBmp ʹ���Ƿ�Ϊ�ڶ����󱸻���λͼ
        \return �Ƿ���Ƴɹ�
        \see saveCachedBitmap
    */
    virtual bool drawCachedBitmap(int x = 0, int y = 0, bool secondBmp = false) = 0;

    //! ��ʾ�󱸻���λͼ
    /*! ����һ��ͼ��ϵͳ�ĺ󱸻���λͼ��ʾ�����������ʾ�豸�ϣ�
        �󱸻���λͼ���ɺ��� saveCachedBitmap ���洴���ġ�\n
        ��һ��ͼ��ϵͳ�������Ǻ�̨��ʾ���䱾������ʾͼ�ε��豸�ϣ��������� endPaint(false)
        \param p ��һ��ͼ��ϵͳ���ö����к󱸻���λͼ
        \param secondBmp ʹ���Ƿ�Ϊ�ڶ����󱸻���λͼ
        \return �Ƿ���Ƴɹ�
        \see saveCachedBitmap
    */
    virtual bool drawCachedBitmap2(const GiGraphics* p, bool secondBmp = false) = 0;

    //! ������ʾ���ݵ��󱸻���λͼ
    /*! ����ǰ��ͼĿ��(�����ǻ�ͼ����)�����ݱ���Ϊһ��λͼ����
        ��λͼ�Ĵ�СΪ��ʾ���ڴ�С��\n
        ����ʾ���ڴ�С�ı����ʾ�����󣬽��Զ�����󱸻���λͼ��
        \param secondBmp �Ƿ�浽�ڶ����󱸻���λͼ
    */
    virtual void saveCachedBitmap(bool secondBmp = false) = 0;

    //! �����Ƿ��к󱸻���λͼ
    /*!
        \param secondBmp �����Ƿ�Ϊ�ڶ����󱸻���λͼ
        \return �Ƿ��иû���λͼ
    */
    virtual bool hasCachedBitmap(bool secondBmp = false) const = 0;

    //! ����󱸻���λͼ
    /*! ����ʾ���ڴ�С�ı����ʾ�����󣬵��� beginPaint() ʱ���Զ�����󱸻���λͼ��
    */
    virtual void clearCachedBitmap() = 0;

    //! �����Ƿ����ڻ�ͼ�����ϻ�ͼ
    /*! ��������� beginPaint ������ָ���Ƿ�ʹ�û�ͼ����
        \return �Ƿ����ڻ�ͼ�����ϻ�ͼ
        \see beginPaint
    */
    virtual bool isBufferedDrawing() const = 0;

    //! ����ͼ��ϵͳ���ͣ������������ֵ
    virtual int getGraphType() const = 0;

    //! ������Ļ�ֱ���DPI, ����
    virtual int getScreenDpi() const = 0;


    //! ���ؼ��ÿ�ģ������
    Box2d getClipModel() const;

    //! �õ����ÿ��߼�����
    /*!
        \param[out] prc ����߼��������
    */
    virtual void getClipBox(RECT* prc) const;

    //! ���ü��ÿ��߼�����
    /*! ֻ�������ڻ�ͼ״̬ʱ���ú����ķ���ֵ����Ч��
        ʧ��ʱ���ı�ͼ��ϵͳ�ڲ��������豸������ļ��ÿ�
        �����ʧ��ʱ��Ҫ������Ӧ��ͼ�����������ڴ���ļ��ÿ��С�

        \param[in] prc �߼��������
        \return �Ƿ�ɹ����ü��ÿ�û�д��ڻ�ͼ״̬�л������ļ��ÿ�Ϊ��ʱʧ��
    */
    virtual bool setClipBox(const RECT* prc);

    //! ���ü��ÿ���������
    /*! �¼��ÿ򽫻��ԭʼ���ÿ�������󽻣����Ժ������ܷ���ʧ�ܡ�\n
        ʧ��ʱ���ı�ͼ��ϵͳ�ڲ��������豸������ļ��ÿ�
        �����ʧ��ʱ��Ҫ������Ӧ��ͼ�����������ڴ���ļ��ÿ��С�\n
        ֻ�������ڻ�ͼ״̬ʱ���ú����ķ���ֵ����Ч��

        \param[in] rectWorld �����������
        \return �Ƿ�ɹ����ü��ÿ�û�д��ڻ�ͼ״̬�л������ļ��ÿ�Ϊ��ʱʧ��
    */
    virtual bool setClipWorld(const Box2d& rectWorld);
    

    //! ��ɫģʽ����
    enum kColorMode {
        kColorReal,     //!< ���
        kColorGray,     //!< �Ҷȣ�256��
        kColorMono      //!< ��ɫ������ɫ�ͷ�ɫ
    };
    //! ������ɫģʽ
    /*!
        \return ��ɫģʽ���� kColorMode ����
        \see kColorMode
    */
    int getColorMode() const;

    //! ������ɫģʽ
    /*!
        \param mode ��ɫģʽ���� kColorMode ����
        \see kColorMode
    */
    void setColorMode(int mode);
    

    //! ���ر���ɫ
    /*!
        \return ����ɫ��RGBɫ������Ǵ�ӡ���ӡԤ������Ϊ��ɫ
    */
    virtual GiColor getBkColor() const = 0;

    //! ���ñ���ɫ
    /*! ��������ڻ�ͼ״̬�У��ú�����ͬʱ���û�ͼ�豸�ı���ɫ
        \param color ����ɫ��RGBɫ
        \return ԭ���ı���ɫ
    */
    virtual GiColor setBkColor(const GiColor& color) = 0;

    //! ���غ�ģ���豸�ĵ�ɫ���������ɫ
    /*! ��ӡ���ӡԤ��ʱ����������Ч������ʱģ���豸Ϊ��ӡ��������Ϊ��ǰ��ʾ�豸��
        \param color ��ͨ��RGB��ɫ
        \return ����ģ���豸��RGB��ɫ
    */
    virtual GiColor getNearestColor(const GiColor& color) const = 0;

    //! ���㻭����ɫ
    /*! ������ɫģʽ���豸���Ե�����ʾ��ɫ��\n
        ���������ɫ�ͱ���ɫ��ͬ�������������Զ���ɫ����˿��ܿ�����ͼ��
        \param color ��ͨ��RGB��ɫ
        \return ʵ�ʻ�ͼ��RGB��ɫ
    */
    GiColor calcPenColor(const GiColor& color) const;

    //! ���㻭�ʿ��
    /*! ��ӡʱ���Զ�����������Ϊ��λ���߿�ʹ�ò���̫ϸ
        \param lineWidth �߿�������λΪ0.01���ף�������λΪ���أ�0��ʾ1����
        \param useViewScale �Ƿ�ʹ����ʾ����������
        \return ���ʿ�ȣ��Ǹ���������
    */
    UInt16 calcPenWidth(Int16 lineWidth, bool useViewScale = true) const;

    //! ������󻭱ʿ�ȣ�����
    /*! ֻ��Ҫ����Ļ��ʾ�����ã���ӡʱ���Զ�����
        \param pixels ��󻭱ʿ�ȣ�����
    */
    void setMaxPenWidth(UInt8 pixels);

    //! �����Ƿ�Ϊ������ģʽ
    bool isAntiAliasMode() const;

    //! �����Ƿ�Ϊ������ģʽ
    virtual void setAntiAliasMode(bool antiAlias);
    
    //! ���ص�ǰ��ͼ����
    virtual const GiContext* getCurrentContext() const = 0;
    

    //! ����ֱ�߶Σ�ģ���������������
    /*!
        \param ctx ��ͼ������������������ΪNULLʱȡΪ��һ����ͼ����
        \param startPt ���
        \param endPt �յ�
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
    */
    bool drawLine(const GiContext* ctx, 
        const Point2d& startPt, const Point2d& endPt, bool modelUnit = true);

    //! �������ߣ�ģ���������������
    /*!
        \param ctx ��ͼ������������������ΪNULLʱȡΪ��һ����ͼ����
        \param count ��ĸ���������Ϊ2
        \param points �������飬����Ϊcount
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
    */
    bool drawLines(const GiContext* ctx, 
        int count, const Point2d* points, bool modelUnit = true);

    //! ���ƶ������������ߣ�ģ���������������
    /*! ��һ�����ߴӵ�һ������Ƶ����ĸ��㣬�Եڶ�����͵�������Ϊ���Ƶ㡣
        �������е�ÿһ���������߶���Ҫ�����㣺
        ǰһ�����ߵ��յ���Ϊ��㣬�����е���������Ϊ���Ƶ㣬��������Ϊ�յ㡣

        \param ctx ��ͼ������������������ΪNULLʱȡΪ��һ����ͼ����
        \param count ��ĸ���������Ϊ4������Ϊ3�ı�����1
        \param points ���Ƶ�Ͷ˵�����飬����Ϊcount
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
    */
    bool drawBeziers(const GiContext* ctx, 
        int count, const Point2d* points, bool modelUnit = true);

    //! ������Բ����ģ���������������
    /*!
        \param ctx ��ͼ������������������ΪNULLʱȡΪ��һ����ͼ����
        \param center ��Բ��
        \param rx ��Բ�볤��ĳ���
        \param ry ��Բ�����ĳ��ȣ�Ϊ0ʱȡΪrx
        \param startAngle ��ʼ�Ƕȣ����ȣ������ָ������ϵ+X�ᣬ��ʱ��Ϊ��
        \param sweepAngle ת�ǣ����ȣ��������ʼ�Ƕȣ���ʱ��Ϊ����˳ʱ��Ϊ����
            ����2PI��С��-2PIʱ��ȡ2PI��-2PI
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
    */
    bool drawArc(const GiContext* ctx, 
        const Point2d& center, double rx, double ry, 
        double startAngle, double sweepAngle, bool modelUnit = true);


    //! ���Ʋ�������Σ�ģ���������������
    /*! ͨ�����ƴ����һ�����㵽��һ��������߶ζ��Զ��պ�
        \param ctx ��ͼ������ΪNULLʱȡΪ��һ����ͼ����
        \param count ��ĸ���������Ϊ2������Ҫ��ĩ�����غ�
        \param points �������飬����Ϊcount
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
    */
    bool drawPolygon(const GiContext* ctx, 
        int count, const Point2d* points, bool modelUnit = true);

    //! ���Ʋ������Բ��ģ���������������
    /*! ����볤��Ͱ����ĳ�����ͬ�����൱��Բ
        \param ctx ��ͼ������ΪNULLʱȡΪ��һ����ͼ����
        \param center Բ��
        \param rx ��Բ�볤��ĳ���
        \param ry ��Բ�����ĳ��ȣ�Ϊ0ʱȡΪrx
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
    */
    bool drawEllipse(const GiContext* ctx, 
        const Point2d& center, double rx, double ry = 0.0, 
        bool modelUnit = true);

    //! ���Ʋ������Բ����ͼ��ģ���������������
    /*! ����һ������Բ���������뾶�ཻ�պ϶��ɵı�״Ш��ͼ��
        ����볤��Ͱ����ĳ�����ͬ�����൱��Բ����
        \param ctx ��ͼ������ΪNULLʱȡΪ��һ����ͼ����
        \param center ��Բ��
        \param rx ��Բ�볤��ĳ���
        \param ry ��Բ�����ĳ��ȣ�Ϊ0ʱȡΪrx
        \param startAngle ��ʼ�Ƕȣ����ȣ������ָ������ϵ+X�ᣬ��ʱ��Ϊ��
        \param sweepAngle ת�ǣ����ȣ��������ʼ�Ƕȣ���ʱ��Ϊ����˳ʱ��Ϊ����
            ����2PI��С��-2PIʱ��ȡ2PI��-2PI
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
    */
    bool drawPie(const GiContext* ctx, 
        const Point2d& center, double rx, double ry, 
        double startAngle, double sweepAngle, bool modelUnit = true);

    //! ���Ʋ����ֱ�Ǿ��Σ�ģ���������������
    /*! 
        \param ctx ��ͼ������ΪNULLʱȡΪ��һ����ͼ����
        \param rect ֱ�Ǿ���
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
    */
    bool drawRect(const GiContext* ctx, const Box2d& rect, 
        bool modelUnit = true);

    //! ���Ʋ����Բ�Ǿ��Σ�ģ���������������
    /*! 
        \param ctx ��ͼ������ΪNULLʱȡΪ��һ����ͼ����
        \param rect �������
        \param rx X�����Բ�ǰ뾶������ʱ��Ч��������Ըò���
        \param ry Y�����Բ�ǰ뾶��Ϊ������ʱȡΪrx
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
    */
    bool drawRoundRect(const GiContext* ctx, 
        const Box2d& rect, double rx, double ry = 0.0, 
        bool modelUnit = true);


    //! �������β����������ߣ�ģ���������������
    /*! ��ʸ������ͨ�� mgCubicSplines ��������õ���һ���ȼ������ʸ����ÿ����ʾ��
        \param ctx ��ͼ������������������ΪNULLʱȡΪ��һ����ͼ����
        \param count ��ֵ��ĵ���������Ϊ2
        \param knots ��ֵ���������飬Ԫ�ظ���Ϊcount
        \param knotVectors ��ֵ�����ʸ�����飬Ԫ�ظ���Ϊcount
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
        \see mgCubicSplines
        \see drawClosedSplines
    */
    bool drawSplines(const GiContext* ctx, 
        int count, const Point2d* knots, const Vector2d* knotVectors, 
        bool modelUnit = true);

    //! ���Ʋ�������β����������ߣ��Զ��պ�
    /*! ��ĩ��ֵ�㲻���غϣ�������ͨ�����ƴ����һ����ֵ�㵽��һ����ֵ������߶ζ��Զ��պϡ�\n
        ��ʸ������ͨ�� mgCubicSplines ��������õ���һ���ȼ������ʸ����ÿ����ʾ��
        \param ctx ��ͼ������ΪNULLʱȡΪ��һ����ͼ����
        \param count ��ֵ��ĵ���������Ϊ2
        \param knots ��ֵ���������飬Ԫ�ظ���Ϊcount
        \param knotVectors ��ֵ�����ʸ�����飬Ԫ�ظ���Ϊcount
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
        \see mgCubicSplines
        \see drawSplines
    */
    bool drawClosedSplines(const GiContext* ctx, 
        int count, const Point2d* knots, const Vector2d* knotVectors, 
        bool modelUnit = true);

    //! ��������B�������ߣ�ģ���������������
    /*! 
        \param ctx ��ͼ������������������ΪNULLʱȡΪ��һ����ͼ����
        \param count ���Ƶ�ĵ���������Ϊ4
        \param controlPoints ���Ƶ��������飬����Ϊcount
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
        \see drawClosedBSplines
    */
    bool drawBSplines(const GiContext* ctx, 
        int count, const Point2d* controlPoints, bool modelUnit = true);

    //! ���Ʋ��������B�������ߣ��Զ��պ�
    /*! ��ĩ���Ƶ㲻���غϣ�������ͨ������������߶ζ��Զ��պ�
        \param ctx ��ͼ������ΪNULLʱȡΪ��һ����ͼ����
        \param count ���Ƶ�ĵ���������Ϊ3
        \param controlPoints ���Ƶ��������飬����Ϊcount
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
        \see drawBSplines
    */
    bool drawClosedBSplines(const GiContext* ctx, 
        int count, const Point2d* controlPoints, bool modelUnit = true);

    //! ����·����ģ���������������
    /*! 
        \param ctx ��ͼ������ΪNULLʱȡΪ��һ����ͼ����
        \param count ������points��types��Ԫ�ظ���
        \param points �˵�Ϳ��Ƶ������
        \param types points��ÿһ��ĺ��壬��MSDN��PolyDraw��˵����ֵΪPT_MOVETO��
        \param modelUnit ָ��������ߴ���ģ������(true)������������(false)
        \return �Ƿ���ʾ�ɹ���ʧ��ԭ��Ϊ��������򳬳���������
        \see GiPath::getPoints
    */
    bool drawPath(const GiContext* ctx, int count, 
        const Point2d* points, const UInt8* types, bool modelUnit = true);


    //! ����ֱ�߶ε�ԭ�ﺯ�����������꣬������
    virtual bool rawLine(const GiContext* ctx, 
        int x1, int y1, int x2, int y2) = 0;

    //! �������ߵ�ԭ�ﺯ�����������꣬������
    virtual bool rawPolyline(const GiContext* ctx, 
        const POINT* lppt, int count) = 0;

    //! ���ƶ������������ߵ�ԭ�ﺯ�����������꣬������
    virtual bool rawPolyBezier(const GiContext* ctx, 
        const POINT* lppt, int count) = 0;

    //! ���ƶ���ε�ԭ�ﺯ�����������꣬������
    virtual bool rawPolygon(const GiContext* ctx, 
        const POINT* lppt, int count) = 0;

    //! ���ƾ��ε�ԭ�ﺯ�����������꣬������
    virtual bool rawRect(const GiContext* ctx, 
        int x, int y, int w, int h) = 0;

    //! ������Բ��ԭ�ﺯ�����������꣬������
    virtual bool rawEllipse(const GiContext* ctx, 
        int x, int y, int w, int h) = 0;

    //! ���ƶ����ߵ�ԭ�ﺯ�����������꣬������
    virtual bool rawPolyDraw(const GiContext* ctx, 
        int count, const POINT* lppt, const UInt8* types) = 0;


    //! ��ʼһ��·����ԭ�ﺯ��
    virtual bool rawBeginPath() = 0;

    //! ��������ʾһ��·����ԭ�ﺯ��
    virtual bool rawEndPath(const GiContext* ctx, bool fill) = 0;

    //! �ڵ�ǰ·�����ƶ����µ�λ�õ�ԭ�ﺯ��
    virtual bool rawMoveTo(int x, int y) = 0;

    //! �ڵ�ǰ·������ӻ���ָ��µ�λ�õ�ԭ�ﺯ��
    virtual bool rawLineTo(int x, int y) = 0;

    //! �ڵ�ǰ·������ӻ�����������ָ���ԭ�ﺯ��
    virtual bool rawPolyBezierTo(const POINT* lppt, int count) = 0;

    //! �ڵ�ǰ·������ӱպ�ָ���ԭ�ﺯ��
    virtual bool rawCloseFigure() = 0;

protected:
    GiGraphics();
    GiGraphicsImpl*  m_impl;
};

//! ����ͻָ�ͼ��ϵͳ�ļ��ÿ�ĸ�����
/*! ���ø����ڶ�ջ�϶���ֲ��������ñ��������������Զ������Ӷ��ָ����ÿ�
    ���ø�����Ա�������;�˳����쳣ʱû��ִ�лָ����ÿ����䡣
    \ingroup _GRAPH_INTERFACE_
*/
class GiSaveClipBox
{
public:
    //! ���캯�������µļ��ÿ�ѹջ
    /*! ������� succeed ��������Ƿ�ɹ���ʧ��ʱ��Ҫ������ͼ
        \param gs Ҫ������ÿ��ͼ��ϵͳ
        \param rectWorld �¼��ÿ�������������
        \see succeed
    */
    GiSaveClipBox(GiGraphics* gs, const Box2d& rectWorld)
    {
        m_gs = gs;
        gs->getClipBox(&m_clipRect);
        m_clip = gs->setClipWorld(rectWorld);
    }

    //! �����������ָ���һ�����ÿ�
    ~GiSaveClipBox()
    {
        if (m_clip)
            m_gs->setClipBox(&m_clipRect);
    }

    //! �����Ƿ�ɹ��������¼��ÿ�
    /*! �������false����Ҫ�����ڸ�����������ÿ��µĻ�ͼ������
        ��Ϊʧ��ʱ�����޷������κ�ͼ�Σ��������ü��ÿ�ʱ�����ı���ÿ�
        �����������ͼ������ܻ��Ƴ�ͼ�Σ����Ѿ�������ȷ�ļ��ÿ��С�
        \return �Ƿ�ɹ��������¼��ÿ�
    */
    bool succeed() const
    {
        return m_clip;
    }

private:
    GiGraphics* m_gs;
    RECT        m_clipRect;
    bool        m_clip;
};

_GEOM_END
#endif // __GEOMETRY_GRAPHSYS_H_