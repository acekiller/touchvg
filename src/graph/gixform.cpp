// gixform.cpp: ʵ������ϵ������GiTransform
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#include "gixform.h"

_GEOM_BEGIN

//! ������Χ
struct ZoomLimit
{
    double      dMinViewScale;  //!< ��С��ʾ����
    double      dMaxViewScale;  //!< �����ʾ����
    Box2d       rectLimitsW;    //!< ��ʾ���޵��������귶Χ

    ZoomLimit()
    {
        dMinViewScale = 0.01;   // ��С��ʾ����Ϊ1%
        dMaxViewScale = 5.0;    // �����ʾ����Ϊ500%
        rectLimitsW.set(Point2d::kOrigin(), 2e5, 2e5);
    }
};

//! GiTransform���ڲ�����
struct GiTransform::Data : public ZoomLimit
{
    GiTransform*    xform;      //!< ӵ����
    long        cxWnd;          //!< ��ʾ���ڿ�ȣ�����
    long        cyWnd;          //!< ��ʾ���ڸ߶ȣ�����
    long        curDpiX;        //!< ��ʾ�豸ÿӢ���������X
    long        curDpiY;        //!< ��ʾ�豸ÿӢ���������Y
    Point2d     pntCenterW;     //!< ��ʾ�������ĵ��������꣬Ĭ��(0,0)
    double      viewScale;      //!< ��ʾ������Ĭ��100%
    Matrix2d    matM2W;         //!< ģ������ϵ����������ϵ�ı任����Ĭ�ϵ�λ����

    Matrix2d    matW2M;         //!< ��������ϵ��ģ������ϵ�ı任����
    Matrix2d    matD2W;         //!< ��ʾ����ϵ����������ϵ�ı任����
    Matrix2d    matW2D;         //!< ��������ϵ����ʾ����ϵ�ı任����
    Matrix2d    matD2M;         //!< ��ʾ����ϵ��ģ������ϵ�ı任����
    Matrix2d    matM2D;         //!< ģ������ϵ����ʾ����ϵ�ı任����
    double      dW2DX;          //!< ���絥λ��Ӧ��������X
    double      dW2DY;          //!< ���絥λ��Ӧ��������Y

    bool        zoomEnabled;    //!< �Ƿ��������
    Point2d     tmpCenterW;     //!< ��ǰ��������������Ƿ��������
    double      tmpViewScale;   //!< ��ǰ��������������Ƿ��������
    long        zoomTimes;      //!< ��������ı�Ĵ���

    Data(GiTransform* p) : xform(p)
        , cxWnd(1), cyWnd(1), curDpiX(96), curDpiY(96), viewScale(1.0)
        , zoomEnabled(true), tmpViewScale(1.0), zoomTimes(0)
    {
        updateTransforms();
    }

    void updateTransforms()
    {
        dW2DX = viewScale * curDpiX / 25.4;
        dW2DY = viewScale * curDpiY / 25.4;

        double xc = cxWnd * 0.5;
        double yc = cyWnd * 0.5;
        matD2W.set(1.0 / dW2DX, 0, 0, -1.0 / dW2DY,
            pntCenterW.x - xc / dW2DX, pntCenterW.y + yc / dW2DY);
        matW2D.set(dW2DX, 0, 0, -dW2DY,
            xc - dW2DX * pntCenterW.x, yc + dW2DY * pntCenterW.y);

        matD2M = matD2W * matW2M;
        matM2D = matM2W * matW2D;
    }

    void coptFrom(const Data* pSrc)
    {
        cxWnd  = pSrc->cxWnd;
        cyWnd  = pSrc->cyWnd;
        curDpiX = pSrc->curDpiX;
        curDpiY = pSrc->curDpiY;
        pntCenterW = pSrc->pntCenterW;
        viewScale = pSrc->viewScale;
        matM2W = pSrc->matM2W;
        matW2M = pSrc->matW2M;
        matD2W = pSrc->matD2W;
        matW2D = pSrc->matW2D;
        matD2M = pSrc->matD2M;
        matM2D = pSrc->matM2D;
        dW2DX = pSrc->dW2DX;
        dW2DY = pSrc->dW2DY;
        dMinViewScale = pSrc->dMinViewScale;
        dMaxViewScale = pSrc->dMaxViewScale;
        rectLimitsW = pSrc->rectLimitsW;
        tmpCenterW = pSrc->tmpCenterW;
        tmpViewScale = pSrc->tmpViewScale;
    }

    void zoomChanged()
    {
        giInterlockedIncrement(&zoomTimes);
    }

    bool zoomNoAdjust(const Point2d& pnt, double scale, bool* changed = NULL)
    {
        bool bChanged = false;

        if (pnt != pntCenterW || !mgIsZero(scale - viewScale))
        {
            tmpCenterW = pnt;
            tmpViewScale = scale;
            bChanged = true;
            if (zoomEnabled)
            {
                pntCenterW = pnt;
                viewScale = scale;
                updateTransforms();
                zoomChanged();
            }
        }
        if (changed != NULL)
            *changed = bChanged;

        return bChanged;
    }

    bool zoomPanAdjust(Point2d &ptW, double dxPixel, double dyPixel) const;
};

GiTransform::GiTransform()
{
    m_data = new Data(this);
}

GiTransform::GiTransform(const GiTransform& src)
{
    m_data = new Data(this);
    m_data->coptFrom(src.m_data);
}

GiTransform::~GiTransform()
{
    delete m_data;
}

GiTransform& GiTransform::operator=(const GiTransform& src)
{
    if (this != &src)
        m_data->coptFrom(src.m_data);
    return *this;
}

long GiTransform::getDpiX() const { return m_data->curDpiX; }
long GiTransform::getDpiY() const { return m_data->curDpiY; }
long GiTransform::getWidth() const { return m_data->cxWnd; }
long GiTransform::getHeight() const { return m_data->cyWnd; }
Point2d GiTransform::getCenterW() const { return m_data->pntCenterW; }
double GiTransform::getViewScale() const { return m_data->viewScale; }
double GiTransform::getWorldToDisplayX() const { return m_data->dW2DX; }
double GiTransform::getWorldToDisplayY() const { return m_data->dW2DY; }
const Matrix2d& GiTransform::modelToWorld() const
    { return m_data->matM2W; }
const Matrix2d& GiTransform::worldToModel() const
    { return m_data->matW2M; }
const Matrix2d& GiTransform::displayToWorld() const
    { return m_data->matD2W; }
const Matrix2d& GiTransform::worldToDisplay() const
    { return m_data->matW2D; }
const Matrix2d& GiTransform::displayToModel() const
    { return m_data->matD2M; }
const Matrix2d& GiTransform::modelToDisplay() const
    { return m_data->matM2D; }
double GiTransform::getMinViewScale() const
    { return m_data->dMinViewScale; }
double GiTransform::getMaxViewScale() const
    { return m_data->dMaxViewScale; }
Box2d GiTransform::getWorldLimits() const
    { return m_data->rectLimitsW; }

long GiTransform::getZoomTimes() const
{
    return m_data->zoomTimes;
}

void GiTransform::setWndSize(int width, int height)
{
    if ((m_data->cxWnd != width || m_data->cyWnd != height)
        && width > 1 && height > 1)
    {
        m_data->cxWnd = width;
        m_data->cyWnd = height;
        m_data->updateTransforms();
        m_data->zoomChanged();
    }
}

void GiTransform::setModelTransform(const Matrix2d& mat)
{
    if (mat.isInvertible() && m_data->matM2W != mat)
    {
        m_data->matM2W = mat;
        m_data->matW2M = m_data->matM2W.inverse();
        m_data->matD2M = m_data->matD2W * m_data->matW2M;
        m_data->matM2D = m_data->matM2W * m_data->matW2D;
        m_data->zoomChanged();
    }
}

void GiTransform::setResolution(int dpiX, int dpiY)
{
    if (dpiX > 10 && dpiY > 10 
        && (m_data->curDpiX != dpiX || m_data->curDpiY != dpiY))
    {
        m_data->curDpiX = dpiX;
        m_data->curDpiY = dpiY;
        m_data->updateTransforms();
        m_data->zoomChanged();
    }
}

void GiTransform::setViewScaleRange(double minScale, double maxScale)
{
    if (minScale > maxScale)
        mgSwap(minScale, maxScale);

    minScale = mgMax(minScale, 1e-5);
    minScale = mgMin(minScale, 0.5);

    maxScale = mgMax(maxScale, 1.0);
    maxScale = mgMin(maxScale, 20.0);

    m_data->dMinViewScale = minScale;
    m_data->dMaxViewScale = maxScale;
}

Box2d GiTransform::setWorldLimits(const Box2d& rect)
{
    Box2d ret = m_data->rectLimitsW;
    m_data->rectLimitsW = rect;
    m_data->rectLimitsW.normalize();
    return ret;
}

bool GiTransform::enableZoom(bool enabled)
{
    bool bOld = m_data->zoomEnabled;
    m_data->zoomEnabled = enabled;
    return bOld;
}

void GiTransform::getZoomValue(Point2d& pntCenterW, double& viewScale) const
{
    pntCenterW = m_data->tmpCenterW;
    viewScale = m_data->tmpViewScale;
}

bool GiTransform::zoom(Point2d pntCenterW, double viewScale, bool* changed)
{
    viewScale = mgMax(viewScale, m_data->dMinViewScale);
    viewScale = mgMin(viewScale, m_data->dMaxViewScale);

    if (!m_data->rectLimitsW.isEmpty())
    {
        double halfw = m_data->cxWnd / m_data->dW2DX * 0.5;
        double halfh = m_data->cyWnd / m_data->dW2DY * 0.5;

        if (pntCenterW.x - halfw < m_data->rectLimitsW.xmin)
            pntCenterW.x += m_data->rectLimitsW.xmin - (pntCenterW.x - halfw);
        if (pntCenterW.x + halfw > m_data->rectLimitsW.xmax)
            pntCenterW.x += m_data->rectLimitsW.xmax - (pntCenterW.x + halfw);
        if (2 * halfw >= m_data->rectLimitsW.width())
            pntCenterW.x = m_data->rectLimitsW.center().x;

        if (pntCenterW.y - halfh < m_data->rectLimitsW.ymin)
            pntCenterW.y += m_data->rectLimitsW.ymin - (pntCenterW.y - halfh);
        if (pntCenterW.y + halfh > m_data->rectLimitsW.ymax)
            pntCenterW.y += m_data->rectLimitsW.ymax - (pntCenterW.y + halfh);
        if (2 * halfh >= m_data->rectLimitsW.height())
            pntCenterW.y = m_data->rectLimitsW.center().y;

        // �����ʾ������Сʹ�ô��ڳ��磬�ͷŴ���ʾ
        if (2 * halfw > m_data->rectLimitsW.width()
            && 2 * halfh > m_data->rectLimitsW.height())
        {
            viewScale *= mgMin(2 * halfw / m_data->rectLimitsW.width(),
                2 * halfh / m_data->rectLimitsW.height());
            if (viewScale > m_data->dMaxViewScale)
                viewScale = m_data->dMaxViewScale;
        }
    }

    m_data->zoomNoAdjust(pntCenterW, viewScale, changed);

    return true;
}

static inline bool ScaleOutRange(double scale, const ZoomLimit* pData)
{
    return scale < pData->dMinViewScale - 1e-5
        || scale > pData->dMaxViewScale + 1e-5;
}

static void AdjustCenterW(Point2d &ptW, double halfw, double halfh, 
                          const Box2d& rectLimitsW)
{
    if (ptW.x - halfw < rectLimitsW.xmin)
        ptW.x += rectLimitsW.xmin - (ptW.x - halfw);
    if (ptW.x + halfw > rectLimitsW.xmax)
        ptW.x += rectLimitsW.xmax - (ptW.x + halfw);
    if (2 * halfw >= rectLimitsW.width())
        ptW.x = rectLimitsW.center().x;

    if (ptW.y - halfh < rectLimitsW.ymin)
        ptW.y += rectLimitsW.ymin - (ptW.y - halfh);
    if (ptW.y + halfh > rectLimitsW.ymax)
        ptW.y += rectLimitsW.ymax - (ptW.y + halfh);
    if (2 * halfh >= rectLimitsW.height())
        ptW.y = rectLimitsW.center().y;
}

bool GiTransform::zoomWnd(const POINT& pt1, const POINT& pt2, bool adjust)
{
    // ���㿪�����ε����ĺͿ��
    Point2d ptCen ((pt2.x + pt1.x) * 0.5, (pt2.y + pt1.y) * 0.5);
    double w = fabs(static_cast<double>(pt2.x - pt1.x));
    double h = fabs(static_cast<double>(pt2.y - pt1.y));
    if (w < 4 || h < 4)
        return false;

    // ���Ĳ��䣬���󿪴�����ʹ�ÿ�߱�������ʾ������ͬ
    if (h * m_data->cxWnd > w * m_data->cyWnd)
        w = h * m_data->cxWnd / m_data->cyWnd;
    else
        h = w * m_data->cyWnd / m_data->cxWnd;

    // �������ǰ�������ĵ���������
    Point2d ptW (ptCen * m_data->matD2W);

    // ��������ʾ����
    double scale = m_data->viewScale * m_data->cyWnd / h;
    if (!adjust && ScaleOutRange(scale, m_data))
        return false;
    scale = mgMax(scale, m_data->dMinViewScale);
    scale = mgMin(scale, m_data->dMaxViewScale);

    // ��������ʾ�����µ���ʾ���ڵ��������귶Χ
    double halfw = m_data->cxWnd / (m_data->dW2DX / m_data->viewScale * scale) * 0.5;
    double halfh = m_data->cyWnd / (m_data->dW2DY / m_data->viewScale * scale) * 0.5;
    Box2d box (ptW, 2 * halfw, 2 * halfh);

    // �����ʾ���ڵ������귶Χ�Ƿ��ڼ��޷�Χ��
    if (!m_data->rectLimitsW.isEmpty() && !m_data->rectLimitsW.isInside(box))
    {
        if (adjust)
            AdjustCenterW(ptW, halfw, halfh, m_data->rectLimitsW);
        else
            return false;
    }

    // �ı���ʾ������λ��
    return m_data->zoomNoAdjust(ptW, scale);
}

bool GiTransform::zoomTo(const Box2d& rectWorld, const RECT* rcTo, bool adjust)
{
    // ���ͼ�η�Χ�Ŀ��߽ӽ����㣬�ͷ���
    if (rectWorld.isEmpty())
        return false;

    // �������ص����׵ı���
    const double d2mmX = m_data->viewScale / m_data->dW2DX;
    const double d2mmY = m_data->viewScale / m_data->dW2DY;

    // ����Ŀ�괰������(����)
    double w = 0, h = 0;
    Point2d ptCen;

    if (rcTo != NULL)
    {
        w = fabs(static_cast<double>(rcTo->right - rcTo->left));
        h = fabs(static_cast<double>(rcTo->bottom - rcTo->top));
        ptCen.x = (rcTo->left + rcTo->right) * 0.5;
        ptCen.y = (rcTo->top + rcTo->bottom) * 0.5;
    }
    if (w < 4 || h < 4)
    {
        w = m_data->cxWnd;
        h = m_data->cyWnd;
        ptCen.set(m_data->cxWnd * 0.5, m_data->cyWnd * 0.5);
    }
    if (w < 4 || h < 4)
        return false;
    w *= d2mmX;
    h *= d2mmY;
    ptCen.scaleBy(d2mmX, d2mmY);

    // ��������ʾ���� (���Ĳ��䣬��С��������ʹ�ÿ�߱�����ͼ�η�Χ��ͬ)
    double scale;
    if (h * rectWorld.width() > w * rectWorld.height())
    {
        //h = w * rectWorld.height() / rectWorld.width();
        scale = w / rectWorld.width();
    }
    else
    {
        //w = h * rectWorld.width() / rectWorld.height();
        scale = h / rectWorld.height();
    }

    // �����ʾ����
    if (!adjust && ScaleOutRange(scale, m_data))
        return false;
    scale = mgMax(scale, m_data->dMinViewScale);
    scale = mgMin(scale, m_data->dMaxViewScale);

    // ����������ʾ��������ʾ�������ĵ���������
    Point2d ptW;
    ptW.x = rectWorld.center().x + (m_data->cxWnd * d2mmX * 0.5 - ptCen.x) / scale;
    ptW.y = rectWorld.center().y - (m_data->cyWnd * d2mmY * 0.5 - ptCen.y) / scale;

    // �������ʾ��������ʾ���ڵ��������귶Χ�Ƿ��ڼ��޷�Χ��
    double halfw = m_data->cxWnd * d2mmX  / scale * 0.5;
    double halfh = m_data->cyWnd * d2mmY  / scale * 0.5;
    Box2d box (ptW, 2 * halfw, 2 * halfh);
    if (!m_data->rectLimitsW.isEmpty() && !m_data->rectLimitsW.isInside(box))
    {
        if (adjust)
            AdjustCenterW(ptW, halfw, halfh, m_data->rectLimitsW);
        else
            return false;
    }

    return m_data->zoomNoAdjust(ptW, scale);
}

bool GiTransform::zoomTo(const Point2d& pntWorld, const POINT* pxAt, bool adjust)
{
    Point2d pnt = pntWorld * m_data->matW2D;
    return zoomPan(
        (pxAt == NULL ? (m_data->cxWnd * 0.5) : pxAt->x) - pnt.x, 
        (pxAt == NULL ? (m_data->cyWnd * 0.5) : pxAt->y) - pnt.y, adjust);
}

bool GiTransform::zoomPan(double dxPixel, double dyPixel, bool adjust)
{
    // �����µ���ʾ�������ĵ���������
    Vector2d vec (dxPixel, dyPixel);
    Point2d ptW (m_data->pntCenterW - vec * m_data->matD2W);

    // �������ʾ��������ʾ���ڵ��������귶Χ�Ƿ��ڼ��޷�Χ��
    if (!m_data->rectLimitsW.isEmpty())
    {
        if (m_data->zoomPanAdjust(ptW, dxPixel, dyPixel) && !adjust)
            return false;
    }
    if (ptW == m_data->pntCenterW)
        return false;

    return m_data->zoomNoAdjust(ptW, m_data->viewScale);
}

bool GiTransform::Data::zoomPanAdjust(Point2d &ptW, 
                                      double dxPixel, double dyPixel) const
{
    bool bAdjusted = false;
    double halfw = cxWnd / dW2DX * 0.5;
    double halfh = cyWnd / dW2DY * 0.5;

    if (dxPixel > 0 && ptW.x - halfw < rectLimitsW.xmin)
    {
        bAdjusted = true;
        ptW.x += rectLimitsW.xmin - (ptW.x - halfw);
    }
    if (dxPixel < 0 && ptW.x + halfw > rectLimitsW.xmax)
    {
        bAdjusted = true;
        ptW.x += rectLimitsW.xmax - (ptW.x + halfw);
    }
    if (fabs(dxPixel) > 0 && 2 * halfw >= rectLimitsW.width())
    {
        bAdjusted = true;
        ptW.x = rectLimitsW.center().x;
    }
    if (dyPixel < 0 && ptW.y - halfh < rectLimitsW.ymin)
    {
        bAdjusted = true;
        ptW.y += rectLimitsW.ymin - (ptW.y - halfh);
    }
    if (dyPixel > 0 && ptW.y + halfh > rectLimitsW.ymax)
    {
        bAdjusted = true;
        ptW.y += rectLimitsW.ymax - (ptW.y + halfh);
    }
    if (fabs(dyPixel) > 0 && 2 * halfh >= rectLimitsW.height())
    {
        bAdjusted = true;
        ptW.y = rectLimitsW.center().y;
    }

    return bAdjusted;
}

bool GiTransform::zoomByFactor(double factor, const POINT* pxAt, bool adjust)
{
    double scale = m_data->viewScale;
    if (factor > 0)
        scale *= (1 + fabs(factor));
    else
        scale /= (1 + fabs(factor));

    if (adjust)
    {
        scale = mgMax(scale, m_data->dMinViewScale);
        scale = mgMin(scale, m_data->dMaxViewScale);
    }
    if (mgIsZero(scale - m_data->viewScale))
        return false;
    return zoomScale(scale, pxAt, adjust);
}

bool GiTransform::zoomScale(double viewScale, const POINT* pxAt, bool adjust)
{
    // �����ʾ����
    if (!adjust && ScaleOutRange(viewScale, m_data))
        return false;
    viewScale = mgMax(viewScale, m_data->dMinViewScale);
    viewScale = mgMin(viewScale, m_data->dMaxViewScale);

    // �õ��������ĵ�Ŀͻ�������
    Point2d ptAt (m_data->cxWnd * 0.5,  m_data->cyWnd * 0.5);
    if (pxAt != NULL)
        ptAt.set(pxAt->x, pxAt->y);

    // �õ��������ĵ��ڷ���ǰ����������
    Point2d ptAtW (ptAt * m_data->matD2W);

    // ��������ʾ��������ʾ�������ĵ���������
    Point2d ptW;
    double dW2DX = m_data->dW2DX / m_data->viewScale * viewScale;
    double dW2DY = m_data->dW2DY / m_data->viewScale * viewScale;
    ptW.x = ptAtW.x + (m_data->cxWnd * 0.5 - ptAt.x) / dW2DX;
    ptW.y = ptAtW.y - (m_data->cyWnd * 0.5 - ptAt.y) / dW2DY;

    // �������ʾ��������ʾ���ڵ��������귶Χ�Ƿ��ڼ��޷�Χ��
    double halfw = m_data->cxWnd / dW2DX * 0.5;
    double halfh = m_data->cyWnd / dW2DY * 0.5;
    Box2d box (ptW, 2 * halfw, 2 * halfh);
    if (!m_data->rectLimitsW.isEmpty() && !m_data->rectLimitsW.isInside(box))
    {
        if (adjust)
            AdjustCenterW(ptW, halfw, halfh, m_data->rectLimitsW);
        else
            return false;
    }

    return m_data->zoomNoAdjust(ptW, viewScale);
}

_GEOM_END
