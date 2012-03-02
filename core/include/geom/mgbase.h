//! \file mgbase.h
//! \brief ����������㹦�ܺ���
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_BASIC_H_
#define __GEOMETRY_BASIC_H_

#include "mgdef.h"

_GEOM_BEGIN

//! ����ת������ֵ��Χ[tmin, tmax)��
/*! ת���������ԭ���������(tmax - tmin)����������
    \ingroup _GEOMAPI_BASIC_
    \param[in] value ������������
    \param[in] tmin ��ֵ��Χ������
    \param[in] tmax ��ֵ��Χ�����ޣ��������tmin
    \return ת������������ڵ���tmin��С��tmax
*/
GEOMAPI double mgToRange(double value, double tmin, double tmax);

//! ʹ�Ƕ���[0, 2PI)֮��
/*! ת����ĽǶȺ�ԭ���ĽǶ����2PI��������
    \ingroup _GEOMAPI_BASIC_
    \param[in] angle �Ƕȣ���λΪ����
    \return �Ƕȣ����ȣ���Χ��[0��2PI)֮��
    \see mgToRange, mgToPI, _M_2PI
*/
GEOMAPI double mgTo0_2PI(double angle);

//! ʹ�Ƕ���[-PI, PI)֮��
/*! ת����ĽǶȺ�ԭ���ĽǶ����2PI��������
    \ingroup _GEOMAPI_BASIC_
    \param[in] angle �Ƕȣ���λΪ����
    \return �Ƕȣ����ȣ���Χ��[-PI, PI)֮��
    \see mgToRange, mgTo0_2PI, M_PI
*/
GEOMAPI double mgToPI(double angle);

//! �ǶȴӶ�ת��������
/*! �ڲ��ǳ���һ����������ת��
    \ingroup _GEOMAPI_BASIC_
    \param[in] deg �Զ�Ϊ��λ�ĽǶ�
    \return �Ի���Ϊ��λ�ĽǶ�
    \see mgRad2Deg, mgDms2Deg, _M_D2R
*/
GEOMAPI double mgDeg2Rad(double deg);

//! �Ƕȴӻ���ת������
/*! �ڲ��ǳ���һ����������ת��
    \ingroup _GEOMAPI_BASIC_
    \param[in] rad �Ի���Ϊ��λ�ĽǶ�
    \return �Զ�Ϊ��λ�ĽǶ�
    \see mgDeg2Rad, mgDms2Deg, _M_R2D
*/
GEOMAPI double mgRad2Deg(double rad);

//! �ȷ���ת�����Ƕ�(��)
/*! �ȷ�����ʽ�ĽǶȵ���������Ϊ�ȣ�ʮ��λ�Ͱٷ�λΪ�֣�
    ǧ��λ�����λ������С��λΪ�롣����32.251242��ʾ32��25'12.42"��
    \ingroup _GEOMAPI_BASIC_
    \param[in] angle �ȷ�����ʽ�ĽǶ�
    \return �Զ�Ϊ��λ�ĽǶ�
    \see mgDeg2Dms, mgDeg2Rad
*/
GEOMAPI double mgDms2Deg(double angle);

//! �Ƕ�(��)ת�����ȷ���
/*! �ȷ�����ʽ�ĽǶȵ���������Ϊ�ȣ�ʮ��λ�Ͱٷ�λΪ�֣�
    ǧ��λ�����λ������С��λΪ�롣����32.251242��ʾ32��25'12.42"��
    \ingroup _GEOMAPI_BASIC_
    \param[in] angle �Զ�Ϊ��λ�ĽǶ�
    \return �ȷ�����ʽ�ĽǶ�
    \see mgDms2Deg, mgDeg2Rad
*/
GEOMAPI double mgDeg2Dms(double angle);

//! �������ǶȵĽ�ƽ���߽Ƕ�, [0, 2PI)
/*! �����������ʼ�Ƕȵ���ֹ�ǶȰ���ʱ�뷽����ת���ǶȵĽ�ƽ���߽Ƕȡ�
    �����ֹ�Ƕ�С����ʼ�Ƕȣ�����ֹ�Ƕ��Զ�����2PI�Ա㰴��ʱ�뷽����ת����ֹ�Ƕ�
    \ingroup _GEOMAPI_BASIC_
    \param[in] fromAngle ��ʼ�Ƕȣ�����
    \param[in] toAngle ��ֹ�Ƕȣ�����
    \return ��ƽ���߽Ƕȣ����ȣ���Χ��[0��2PI)֮��
*/
GEOMAPI double mgMidAngle(double fromAngle, double toAngle);

//! �������Ƕȵļн�, [-PI, PI)
/*! �����������ʼ�Ƕȵ���ֹ�ǶȰ���ʱ�뷽����ת���Ƕȣ���ת����[-PI��PI)��Χ
    \ingroup _GEOMAPI_BASIC_
    \param[in] fromAngle ��ʼ�Ƕȣ�����
    \param[in] toAngle ��ֹ�Ƕȣ�����
    \return �нǣ����ȣ���Χ��[-PI��PI)֮��
*/
GEOMAPI double mgDiffAngle(double fromAngle, double toAngle);

//! �������Լ��
/*! ���Լ�������ܱ������������������������Ҳ���������������������
    \ingroup _GEOMAPI_BASIC_
    \param[in] x ��һ��������
    \param[in] y �ڶ���������
    \return ���Լ����������
*/
GEOMAPI long mgGcd(long x, long y);

//! ��������Ϊ������
/*! ���� mgRoundReal(1.25, 1)=1.3
    \ingroup _GEOMAPI_BASIC_
    \param[in] value Ҫ�����������
    \param[in] decimal Ҫ������С��λ������ΧΪ-6��7��������ʾ��С��λ��
        0�൱��ȡ����������ʾȡ����ʹĳЩ��λ����Ϊ��
    \return ���������ĸ�����
    \see mgRound
*/
GEOMAPI double mgRoundReal(double value, int decimal);

_GEOM_END
#endif // __GEOMETRY_BASIC_H_