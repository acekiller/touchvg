//! \file gixform.h
//! \brief ��������ϵ������ GiTransform
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_TRANSFORMSYS_H_
#define __GEOMETRY_TRANSFORMSYS_H_

#include "gidef.h"
#include <mgrect.h>

_GEOM_BEGIN

//! ����ϵ������
/*!
    \ingroup _GRAPH_INTERFACE_
    ����ϵ������Ĺ����ǹ���ͼ��ϵͳ�õ��ĸ�������ϵ����ת����
    �õ�������������ϵ��\n
    1. ��������ϵ���̶�����ĵѿ�������ϵ�������������ж������������ϵ�Ļ�����
    �� �õ�λ�����ʾ����λΪ���ס�\n
    2. ģ������ϵ���û����������ϵ������������ʵ�����е�ͼ�Σ��䵥λ�������ߡ�
    �� X���Y��ķ��������������趨��ģ������ϵ��һ���任����(Matrix)��ʾ��\n
    3. ��ʾ����ϵ������ʾ������ӡ������ͼ������ʾʱ�õ�����ϵ����λΪ���أ�
    �� +X���ң�+Y���£�ԭ������ʾ���ڵ����Ͻǡ���ʾ����ϵ����ʾ���ڵ����ĵ�����
    �� ���ꡢ��ʾ��������ʾ�豸�ķֱ���(DPI)��ͬ���������Լ����һ���任����
*/
class GiTransform
{
public:
    //! Ĭ�Ϲ��캯��
    /*! ��������Ϊ��96dpi����ʾ�������ĵ���������Ϊ(0,0)����ʾ����Ϊ100����
        ģ������ϵ�ı任����Ϊ��λ������ʾ������ΧΪ1����500����
        ��ʾ���޵��������귶ΧΪ(-1e5,-1e5)��(1e5,1e5)
        \param ydown true��ʾ��ʾ�豸��+Y����Ϊ���£�false������
    */
    GiTransform(bool ydown = true);

    //! �������캯��
    /*! ������ enableZoom ��Ӧ����
        \param src Դ����
    */
    GiTransform(const GiTransform& src);

    //! ��������
    ~GiTransform();

    //! ��ֵ����������
    /*! ������ enableZoom ��Ӧ����
        \param src Դ����
        \return �����������
    */
    GiTransform& operator=(const GiTransform& src);
    
public:
    //! ���ص�ǰ��ͼ���豸X�ֱ���
    /*! ��Ļ������ʾʱΪ��Ļ�ֱ��ʣ���ӡ���ӡԤ��ʱΪ��ӡ���ֱ���
    */
    long getDpiX() const;

    //! ���ص�ǰ��ͼ���豸Y�ֱ���
    /*! ��Ļ������ʾʱΪ��Ļ�ֱ��ʣ���ӡ���ӡԤ��ʱΪ��ӡ���ֱ���
    */
    long getDpiY() const;

    //! ������ʾ���ڵĿ�ȣ�����
    /*! ��Ļ��ʾʱΪ���ڵĿͻ�����ȣ���ӡ�ʹ�ӡԤ��ʱΪֽ�ſɴ�ӡ������
    */
    long getWidth() const;

    //! ������ʾ���ڵĸ߶ȣ�����
    /*! ��Ļ��ʾʱΪ���ڵĿͻ����߶ȣ���ӡ�ʹ�ӡԤ��ʱΪֽ�ſɴ�ӡ����߶�
    */
    long getHeight() const;

    //! ������ʾ�������ĵ���������
    Point2d getCenterW() const;

    //! ������ʾ����
    /*! ��ʾ����Ϊ1ʱ��ʾ100����ʾ��С��1ʱ��С��ʾ������1ʱ�Ŵ���ʾ
    */
    double getViewScale() const;

    //! ����X���������絥λ��Ӧ��������
    /*! ��ֵ��ʾX��������������ϵ��1��λ���ȶ�Ӧ����ʾ����ϵ�еĳ���(����)��
        ����ʾ�豸�ֱ��ʺ���ʾ������������Ϊ getDpiX() * getViewScale()
    */
    double getWorldToDisplayX() const;

    //! ����Y���������絥λ��Ӧ��������
    /*! ��ֵ��ʾY��������������ϵ��1��λ���ȶ�Ӧ����ʾ����ϵ�еĳ���(����)��
        ����ʾ�豸�ֱ��ʺ���ʾ������������Ϊ getDpiY() * getViewScale()
    */
    double getWorldToDisplayY() const;

    //! ����ģ������ϵ����������ϵ�ı任����
    const Matrix2d& modelToWorld() const;

    //! ������������ϵ��ģ������ϵ�ı任����
    const Matrix2d& worldToModel() const;

    //! ������ʾ����ϵ����������ϵ�ı任����
    const Matrix2d& displayToWorld() const;

    //! ������������ϵ����ʾ����ϵ�ı任����
    const Matrix2d& worldToDisplay() const;

    //! ������ʾ����ϵ��ģ������ϵ�ı任����
    const Matrix2d& displayToModel() const;

    //! ����ģ������ϵ����ʾ����ϵ�ı任����
    const Matrix2d& modelToDisplay() const;

    //! ������ʾ���ڵĴ�С������
    /*! ��ʾ��������Ļ��ʾʱΪ���ڵĿͻ������Σ���ӡ�ʹ�ӡԤ��ʱΪֽ�ſɴ�ӡ����\n
        ��Ļ��ʾʱ��һ�����ڴ��ڵ�WM_SIZE�¼�����Ӧ�����е��øú�����������
        OnSize(UINT nType, int cx, int cy)�����е���setWndSize(cx, cy)��\n
        ��ӡ�ʹ�ӡԤ��ʱ�����������ͼ��ϵͳ�� printSetup �����������ٵ��ñ�������
        ������Ҫ��ֽ�ſɴ�ӡ����Ĵ�С��Ϊ�������ñ�����
        \param width ��ʾ���ڵĿ�ȣ�����
        \param height ��ʾ���ڵĸ߶ȣ�����
    */
    void setWndSize(int width, int height);

    //! ������ʾ�ֱ���
    /*! һ�㲻ֱ�ӵ��ñ����������ǵ���ͼ��ϵͳ�� beginPaint �� printSetup ����
        \param dpiX ˮƽ�ֱ���DPI
        \param dpiY ��ֱ�ֱ���DPI��Ϊ0��ȡΪdpiX
    */
    void setResolution(int dpiX, int dpiY = 0);

    //! ����ģ������ϵ�ı任����
    /*! �����ڵ���ͼ��ϵͳ�� beginPaint ����ǰ���ñ�������\n
        ���� Matrix2d::coordSystem ��������任����
        ���� GiSaveModelTransform �ౣ��ͻָ�ģ������ϵ�ı任����
        \param mat ģ������ϵ����������ϵ�ı任���󣬱������
    */
    void setModelTransform(const Matrix2d& mat);

    //! ������С��ʾ����
    double getMinViewScale() const;

    //! ���������ʾ����
    double getMaxViewScale() const;

    //! ������ʾ���޵��������귶Χ
    Box2d getWorldLimits() const;

    //! ������ʾ������Χ
    /*!
        \param minScale ��С��ʾ��������1e-5��0.5֮��
        \param maxScale �����ʾ��������1.0��20֮��
    */
    void setViewScaleRange(double minScale, double maxScale);

    //! ������ʾ���޵��������귶Χ
    /*! ���Ϊ�վ��ο������ʱ��������ʾλ�ã�������������ʾ���޵��������귶Χ��
        \param rect �������귶Χ
        \return ԭ�������꼫�޷�Χ
    */
    Box2d setWorldLimits(const Box2d& rect);

    
    //! �����Ŵ�
    /*! �������������γɵľ����е�ͼ����ȫ��ʾ����ʾ�������������У�
        ��ʹ����������С���ҽ�������������е㴦��ͼ��λ��ƽ�Ƶ���ʾ���ڵ�����
        \param pt1 ��ʾ�����е�һ�㣬�߼�����
        \param pt2 ��ʾ�����е���һ�㣬�߼�����
        \param adjust �����ʾ������λ�ó�����Χ���Ƿ����
        \return �Ƿ�����ɹ�
    */
    bool zoomWnd(const POINT& pt1, const POINT& pt2, bool adjust = true);

    //! ����ͼ�ε���������
    /*! ��ָ����ͼ�η�ΧrectWorld������ʾ����ʾ�����е�ָ������rcTo��
        ��ʹ����������С���ҽ�������������е㴦��ͼ��λ��ƽ�Ƶ���ʾ���ڵ�����
        \param rectWorld Ҫ��ʾ��ͼ�η�Χ����������
        \param rcTo ��ʾ�����е�ָ�������߼����꣬���ΪNULL��Ϊ������ʾ���ڷ�Χ
        \param adjust �����ʾ������λ�ó�����Χ���Ƿ����
        \return �Ƿ�����ɹ�
    */
    bool zoomTo(const Box2d& rectWorld, const RECT* rcTo = NULL, bool adjust = true);

    //! ƽ����ʾ
    /*! ��һ�����������ƽ����ʾ����Ļ��ָ����
        \param pntWorld ͼ�ε����������
        \param pxAt ��ʾ�����е�һ�㣬�߼����꣬���ΪNULL��Ϊ��ʾ���ڵ�����
        \param adjust �����ʾ������λ�ó�����Χ���Ƿ����
        \return �Ƿ�����ɹ�
    */
    bool zoomTo(const Point2d& pntWorld, const POINT* pxAt = NULL, bool adjust = true);

    //! ƽ����ʾ
    /*! 
        \param dxPixel ͼ�����ҵ�ƽ����������
        \param dyPixel ͼ�����ϵ�ƽ����������
        \param adjust �����ʾ������λ�ó�����Χ���Ƿ����
        \return �Ƿ�����ɹ�
    */
    bool zoomPan(double dxPixel, double dyPixel, bool adjust = true);

    //! ��һ��Ϊ���İ��ձ��ʷ���
    /*! ��factor����0ʱ����ʾ��������Ϊԭ����(1+factor)����\n
        ��factorС��0ʱ����ʾ��������Ϊԭ����1/(1+fabs(factor))��
        \param factor �������ʣ�����0ʱ�Ŵ�С��0ʱ��С
        \param pxAt ��ʾ�����б��ֲ����ĵ���߼����꣬ΪNULLʱȡ��ʾ�������ĵ�
        \param adjust �����ʾ������λ�ó�����Χ���Ƿ����
        \return �Ƿ�����ɹ�
    */
    bool zoomByFactor(double factor, const POINT* pxAt = NULL, bool adjust = true);

    //! ��һ��Ϊ����ָ����������
    /*! 
        \param viewScale ��ʾ����
        \param pxAt ��ʾ�����б��ֲ����ĵ���߼����꣬ΪNULLʱȡ��ʾ�������ĵ�
        \param adjust �����ʾ������λ�ó�����Χ���Ƿ����
        \return �Ƿ�����ɹ�
    */
    bool zoomScale(double viewScale, const POINT* pxAt = NULL, bool adjust = true);

    //! ������ʾ����״̬
    /*! 
        \param[in] centerW ��ʾ�������ĵ���������
        \param[in] viewScale ��ʾ����
        \param[out] changed ����Ƿ��Ѹı���������ı�ǣ�ΪNULL�����
        \return ʼ�շ���true
    */
    bool zoom(Point2d centerW, double viewScale, bool* changed = NULL);

    //! ���ø��ַ��������Ƿ�������Ч
    /*! �����������ڼ�������������Ч�ԣ�����ı�ͼ��ϵͳ�ķ���״̬��
        �ڿ��������в����Ʊ�������
        \param enabled �µ�����״̬��true: ֱ�Ӹı����״̬��������Ч��
            false: ����¼��ʱ�����������������ı�֪ͨ
        \return ԭ��������״̬�����ڻָ�״̬��
    */
    bool enableZoom(bool enabled);

    //! �õ���һ�η��������Ľ��
    /*! ���� enableZoom ����ʲôֵ�����ܻ�ȡ�������
        \param[out] centerW ��ʾ�������ĵ���������
        \param[out] viewScale ��ʾ����
    */
    void getZoomValue(Point2d& centerW, double& viewScale) const;

    //! ���ط�������ı�Ĵ�������ͼ��ϵͳ�ȹ۲������Ƚ�ʹ��
    long getZoomTimes() const;

private:
    struct Data;
    Data*   m_data;
};

//! ����ͻָ�ģ������ϵ�ı任����ĸ�����
/*! ���ø����ڶ�ջ�϶���ֲ��������ñ��������������Զ������Ӷ��ָ�ģ������ϵ��
    ���ø�����Ա�������;�˳����쳣ʱû��ִ�лָ�ģ������ϵ����䡣
    \ingroup _GRAPH_INTERFACE_
*/
class GiSaveModelTransform
{
public:
    //! ���캯�������µ�ģ������ϵѹջ
    /*!
        \param xform Ҫ����ģ������ϵ��ͼ��ϵͳ
        \param mat �任������ԭ����ģ������ϵ������ʩ�Ӹ��ӵļ��α任��
            ������ģ������ϵ�ı任����Ϊԭ���������ָ������xMat�Ľ��
    */
    GiSaveModelTransform(GiTransform* xform, const Matrix2d& mat)
        : m_xform(xform)
        , m_mat(xform->modelToWorld())
    {
        m_xform->setModelTransform(m_mat * mat);
    }

    //! �����������ָ���һ��ģ������ϵ�ı任����
    ~GiSaveModelTransform()
    {
        m_xform->setModelTransform(m_mat);
    }

private:
    GiTransform*    m_xform;
    Matrix2d        m_mat;
};

_GEOM_END
#endif // __GEOMETRY_TRANSFORMSYS_H_