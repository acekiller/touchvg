//! \file giimagep.h
//! \brief ����GDI+ͼ���ļ��ĸ����� GiGdipImage
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_GDIPIMAGE_H_
#define __GEOMETRY_GDIPIMAGE_H_

#include "graphwin.h"
#include <ocidl.h>

_GEOM_BEGIN

//! GDI+ͼ���ļ��ĸ�����
/*!
    ֧�� BMP/JPEG/GIF/TIFF/PNG/WMF/EMF/ICON �ļ�
    \ingroup _GRAPH_INTERFACE_
*/
class GiGdipImage
{
public:
    //! ���캯�����ɴ�ָ�����ļ�
    GiGdipImage(const wchar_t* filename = L"");

    //! �Ӹ�����λͼ����
    GiGdipImage(HBITMAP hbm);

    //! ��������
    ~GiGdipImage();

    //! �ͷ��ڴ�
    void clear();

    //! ��ָ����ͼ���ļ�
    bool open(const wchar_t* filename);

    //! ����X�ֱ���
    long getDpiX() const;

    //! ����Y�ֱ���
    long getDpiY() const;

    //! ����ͼ�����ؿ��
    long getWidth() const;

    //! ����ͼ�����ظ߶�
    long getHeight() const;

    //! ����ͼ��ԭʼ��ȣ���λΪHIMETRIC(0.01mm)
    long getHmWidth() const;

    //! ����ͼ��ԭʼ�߶ȣ���λΪHIMETRIC(0.01mm)
    long getHmHeight() const;

    //! ����GDIͼ����Դ
    HBITMAP createBitmap(GiColor bkColor = GiColor::White()) const;

    //! ��ʾͼ����ת�Ƕ�Ϊ90�ȵ���������
    /*!
        \param graph ͼ��ϵͳ��������� GiGraphGdip �������Զ�ȡHBITMAP����ʾ
        \param rectW ����ͼ���Ӧ��������������
        \param fast ��ʾ��ʽ. true: ������ʾ, false: �߾�����ʾ
        \return �Ƿ���ʾ�ɹ�
    */
    bool draw(GiGraphWin& graph, const Box2d& rectW, bool fast = false) const;

    //! �����µ�����ͼ
    /*!
        \param maxWidth ��ͼ���������ؿ�ȣ�0��ʾ����С
        \param maxHeight ��ͼ���������ظ߶ȣ�0��ʾ����С
        \return �µ�����ͼ����Ҫ�� delete �ͷ�
    */
    GiGdipImage* thumbnailImage(UInt32 maxWidth = 0, UInt32 maxHeight = 0);

    //! ������ͼ���ļ�
    /*!
        \param filename �ļ�ȫ��
        \param quality JPEG����, 0��100
        \return �Ƿ�ִ�гɹ�
    */
    bool save(const wchar_t* filename, ULONG quality = 100);

    //! �õ�ͼƬ��׺����Ӧ��ͼ������ʽ��
    /*!
        \param[in] filename �ļ�����ֻҪ�����к�׺�����У����硰1.jpg��
        \param[out] format ���ͼ������ʽ���ƣ����硰image/jpeg��
        \param[out] clsidEncoder ���ͼ�������GUID
        \return �Ƿ��ѯ�ɹ�
    */
    static bool getEncoder(const wchar_t* filename, WCHAR format[20], CLSID& clsidEncoder);

private:
    struct Impl;
    Impl*   m_impl;
};

_GEOM_END
#endif // __GEOMETRY_GDIPIMAGE_H_