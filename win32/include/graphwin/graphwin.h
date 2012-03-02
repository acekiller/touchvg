//! \file graphwin.h
//! \brief ����ͼ��ϵͳ�� GiGraphWin
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_GRAPHWINSYS_WIN_H_
#define __GEOMETRY_GRAPHWINSYS_WIN_H_

#include "gigraph.h"

#ifndef _WINDOWS_
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

_GEOM_BEGIN

//! Windowsƽ̨��ͼ��ϵͳ��
/*! ����������Windowsƽ̨��ʾ����ͼ�Σ�ͼԪ��ʾԭ����������ʵ��
    \ingroup _GRAPH_INTERFACE_
*/
class GiGraphWin : public GiGraphics
{
public:
    //! Ĭ�Ϲ��캯��
    GiGraphWin(GiTransform& xform);

    //! �������캯��
    GiGraphWin(const GiGraphWin& src);

    //! ��ֵ����������
    GiGraphWin& operator=(const GiGraphWin& src);

public:
    //! ׼����ʼ��ͼ
    /*!
        ��������ѡ���ԵĴ�����ͼ���壬��ʼ����ͼ������
        �ڵ��û�ͼ����ǰ��������ñ�������\n
        ������hdcΪNULL����ǰ��ͼ��δ�����������ʧ�ܣ���ʱ��Ҫ���û�ͼ������endPaint()��
        ������óɹ������ڻ�ͼ��ɻ�ֹͣʱ���������endPaint()��\n
        ��ͼʱ��ӳ��ģʽ����ΪMM_TEXT������ʧ�ܡ�
        ��ӡԤ��ʱhdc��ӳ��ģʽ���Բ���MM_TEXT����attribDC��ӳ��ģʽ�����ΪMM_TEXT��\n
        ������������ setResolution ��������ӡ�ʹ�ӡԤ��ʱ�������� setWndSize ������

        \param hdc ��ʾ������豸��������
        \param attribDC ��ӡԤ��ʱΪ��ӡ������ͼ�ǵ��豸����������ʱ��ΪNULL
        \param buffered �Ƿ�ʹ�û�ͼ���壬��ӡ���ӡԤ��ʱ���Ըò���
        \param overlay ��ʹ�û�ͼ����ʱ, �ò�����ʾ�Ƿ���ԭhdc�ϵ���ʾ����
            �Ͻ��е�����ʾ�������������ʾ��ͨ����Ҫ���� clearWnd()
        \return �Ƿ��ʼ���ɹ���ʧ��ԭ���������ǰ��ͼ��δ���������������
        \see endPaint
    */
    virtual bool beginPaint(HDC hdc, HDC attribDC = NULL, 
        bool buffered = true, bool overlay = false);

    //! ������ͼ
    /*! ���������ٻ�ͼ����ͻ�ͼ��������ʱ���ݣ����ʹ���˻�ͼ���壬�ͽ������е�
        ͼ����ʾ��ԭ��ͼ����豸�������ϡ����� beginPaint �ɹ��󣬱�����ñ�������
        \param draw �Ƿ񽫻�ͼ����������ʾ��������beginPaint��ָ����ʹ�û�ͼ����ʱ��Ч��
            �ڽ���Ҫ���ɻ�ͼ����ʱ����false�������ɵ��� drawCachedBitmap2 ����ʾ��������
        \see beginPaint
        \see drawCachedBitmap2
    */
    virtual void endPaint(bool draw = true);

    //! ��ȡ��ͼDC
    /*! ����ں��� beginPaint ��ָ��ʹ�û�ͼ���壬��᷵�ػ�ͼ����DC��\n
        ���ñ�������ֻ��ʹ��GDI�ĺ�����һ�㲻�ܵ��ñ����Drawxxx��ͼ������\n
        ������ endPaint ֮ǰ���� releaseDC �ͷ���Դ��
        \return �豸��������
        \see releaseDC
    */
    virtual HDC acquireDC() = 0;

    //! �ͷŻ�ͼDC
    /*! ������ acquireDC �������ñ������ͷ�
        \param hdc �� acquireDC() ���ص��豸��������
        \see acquireDC
    */
    virtual void releaseDC(HDC hdc) = 0;

    //! ������Ļ�ֱ���DPI, ����
    virtual int getScreenDpi() const;

    //! ��ʾ���ֵ�ԭ�ﺯ��(������TextOutA)
    virtual bool rawTextOut(HDC hdc, int x, int y, const char* str, int len);
    
    //! ��ʾ���ֵ�ԭ�ﺯ��(������TextOutW)
    virtual bool rawTextOut(HDC hdc, int x, int y, const wchar_t* str, int len);

    //! ��ʾ���ֵ�ԭ�ﺯ��(������ExtTextOutA)
    virtual bool rawTextOut(HDC hdc, int x, int y, UInt32 options, 
        const RECT* prc, const char* str, int len, const Int32* pDx);

    //! ��ʾ���ֵ�ԭ�ﺯ��(������ExtTextOutW)
    virtual bool rawTextOut(HDC hdc, int x, int y, UInt32 options, 
        const RECT* prc, const wchar_t* str, int len, const Int32* pDx);

    //! ��ʾͼ����ת�Ƕ�Ϊ90�ȵ���������
    /*!
        \param hmWidth ͼ��ԭʼ��ȣ���λΪHIMETRIC(0.01mm)
        \param hmHeight ͼ��ԭʼ�߶ȣ���λΪHIMETRIC(0.01mm)
        \param hbitmap ͼ����Դ���
        \param rectW ����ͼ���Ӧ��������������
        \param fast ��ʾ��ʽ. true: ������ʾ, false: �߾�����ʾ
        \return �Ƿ���ʾ�ɹ�
    */
    virtual bool drawImage(long hmWidth, long hmHeight, HBITMAP hbitmap, 
        const Box2d& rectW, bool fast = false) = 0;

protected:
    HDC         m_attribDC;          //!< ����DC����ӡԤ��ʱΪ��ӡ��DC
};

//! ��ӡҳ������
/*! �ú���������ʾ�ֱ��ʡ���ʾ���ڴ�С�������������ʵ�������ʾ��\n
    �����˸ú�������Ҫ�ٵ��� setResolution �� setWndSize ������\n
    �������������� beginPaint ���������á�

    \param prtDC ��ӡ�����ͼ�ǵ��豸��������
    \param rectShow Ҫ��ӡ��ͼ�η�Χ���Ƿ�Ϊ����������bWorldRect������\n
        �����ģ��������Σ�Ӧֱ�Ӵ���ģ�����꣬�ɱ���������ȱʡģ�ͱ仯������㡣
    \param bWorldRect true��ʾ����ͼ�η�Χ���������꣬false��ʾ��ģ������
    \param margin �ĸ������ҳ�߾࣬��λΪ0.01mm��ΪNULL��ȡ��ӡֽ��Сҳ�߾�
    \param scale ��ӡ������Ϊ1���޷�����ӡ��С��1����С��ӡ��Ϊ0�����������ӡ
    \param offsetX ͼ���ڴ�ӡֽ�����Ҷ���ƫ���������ף�
        ��ָ������Ч�Ĵ�ӡ����ʱ�ò�����Ч
    \param offsetY ͼ���ڴ�ӡֽ�����϶���ƫ���������ף�
        ��ָ������Ч�Ĵ�ӡ����ʱ�ò�����Ч
    \return �Ƿ����úͷ����ɹ�
*/
bool giPrintSetup(GiTransform& xf, HDC prtDC, const Box2d& rectShow,
    bool bWorldRect = true, const RECT* margin = NULL,
    double scale = 0, double offsetX = 0, double offsetY = 0);

//! �Զ��������ͷż���DC�ĸ�����
class GiCompatibleDC
{
    HDC m_hdc;
public:
    //! ���캯��, �Զ���������DC
    GiCompatibleDC(HDC hdc)
    {
        m_hdc = ::CreateCompatibleDC(hdc);
    }
    //! ��������, �Զ��ͷż���DC
    ~GiCompatibleDC()
    {
        if (m_hdc != NULL)
            ::DeleteDC(m_hdc);
    }
    //! ���ؼ���DC�Ĳ���������
    operator HDC() const
    {
        return m_hdc;
    }
};

_GEOM_END
#endif // __GEOMETRY_GRAPHWINSYS_WIN_H_