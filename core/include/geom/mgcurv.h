//! \file mgcurv.h
//! \brief �������߼��㺯��
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_FITCURVE_H_
#define __GEOMETRY_FITCURVE_H_

#include "mgrect.h"

_GEOM_BEGIN

//! �������α��������߶εĲ�����
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in] pts 4��������飬Ϊ���������߶εĿ��Ƶ�
    \param[in] t Ҫ����Ĳ�����Ĳ�������ΧΪ[0, 1]
    \param[out] ptFit ������Ĳ�����
    \see mgBezier4P, mgCubicSplines
*/
GEOMAPI void mgFitBezier(const Point2d* pts, double t, Point2d& ptFit);

//! �������ĵ㹹�����α��������߶�
/*! �ñ��������߶ε������յ�Ϊ�����㣬�м侭���������������㣬
    t=1/3��pt2, t=2/3��pt3��
    ������ı��������߶ε����Ϊpt1���յ�Ϊpt4���м��������Ƶ�ΪptCtr1��ptCtr2
    \ingroup _GEOMAPI_CURVE_
    \param[in] pt1 �ߵ����
    \param[in] pt2 ���ϵĵ�һ���м��
    \param[in] pt3 ���ϵĵڶ����м��
    \param[in] pt4 �ߵ��յ�
    \param[out] ptCtr1 �м��һ�����Ƶ�
    \param[out] ptCtr2 �м�ڶ������Ƶ�
    \see mgEllipse90ToBezier, mgEllipseToBezier, mgAngleArcToBezier
*/
GEOMAPI void mgBezier4P(
    const Point2d& pt1, const Point2d& pt2, const Point2d& pt3, 
    const Point2d& pt4, Point2d& ptCtr1, Point2d& ptCtr2);

//! �ø����������յ㹹��90����Բ������ת��Ϊһ�����α��������߶�
/*! ��Բ��Ϊ����㵽�յ���ʱ��ת90�ȡ�
    ������ı��������߶ε����Ϊpt1���յ�Ϊpt4���м��������Ƶ�ΪptCtr1��ptCtr2
    \ingroup _GEOMAPI_CURVE_
    \param[in] ptFrom ���
    \param[in] ptTo �յ�
    \param[out] ptCtr1 �м��һ�����Ƶ�
    \param[out] ptCtr2 �м�ڶ������Ƶ�
    \see mgBezier4P, mgEllipseToBezier, mgAngleArcToBezier
*/
GEOMAPI void mgEllipse90ToBezier(
    const Point2d& ptFrom, const Point2d& ptTo, Point2d& ptCtr1, Point2d& ptCtr2);

//! ��һ����Բת��Ϊ4�����α���������
/*! 4�����α����������ǰ���ʱ�뷽��ӵ�һ���޵������������ӣ�
    ��һ��������һ�����غ���+X���ϵ�(rx, 0)��
    \ingroup _GEOMAPI_CURVE_
    \param[out] points ���������ߵĿ��Ƶ㣬13����
    \param[in] center ��Բ��
    \param[in] rx �볤��ĳ���
    \param[in] ry �����ĳ���
    \see mgBezier4P, mgEllipse90ToBezier, mgAngleArcToBezier
*/
GEOMAPI void mgEllipseToBezier(
    Point2d points[13], const Point2d& center, double rx, double ry);

//! ��һ��Բ�Ǿ���ת��Ϊ4�����α���������
/*! ��4�α��������߰���ʱ�뷽��ӵ�һ���޵��������ޣ�ÿ��4���㣬
    ��һ�εĵ����Ϊ[0,1,2,3]������ε������ơ�
    \ingroup _GEOMAPI_CURVE_
    \param[out] points ���������ߵĿ��Ƶ㣬ÿ��4���㣬��16����
    \param[in] rect ������򣬹淶������
    \param[in] rx X�����Բ�ǰ뾶���Ǹ���
    \param[in] ry Y�����Բ�ǰ뾶���Ǹ���
    \see mgEllipseToBezier
*/
GEOMAPI void mgRoundRectToBeziers(
    Point2d points[16], const Box2d& rect, double rx, double ry);

//! ��һ����Բ��ת��Ϊ������α���������
/*! 4�����α����������ǰ���ʱ�뷽��ӵ�һ���޵������������ӣ�ÿһ��4���㣬
    ��һ��������һ�����غ���+X���ϵ�(rx, 0)��
    \ingroup _GEOMAPI_CURVE_
    \param[out] points ���������ߵĿ��Ƶ㣬16����
    \param[in] center ��Բ��
    \param[in] rx �볤��ĳ���
    \param[in] ry �����ĳ��ȣ�Ϊ0��ȡΪrx
    \param[in] startAngle ��ʼ�Ƕȣ����ȣ������+X�ᣬ��ʱ��Ϊ��
    \param[in] sweepAngle ת�ǣ����ȣ��������ʼ�Ƕȣ���ʱ��Ϊ��
    \return �����Ŀ��Ƶ���������С��4����������д���
    \see mgBezier4P, mgEllipse90ToBezier, mgEllipseToBezier, mgArc3P
*/
GEOMAPI int mgAngleArcToBezier(
    Point2d points[16], const Point2d& center, double rx, double ry,
    double startAngle, double sweepAngle);

//! ������㡢����һ����յ㣬����Բ������
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in] start Բ�������
    \param[in] point ���ϵ�һ��
    \param[in] end Բ�����յ�
    \param[out] center Բ��
    \param[out] radius �뾶
    \param[out] startAngle �����ʼ�Ƕȣ�ΪNULL����Ըò���
    \param[out] sweepAngle ���Բ��ת�ǣ���ʱ��Ϊ����ΪNULL����Ըò���
    \return �Ƿ����ɹ�
    \see mgArcTan, mgArcBulge, mgAngleArcToBezier
*/
GEOMAPI bool mgArc3P(
    const Point2d& start, const Point2d& point, const Point2d& end,
    Point2d& center, double& radius,
    double* startAngle = NULL, double* sweepAngle = NULL);

//! ������㡢�յ��������򣬼���Բ������
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in] start Բ�������
    \param[in] end Բ�����յ�
    \param[in] vecTan Բ������㴦������ʸ��
    \param[out] center Բ��
    \param[out] radius �뾶
    \param[out] startAngle �����ʼ�Ƕȣ�ΪNULL����Ըò���
    \param[out] sweepAngle ���Բ��ת�ǣ���ʱ��Ϊ����ΪNULL����Ըò���
    \return �Ƿ����ɹ�
    \see mgArc3P, mgArcBulge, mgAngleArcToBezier
*/
GEOMAPI bool mgArcTan(
    const Point2d& start, const Point2d& end, const Vector2d& vecTan,
    Point2d& center, double& radius,
    double* startAngle = NULL, double* sweepAngle = NULL);

//! �����Һ͹��߼���Բ������
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in] start Բ�������
    \param[in] end Բ�����յ�
    \param[in] bulge ���ߣ�����Ϊ��ʱ�뷽�򣬸���Ϊ˳ʱ�뷽��
    \param[out] center Բ��
    \param[out] radius �뾶
    \param[out] startAngle �����ʼ�Ƕȣ�ΪNULL����Ըò���
    \param[out] sweepAngle ���Բ��ת�ǣ���ʱ��Ϊ����ΪNULL����Ըò���
    \return �Ƿ����ɹ�
    \see mgArc3P, mgArcTan, mgAngleArcToBezier
*/
GEOMAPI bool mgArcBulge(
    const Point2d& start, const Point2d& end, double bulge,
    Point2d& center, double& radius,
    double* startAngle = NULL, double* sweepAngle = NULL);

//! ������Խ��߷�����
/*! ���Խ��߷�����������ʾ: \n
    ������| b0������c0������������| \n
    A��=��| a0������b1������c1����| \n
    ������|����..������..����.. ��| \n
    ������|������a[n-2]����b[n-1] | \n
    A * (x,y) = (rx,ry)

    \ingroup _GEOMAPI_BASIC_
    \param[in] n �������������СΪ2
    \param[in] a ϵ�������е���Խ���Ԫ�����飬a[0..n-2]
    \param[in,out] b ϵ�������е��жԽ���Ԫ�����飬b[0..n-1]���ᱻ�޸�
    \param[in] c ϵ�������е��ҶԽ���Ԫ�����飬c[0..n-2]
    \param[in,out] vs ���뷽����Ⱥ��ұߵ���֪n��ʸ�������������δ֪ʸ��
    \return �Ƿ����ɹ���ʧ��ԭ������ǲ����������ϵ�����������ռ�Ŷ����ֳ���
    \see mgGaussJordan
*/
GEOMAPI bool mgTriEquations(
    Int32 n, double *a, double *b, double *c, Vector2d *vs);

//! Gauss-Jordan��������Է�����
/*!
    \ingroup _GEOMAPI_BASIC_
    \param[in] n �������������СΪ2
    \param[in,out] mat ϵ������nά���󣬻ᱻ�޸�
    \param[in,out] vs ���뷽����Ⱥ��ұߵ���֪n��ʸ�������������δ֪ʸ��
    \return �Ƿ����ɹ���ʧ��ԭ������ǲ����������ϵ�����������ռ�Ŷ����ֳ���
    \see mgTriEquations
*/
GEOMAPI bool mgGaussJordan(Int32 n, double *mat, Vector2d *vs);

//! ���β����������ߵĶ˵�����
//! \see mgCubicSplines
enum kCubicSplinesFlags
{
    kCubicTan1 = 1,         //!< ��ʼ�гֶ�
    kCubicArm1 = 2,         //!< ��ʼ���۶�
    kCubicTan2 = 4,         //!< ��ֹ�гֶ�
    kCubicArm2 = 8,         //!< ��ֹ���۶�
    kCubicLoop = 16,        //!< �պ�, �и�ֵʱ�����������ֵ
};

//! �������β����������ߵ���ֵ�����ʸ��
/*! ���β����������ߵķֶ����߷���Ϊ��\n
    P[i](t) = knots[i] + knotVectors[i] * t \n
    ������+ (3*(knots[i+1] - knots[i]) - 2 * knotVectors[i] - knotVectors[i+1]) * t^2 \n
    ������+ (2*(knots[i] - knots[i+1]) + knotVectors[i] + knotVectors[i+1]) * t^3 \n
    ���� 0 �� t �� 1

    \ingroup _GEOMAPI_CURVE_
    \param[in] n ��ֵ��ĵ���
    \param[in] knots ��ֵ���������飬Ԫ�ظ���Ϊn
    \param[out] knotVectors ��ֵ�����ʸ�����飬Ԫ�ظ���Ϊn�����������ڴ�
    \param[in] flag ���߽߱��������� kCubicSplinesFlags ����ֵ��϶��ɡ�\n
        ָ�� kCubicTan1 ʱ, knotVectors[0]����ָ����Ч����ʸ����\n
        ָ�� kCubicTan2 ʱ, knotVectors[n-1]����ָ����Ч����ʸ����\n
        ָ�� kCubicLoop ʱ��knots����ĩ��ֵ�㲻���غϣ������н���ĩ��ֵ����Ϊ�������㡣
    \param[in] tension ����ϵ����0��coeff��1, Ϊ1ʱC2������, Ϊ0ʱ������
    \return �Ƿ����ɹ�
    \see kCubicSplinesFlags, mgFitCubicSpline, mgCubicSplinesBox
*/
GEOMAPI bool mgCubicSplines(
    Int32 n, const Point2d* knots, Vector2d* knotVectors,
    UInt32 flag = 0, double tension = 1.0);

//! �������������ߵ�һ�����ϲ�ֵ�õ���͵�����
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in] n �����������ߵ���ֵ��ĵ���
    \param[in] knots ��ֵ���������飬Ԫ�ظ���Ϊn
    \param[in] knotVectors ��ֵ�����ʸ�����飬Ԫ�ظ���Ϊn
    \param[in] i �ֶ�������ţ���0��(n-2)֮�䣬��������Ǳպ����������ȡ��(n-1)
    \param[in] t �ֶ����ߺ�����������0��1֮��
    \param[out] fitPt ��͵����꣬��i�������ϲ���t��Ӧ����������
    \see mgCubicSplines, mgCubicSplineToBezier
*/
GEOMAPI void mgFitCubicSpline(
    Int32 n, const Point2d* knots, const Vector2d* knotVectors,
    Int32 i, double t, Point2d& fitPt);

//! �õ������������ߵķֶα��������߶ο��Ƶ�
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in] n �����������ߵ���ֵ��ĵ���
    \param[in] knots ��ֵ���������飬Ԫ�ظ���Ϊn
    \param[in] knotVectors ��ֵ�����ʸ�����飬Ԫ�ظ���Ϊn
    \param[in] i �ֶ�������ţ���0��(n-2)֮�䣬��������Ǳպ����������ȡ��(n-1)
    \param[out] points ���������߶εĿ��Ƶ㣬4����
    \see mgCubicSplines, mgFitCubicSpline
*/
GEOMAPI void mgCubicSplineToBezier(
    Int32 n, const Point2d* knots, const Vector2d* knotVectors,
    Int32 i, Point2d points[4]);

//! ���������������ߵ���ֵ��������ҳ�
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in,out] n ��ֵ��ĵ�����������غϵ������ʵ�ʵ���
    \param[in,out] knots ��ֵ���������飬Ԫ�ظ���Ϊn�����غϵ����ɾ��������
    \param[in] sgm ���Ʋ�����>0��һ��ȡ1.5
    \param[in] tol �����ݲ�ֵ�������ж��غϵ�
    \param[out] sigma �淶������ϵ����= ���Ʋ��� / ƽ���ҳ�
    \param[out] hp �ҳ����飬Ԫ�ظ���Ϊn-1��n�����������ڴ�
    \param[out] knotVectors ��ֵ���f"(x_i)/sigma^2��Ԫ�ظ���Ϊn�����������ڴ�
    \return �Ƿ����ɹ�
    \see mgFitClampedSpline
*/
GEOMAPI bool mgClampedSplines(
    Int32& n, Point2d* knots, double sgm, double tol, double& sigma,
    double* hp, Vector2d* knotVectors);

//! �������������ߵ�һ�����ϲ�ֵ�õ���͵�����
/*!
    \ingroup _GEOMAPI_CURVE_
    \param[in] knots ��ֵ����������
    \param[in] i �ֶ�������ţ���0��(��ֵ��ĵ���-1)֮��
    \param[in] t �ֶ����ߺ�����������0��hp[i]֮��
    \param[in] sigma �淶������ϵ��
    \param[in] hp �ҳ�����
    \param[in] knotVectors ��ֵ���f"(x_i)/sigma^2����
    \param[out] fitPt ��͵����꣬��i�������ϲ���t��Ӧ����������
    \see mgClampedSplines
*/
GEOMAPI void mgFitClampedSpline(
    const Point2d* knots, Int32 i, double t, double sigma,
    const double* hp, const Vector2d* knotVectors, Point2d& fitPt);

_GEOM_END
#endif // __GEOMETRY_FITCURVE_H_