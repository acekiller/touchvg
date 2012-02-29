//! \file mgtype.h
//! \brief ������ѧ���ο�ļ��������� VECTOR2D,POINT2D,BOX2D,MATRIX2D
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_MGTYPE_H_
#define __GEOMETRY_MGTYPE_H_

#include "mgnamesp.h"

_GEOM_BEGIN

//! ��άʸ���ṹ
typedef struct tagVECTOR2D
{
    double   x;     //!< X�������
    double   y;     //!< Y�������
} VECTOR2D;

//! ��ά��ṹ
typedef struct tagPOINT2D
{
    double   x;     //!< X�������
    double   y;     //!< Y�������
} POINT2D;

//! ���ο�ṹ
typedef struct tagBOX2D
{
    double   xmin;  //!< �������½�X����
    double   ymin;  //!< �������½�Y����
    double   xmax;  //!< �������Ͻ�X����
    double   ymax;  //!< �������Ͻ�Y����
} BOX2D;

//! ��ά��α任����ṹ
typedef struct tagMATRIX2D
{
    double   m11;   //!< ����Ԫ�أ�����X�������Ա任����
    double   m12;   //!< ����Ԫ�أ�����X�������Ա任����
    double   m21;   //!< ����Ԫ�أ�����Y�������Ա任����
    double   m22;   //!< ����Ԫ�أ�����Y�������Ա任����
    double   dx;    //!< ����Ԫ�أ�����X����ƽ����
    double   dy;    //!< ����Ԫ�أ�����Y����ƽ����
} MATRIX2D;

_GEOM_END

// ����׼ȷ�ֽڳ��ȵĻ�����������
#ifndef Int32
typedef signed   char  Int8;    //!< ���ֽ��з�����������
typedef unsigned char  UInt8;   //!< ���ֽ��޷�����������
typedef signed   short Int16;   //!< ˫�ֽ��з�����������
typedef unsigned short UInt16;  //!< ˫�ֽ��޷�����������
typedef signed   long  Int32;   //!< ���ֽ��з�����������
typedef unsigned long  UInt32;  //!< ���ֽ��޷�����������
#endif

#endif // __GEOMETRY_MGTYPE_H_