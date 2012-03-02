//! \file mglnrel.h
//! \brief ����ͼ��λ�ù�ϵ����
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_LINEREL_H_
#define __GEOMETRY_LINEREL_H_

#include "mgrect.h"

_GEOM_BEGIN

//! �жϵ�pt�Ƿ�������ֱ��a->b����� (������)
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ֱ�ߵ����
    \param[in] b ֱ�ߵ��յ�
    \param[in] pt �����Ĳ��Ե�
    \return ��ֱ�ߵ����ʱ����true�����򷵻�false
*/
GEOMAPI bool mgIsLeft(const Point2d& a, const Point2d& b, const Point2d& pt);

//! �жϵ�pt�Ƿ�������ֱ��a->b�����
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ֱ�ߵ����
    \param[in] b ֱ�ߵ��յ�
    \param[in] pt �����Ĳ��Ե�
    \param[in] tol �жϵ��ݲ�õ����еĳ����ݲ�ֵ
    \return ��ֱ�ߵ����ʱ����true�����򷵻�false
*/
GEOMAPI bool mgIsLeft2(
    const Point2d& a, const Point2d& b, const Point2d& pt, const Tol& tol);

//! �жϵ�pt�Ƿ�������ֱ��a->b����߻����� (������)
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ֱ�ߵ����
    \param[in] b ֱ�ߵ��յ�
    \param[in] pt �����Ĳ��Ե�
    \return ��ֱ�ߵ���߻�����ʱ����true�����򷵻�false
*/
GEOMAPI bool mgIsLeftOn(const Point2d& a, const Point2d& b, const Point2d& pt);

//! �жϵ�pt�Ƿ�������ֱ��a->b����߻�����
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ֱ�ߵ����
    \param[in] b ֱ�ߵ��յ�
    \param[in] pt �����Ĳ��Ե�
    \param[in] tol �жϵ��ݲ�õ����еĳ����ݲ�ֵ
    \return ��ֱ�ߵ���߻�����ʱ����true�����򷵻�false
*/
GEOMAPI bool mgIsLeftOn2(
    const Point2d& a, const Point2d& b, const Point2d& pt, const Tol& tol);

//! �жϵ�pt�Ƿ���ֱ��a->b������
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ֱ�ߵ����
    \param[in] b ֱ�ߵ��յ�
    \param[in] pt �����Ĳ��Ե�
    \return ��ֱ����ʱ����true�����򷵻�false
*/
GEOMAPI bool mgIsColinear(const Point2d& a, const Point2d& b, const Point2d& pt);

//! �жϵ�pt�Ƿ���ֱ��a->b������
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ֱ�ߵ����
    \param[in] b ֱ�ߵ��յ�
    \param[in] pt �����Ĳ��Ե�
    \param[in] tol �жϵ��ݲ�õ����еĳ����ݲ�ֵ
    \return ��ֱ����ʱ����true�����򷵻�false
*/
GEOMAPI bool mgIsColinear2(
    const Point2d& a, const Point2d& b, const Point2d& pt, const Tol& tol);

//! �ж������߶�ab��cd�Ƿ��ཻ���߶��ڲ�
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ��һ���߶ε����
    \param[in] b ��һ���߶ε��յ�
    \param[in] c �ڶ����߶ε����
    \param[in] d �ڶ����߶ε��յ�
    \return �Ƿ��ཻ���߶��ڲ����������˵�
*/
GEOMAPI bool mgIsIntersectProp(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d);

//! �жϵ�pt�Ƿ����߶�ab��(������)
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a �߶ε����
    \param[in] b �߶ε��յ�
    \param[in] pt �����Ĳ��Ե�
    \return ���߶���ʱ����true�����򷵻�false
*/
GEOMAPI bool mgIsBetweenLine(const Point2d& a, const Point2d& b, const Point2d& pt);

//! �жϵ�pt�Ƿ����߶�ab��
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a �߶ε����
    \param[in] b �߶ε��յ�
    \param[in] pt �����Ĳ��Ե�
    \param[in] tol �жϵ��ݲ�õ����еĳ����ݲ�ֵ
    \return ���߶���ʱ����true�����򷵻�false
*/
GEOMAPI bool mgIsBetweenLine2(
    const Point2d& a, const Point2d& b, const Point2d& pt, const Tol& tol);

//! ��֪��pt��ֱ��ab��, �жϵ�pt�Ƿ����߶�ab��(������)
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a �߶ε����
    \param[in] b �߶ε��յ�
    \param[in] pt �����Ĳ��Ե�
    \param[out] ptNear ���߶ε������˵��У��������ĵ�����Ķ˵㣬ΪNULL����Ըò���
    \return ���߶���ʱ����true�����򷵻�false
*/
GEOMAPI bool mgIsBetweenLine3(
    const Point2d& a, const Point2d& b, const Point2d& pt, Point2d* ptNear = NULL);

//! �ж������߶�ab��cd�Ƿ��ཻ(�������߶α�������)
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ��һ���߶ε����
    \param[in] b ��һ���߶ε��յ�
    \param[in] c �ڶ����߶ε����
    \param[in] d �ڶ����߶ε��յ�
    \return �Ƿ��ཻ���߶α������ڣ������˵�
*/
GEOMAPI bool mgIsIntersect(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d);

//! �����pt������ֱ��ab�ľ���
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ����ֱ�ߵ����
    \param[in] b ����ֱ�ߵ��յ�
    \param[in] pt �����Ĳ��Ե�
    \return �㵽����ֱ�ߵľ���
*/
GEOMAPI double mgPtToBeeline(const Point2d& a, const Point2d& b, const Point2d& pt);

//! �����pt������ֱ��ab�ľ���
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ����ֱ�ߵ����
    \param[in] b ����ֱ�ߵ��յ�
    \param[in] pt �����Ĳ��Ե�
    \param[out] ptPerp ֱ���ϵĴ���
    \return �����㵽����ľ���
*/
GEOMAPI double mgPtToBeeline2(
    const Point2d& a, const Point2d& b, const Point2d& pt, Point2d& ptPerp);

//! �����pt���߶�ab���������
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a �߶ε����
    \param[in] b �߶ε��յ�
    \param[in] pt �����Ĳ��Ե�
    \param[out] ptNear �߶��ϵ������
    \return �����㵽�����ľ���
*/
GEOMAPI double mgPtToLine(
    const Point2d& a, const Point2d& b, const Point2d& pt, Point2d& ptNear);

//! ������ֱ��(ax+by+c=0)�Ľ���
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a1 ��һ��ֱ�ߵı�׼���̲���A
    \param[in] b1 ��һ��ֱ�ߵı�׼���̲���B
    \param[in] c1 ��һ��ֱ�ߵı�׼���̲���C
    \param[in] a2 �ڶ���ֱ�ߵı�׼���̲���A
    \param[in] b2 �ڶ���ֱ�ߵı�׼���̲���B
    \param[in] c2 �ڶ���ֱ�ߵı�׼���̲���C
    \param[out] ptCross ����
    \param[in] tolVec �ж�ƽ�е��ݲ�õ���ʸ���ݲ�ֵ
    \return �Ƿ��н���
*/
GEOMAPI bool mgCrossLineAbc(
    double a1, double b1, double c1, double a2, double b2, double c2,
    Point2d& ptCross, const Tol& tolVec = Tol::gTol());

//! ����������ֱ�ߵĽ���
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ��һ��ֱ�ߵ����
    \param[in] b ��һ��ֱ�ߵ��յ�
    \param[in] c �ڶ���ֱ�ߵ����
    \param[in] d �ڶ���ֱ�ߵ��յ�
    \param[out] ptCross ����
    \param[out] pu �����ڵ�һ��ֱ���ϵĲ��������ΪNULL����Ըò���
    \param[out] pv �����ڵڶ���ֱ���ϵĲ��������ΪNULL����Ըò���
    \param[in] tolVec �ж�ƽ�е��ݲ�õ���ʸ���ݲ�ֵ
    \return �Ƿ��н���
*/
GEOMAPI bool mgCross2Beeline(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d, 
    Point2d& ptCross, double* pu = NULL, double* pv = NULL, 
    const Tol& tolVec = Tol::gTol());

//! �������߶εĽ���
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a ��һ���߶ε����
    \param[in] b ��һ���߶ε��յ�
    \param[in] c �ڶ����߶ε����
    \param[in] d �ڶ����߶ε��յ�
    \param[out] ptCross ����
    \param[in] tolVec �ж�ƽ�е��ݲ�õ���ʸ���ݲ�ֵ
    \return �Ƿ��н���
*/
GEOMAPI bool mgCross2Line(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d,
    Point2d& ptCross, const Tol& tolVec = Tol::gTol());

//! ���߶κ�ֱ�ߵĽ���
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] a �߶ε����
    \param[in] b �߶ε��յ�
    \param[in] c ֱ�ߵ����
    \param[in] d ֱ�ߵ��յ�
    \param[out] ptCross ����
    \param[out] pv ������ֱ���ϵĲ��������ΪNULL����Ըò���
    \param[in] tolVec �ж�ƽ�е��ݲ�õ���ʸ���ݲ�ֵ
    \return �Ƿ��н���
*/
GEOMAPI bool mgCrossLineBeeline(
    const Point2d& a, const Point2d& b, const Point2d& c, const Point2d& d,
    Point2d& ptCross, double* pv = NULL, 
    const Tol& tolVec = Tol::gTol());

//! �þ��μ����߶Σ�Sutherland-Cohen�㷨
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] pt1 �߶ε����
    \param[in] pt2 �߶ε��յ�
    \param[in] box ���þ��Σ�����Ϊ�ǿչ淶������
    \return ���ú��Ƿ��д��ڼ��þ����ڵ��߶β���
*/
GEOMAPI bool mgClipLine(Point2d& pt1, Point2d& pt2, const Box2d& box);

//! mgPtInArea �ķ���ֵö�ٶ���
//! \see mgPtInArea
enum PtInAreaRet
{
    kPtInArea,          //!< �ڶ������
    kPtOutArea,         //!< �ڶ������
    kPtOnEdge,          //!< �ڵ�order����
    kPtAtVertex,        //!< ���order�����غ�
};

//! �ж�һ���Ƿ���һ����η�Χ��
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] pt �����Ĳ��Ե�
    \param[in] count ����εĶ�����
    \param[in] vertexs ����εĶ�������
    \param[out] order ���� kPtAtVertex ʱ����������[0, count-1]��\n
        ���� kPtOnEdge ʱ������ߺ�[0, count-1]��\nΪNULL����Ըò���
    \param[in] tol �ݲ�
    \return Ϊö�ٶ��� PtInAreaRet �ĸ���ֵ
    \see PtInAreaRet
*/
GEOMAPI int mgPtInArea(
    const Point2d& pt, Int32 count, const Point2d* vertexs, 
    Int32& order, const Tol& tol = Tol::gTol());

//! �ж϶�����Ƿ�Ϊ͹�����
/*!
    \ingroup _GEOMAPI_LNREL_
    \param[in] count �������
    \param[in] vertexs ��������
    \param[out] pACW ������Ƿ�Ϊ��ʱ�뷽��ΪNULL����Ըò���
    \return �Ƿ�Ϊ͹�����
*/
GEOMAPI bool mgIsConvex(Int32 count, const Point2d* vertexs, bool* pACW = NULL);

_GEOM_END
#endif // __GEOMETRY_LINEREL_H_