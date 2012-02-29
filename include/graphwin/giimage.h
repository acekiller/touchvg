//! \file giimage.h
//! \brief ����ͼ���ļ��򿪺���ʾ�ĸ����� GiImage
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_IMAGE_H_
#define __GEOMETRY_IMAGE_H_

#include "graphwin.h"
#include <ocidl.h>
#include <objidl.h>

_GEOM_BEGIN

//! ���ļ���������
enum kOpenImageError
{
    kOpenImage_OK,              //!< �ɹ�
    kOpenImage_NullString,      //!< �ļ���Ϊ��
    kOpenImage_FileNotExist,    //!< �ļ�������
    kOpenImage_NullFile,        //!< ���ļ�
    kOpenImage_ReadFail,        //!< ��ȡ����ʧ��
    kOpenImage_TooLarge,        //!< �ļ�̫��, ����16M
    kOpenImage_NoMemory,        //!< �ڴ治��
    kOpenImage_NotPicture,      //!< ����ʶ��ͼ���ʽ
};

//! ͼ���ļ��򿪺���ʾ�ĸ�����
/*!
    ������� OleLoadPicture ����ͼ���ʽ���ļ���С������16M��
    ���ʹ��GDI+ͼ��ϵͳ GiGraphGdip ,������� GiGdipImage �����򿪺���ʾͼ��
    \ingroup _GRAPH_INTERFACE_
*/
class GiImage
{
public:
    //! Ĭ�Ϲ��캯��
    GiImage();

    //! ���캯������ָ�����ļ�
    GiImage(const char* filename);

    //! ���캯������ָ�����ļ�
    GiImage(const wchar_t* filename);

    //! ��������
    ~GiImage();

    //! �ͷ��ڴ�
    void clear();

    //! ��ָ����ͼ���ļ�
    bool open(const char* filename, kOpenImageError* perr = NULL);

    //! ��ָ����ͼ���ļ�
    bool open(const wchar_t* filename, kOpenImageError* perr = NULL);

    //! ����ͼ��ԭʼ��ȣ���λΪHIMETRIC(0.01mm)
    long getHmWidth() const;

    //! ����ͼ��ԭʼ�߶ȣ���λΪHIMETRIC(0.01mm)
    long getHmHeight() const;

    //! ����ͼ����Դ���
    HBITMAP getBitmap() const;

    //! ��ʾͼ����ת�Ƕ�Ϊ90�ȵ���������
    /*!
        \param graph ͼ��ϵͳ
        \param rectW ����ͼ���Ӧ��������������
        \param fast ��ʾ��ʽ. true: ������ʾ, false: �߾�����ʾ
        \return �Ƿ���ʾ�ɹ�
    */
    bool draw(GiGraphWin& graph, const Box2d& rectW, bool fast = false) const;

private:
    IPicture*   m_picture;
    IStream*    m_stream;
};

_GEOM_END
#endif // __GEOMETRY_IMAGE_H_