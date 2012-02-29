//! \file mgnear.h
//! \brief �����������������ĺ���
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_CURVENEAR_H_
#define __GEOMETRY_CURVENEAR_H_

#include "mgrect.h"

_GEOM_BEGIN

//! ����һ�㵽���α��������߶��ϵ������
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in] pt ���߶�������ĵ�
    \param[in] pts ���α��������߶εĿ��Ƶ㣬4����
    \param[out] ptNear ���߶��ϵ������
*/
GEOMAPI void mgNearestOnBezier(
    const Point2d& pt, const Point2d* pts, Point2d& ptNear);

//! ���㱴�������ߵİ󶨿�
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[out] box �󶨿�
    \param[in] count ��ĸ���������Ϊ4������Ϊ3�ı�����1
    \param[in] points ���Ƶ�Ͷ˵�����飬����Ϊcount
    \param[in] closed �Ƿ�Ϊ�պ�����
    \see mgCubicSplines
*/
GEOMAPI void mgBeziersBox(
    Box2d& box, Int32 count, const Point2d* points, bool closed = false);

//! ���������������ߵİ󶨿�
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[out] box �󶨿�
    \param[in] n �����������ߵ���ֵ��ĵ���
    \param[in] knots ��ֵ���������飬Ԫ�ظ���Ϊn
    \param[in] knotVectors ��ֵ�����ʸ�����飬Ԫ�ظ���Ϊn
    \param[in] closed �Ƿ�Ϊ�պ�����
    \see mgCubicSplines
*/
GEOMAPI void mgCubicSplinesBox(
    Box2d& box, Int32 n, const Point2d* knots, 
    const Vector2d* knotVectors, bool closed = false);

//! ����㵽�����������ߵ��������
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in] n �����������ߵ���ֵ��ĵ���
    \param[in] knots ��ֵ���������飬Ԫ�ظ���Ϊn
    \param[in] knotVectors ��ֵ�����ʸ�����飬Ԫ�ظ���Ϊn
    \param[in] closed �Ƿ�Ϊ�պ�����
    \param[in] pt ���߶�������ĵ�
    \param[in] dTol ���빫������������򲻼��������
    \param[out] ptNear �����ϵ������
    \param[out] nSegment ������������߶ε���ţ�[0,n-2]���պ�ʱΪ[0,n-1]��������ʾʧ��
    \return �����ĵ㵽�����ľ��룬ʧ��ʱΪ������
    \see mgCubicSplines
*/
GEOMAPI double mgCubicSplinesHit(
    Int32 n, const Point2d* knots, const Vector2d* knotVectors, bool closed, 
    const Point2d& pt, double dTol, Point2d& ptNear, Int32& nSegment);

//! ����㵽���߻����ε��������
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] n ������
    \param[in] points �����������飬Ԫ�ظ���Ϊn
    \param[in] closed �Ƿ�Ϊ�����
    \param[in] pt ͼ��������ĵ�
    \param[in] dTol ���빫������������򲻼��������
    \param[out] ptNear ͼ���ϵ������
    \param[out] nSegment ����������߶ε���ţ�[0,n-2]���պ�ʱΪ[0,n-1]��������ʾʧ��
    \return �����ĵ㵽�����ľ��룬ʧ��ʱΪ������
*/
GEOMAPI double mgLinesHit(
    Int32 n, const Point2d* points, bool closed, 
    const Point2d& pt, double dTol, Point2d& ptNear, Int32& nSegment);

//! ����㵽Բ�Ǿ��ε��������
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] rect ��Ӿ��Σ�����Ϊ�淶������
    \param[in] rx ˮƽ�����Բ�ǰ뾶���Ǹ���
    \param[in] ry ��ֱ�����Բ�ǰ뾶��Ϊ0��ȡΪrx
    \param[in] pt ͼ��������ĵ�
    \param[in] dTol ���빫������������򲻼��������
    \param[out] ptNear ͼ���ϵ������
    \param[out] nSegment ��������ڶε���š�������ʾʧ�ܣ�
        0��3Ϊ�����Ͻ���˳ʱ����ĸ�Բ�ǣ�4��7Ϊ���ҵ���
    \return �����ĵ㵽�����ľ��룬ʧ��ʱΪ������
*/
GEOMAPI double mgRoundRectHit(
    const Box2d& rect, double rx, double ry, 
    const Point2d& pt, double dTol, Point2d& ptNear, Int32& nSegment);

//! �õ����ε�8�������ֱ�����
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] rect ���Σ�����Ϊ�淶������
    \param[in] nHandle �����ֱ�����ţ�0��7��
        0��3Ϊ�����Ͻ���˳ʱ����ĸ��ǵ㣻4��7Ϊ���ҵ�����е㣻����Ϊ���ĵ�
    \param[out] pt �����ֱ�������
*/
GEOMAPI void mgGetRectHandle(const Box2d& rect, Int32 nHandle, Point2d& pt);

//! �ƶ����ε�һ�������ֱ�
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in,out] rect ���Σ�����Ϊ�淶������
    \param[in] nHandle �����ֱ�����ţ�0��7��
        0��3Ϊ�����Ͻ���˳ʱ����ĸ��ǵ㣻4��7Ϊ���ҵ�����е㣻����Ϊ���ĵ�
    \param[in] pt �����ֱ���������
*/
GEOMAPI void mgMoveRectHandle(Box2d& rect, Int32 nHandle, const Point2d& pt);

_GEOM_END
#endif // __GEOMETRY_CURVENEAR_H_