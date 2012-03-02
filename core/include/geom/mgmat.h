//! \file mgmat.h
//! \brief �����ά��α任������ Matrix2d
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_MATRIX_H_
#define __GEOMETRY_MATRIX_H_

#include "mgpnt.h"

_GEOM_BEGIN

//! ��ά��α任������
/*!
    \ingroup _GEOM_CLASS_
    
    �任������Matrix���ڶ�άͼ�εķ���任������ M ����ʽΪ: \n
    ����e0x��e0y��0 \n
    ����e1x��e1y��0 \n
    ����dx����dy��1 \n
    ���о��� A: \n
    ����e0x��e0y \n
    ����e1x��e1y \n
    ��Ϊ M �����Բ��֣��������Ƕ�ͼ�ν�����������ת���Գƺʹ��еȱ任��\n
    ������ T (dx, dy) ��Ϊ M ��ƽ�Ʋ��֣��������Ƕ�ͼ�ν���ƽ�Ʊ任��\n
    
    Point�ĵ�pnt�Ķ�Ӧ�任��Ϊ P x M����ʸ�� P = (pnt.x, pnt.y, 1.0) \n
    Vector��ʸ��vec�Ķ�Ӧ�任ʸ��Ϊ V x M��M ��ƽ�Ʋ��ֲ�������㡣\n
    
    ÿ������ M ��Ӧһ������ϵ��������ԭ��Ϊ(dx, dy)��������Ϊʸ��(e0x, e0y)��
    (e1x, e1y)��M Ϊ��(0,0)(1,0)(0,1)ӳ�䵽(dx, dy)(e0x, e0y)(e1x, e1y)�ľ���
*/
class Matrix2d : public MATRIX2D
{
public:
    //! ��λ����
    static const Matrix2d& kIdentity()
    {
        static const Matrix2d mat;
        return mat;
    }
    
    //! ����Ϊ��λ����
    Matrix2d();
    
    //! �������캯��
    Matrix2d(const MATRIX2D& src);
    
    //! ����Ԫ�ع���
    Matrix2d(double _m11, double _m12, double _m21, double _m22,
        double _dx, double _dy);
    
    //! ������������ʸ����ԭ�㹹��
    /*! ����ھ�������ϵ������µ�����ϵ����
        ���������������ʸ�����������������������ϵ������Ϊ��������ϵ
        \param e0 X��һ����λ��ʸ��
        \param e1 Y��һ����λ��ʸ��
        \param origin ������ϵ��ԭ��
    */
    Matrix2d(const Vector2d& e0, const Vector2d& e1,
        const Point2d& origin);
    
    //! ����˷�
    Matrix2d operator*(const Matrix2d& mat) const;
    
    //! ����˷�
    Matrix2d& operator*=(const Matrix2d& mat);
    
    //! ���һ������leftSide * (*this)
    Matrix2d& preMultBy(const Matrix2d& leftSide);
    
    //! �ҳ�һ������(*this) * rightSide
    Matrix2d& postMultBy(const Matrix2d& rightSide);
    
    //! ����Ϊ��������ĳ˻� (m1 * m2)
    Matrix2d& setToProduct(const Matrix2d& m1, const Matrix2d& m2);
    
    //! �Զ������о���任
    /*!
        \param[in] count ��ĸ���
        \param[in,out] points Ҫ�任�ĵ�����飬Ԫ�ظ���Ϊcount
    */
    void TransformPoints(Int32 count, Point2d* points) const;

    //! �Զ��ʸ�����о���任
    /*! ��ʸ�����о���任ʱ�������ƽ�Ʒ������ֲ�������
        \param[in] count ʸ���ĸ���
        \param[in,out] vectors Ҫ�任��ʸ�������飬Ԫ�ظ���Ϊcount
    */
    void TransformVectors(Int32 count, Vector2d* vectors) const;
    
    //! ����ʽֵ
    double det() const;
    
    //! ����Ϊ�����
    /*!
        \return �Ƿ���棬���������������Ϊ��λ����
    */
    bool invert();
    
    //! ���������
    Matrix2d inverse() const;
    
    //! �жϾ����Ƿ����
    bool isInvertible() const;
    
    //! ������С
    double scale() const;
    
    //! X������С
    double scaleX() const;
    
    //! Y������С
    double scaleY() const;
    
    //! �ж����������Ƿ����
    bool operator==(const Matrix2d& mat) const;
    
    //! �ж����������Ƿ����
    bool operator!=(const Matrix2d& mat) const;
    
    //! ��ŷ�������ж����������Ƿ���ȣ����жϾ������ʸ���Ƿ����
    bool isEqualTo(const Matrix2d& mat, const Tol& tol = Tol::gTol()) const;

    //! �ж��Ƿ�Ϊ��λ����
    bool isIdentity() const;

    //! �жϾ����������ʸ���Ƿ�ֱ�ˮƽ�ʹ�ֱ
    bool isOrtho() const;
    
    //! �õ���������ת������ɷ�
    /*!
        \param[out] scaleX �����X�����������
        \param[out] scaleY �����Y�����������
        \param[out] angle �������ת�Ƕȣ�����
        \param[out] isMirror �������Ƿ��жԳƳɷ�
        \param[out] reflex �����еĶԳ��᷽��ʸ��(����жԳƳɷ�)
        \return �Ƿ����ɹ��������X���Y�᲻��ֱ��ʧ��
    */
    bool isConformal(double& scaleX, double& scaleY, double& angle,
        bool& isMirror, Vector2d& reflex) const;
    
    //! ����Ϊԭ��Ϊorigin��������ʸ��Ϊe0��e1������ϵ
    Matrix2d& setCoordSystem(
        const Vector2d& e0, const Vector2d& e1, const Point2d& origin);
    
    //! �õ�����ϵ��ԭ��origin��������ʸ��e0��e1
    void getCoordSystem(
        Vector2d& e0, Vector2d& e1, Point2d& origin) const;
    
    //! ����ԭ��Ϊorigin��������ʸ��Ϊe0��e1������ϵ
    static Matrix2d coordSystem(
        const Vector2d& e0, const Vector2d& e1, const Point2d& origin);
    
    //! ���ظ���ԭ�㡢��������ת�Ƕȵ�����ϵ
    /*!
        \param origin ������ϵ��ԭ������
        \param scaleX X��ı���ϵ��
        \param scaleY Y��ı���ϵ����Ϊ0��ȡΪscaleX
        \param angle X�����ת�Ƕȣ�����
        \return ������ϵ�ľ���
    */
    static Matrix2d coordSystem(const Point2d& origin, 
        double scaleX, double scaleY = 0.0, double angle = 0.0);
    
    //! ����Ϊ��λ����
    Matrix2d& setToIdentity();
    
    //! ���þ���Ԫ��
    Matrix2d& set(double _m11, double _m12, double _m21, double _m22,
        double _dx, double _dy);
    
    //! ����Ϊƽ�Ʊ任����
    /*!
        \param vec ƽ��ʸ��
        \return �ı��ı����������
    */
    Matrix2d& setToTranslation(const Vector2d& vec);
    
    //! ����Ϊ��һ��Ϊ���ĵ���ת�任����
    /*!
        \param angle ��ת�Ƕȣ����ȣ���ʱ��Ϊ��
        \param center ��ת���ĵ�
        \return �ı��ı����������
    */
    Matrix2d& setToRotation(double angle, 
        const Point2d& center = Point2d::kOrigin());
    
    //! ����Ϊ��һ��Ϊ���ĵķ����任����
    /*!
        \param scale ��������
        \param center �������ĵ�
        \return �ı��ı����������
    */
    Matrix2d& setToScaling(double scale, 
        const Point2d& center = Point2d::kOrigin());
    
    //! ����Ϊ��һ��Ϊ���ĵķ����任����
    /*!
        \param scaleX ��X�����ϵķ�������
        \param scaleY ��Y�����ϵķ������������Ϊ0��ȡΪscaleX
        \param center �������ĵ�
        \return �ı��ı����������
    */
    Matrix2d& setToScaling(double scaleX, double scaleY, 
        const Point2d& center = Point2d::kOrigin());
    
    //! ����Ϊ����һ��ԳƵı任����
    /*!
        \param pnt �Գ����ĵ�
        \return �ı��ı����������
    */
    Matrix2d& setToMirroring(const Point2d& pnt = Point2d::kOrigin());
    
    //! ����Ϊ��ֱ��(pnt,dir)Ϊ�����ߵĶԳƱ任����
    /*!
        \param pnt �Գ��������ϵ�һ��
        \param dir �Գ������ߵķ���ʸ��
        \return �ı��ı����������
    */
    Matrix2d& setToMirroring(const Point2d& pnt, const Vector2d& dir);
    
    //! ����Ϊ���б任����
    /*!
        \param sx ��X�����ϵĴ��б���
        \param sy ��Y�����ϵĴ��б��������Ϊ0��ȡΪsx
        \param pnt ���л��㣬�ڸõ��ϵĵ�任��λ�ò���
        \return �ı��ı����������
    */
    Matrix2d& setToShearing(double sx, double sy, 
        const Point2d& pnt = Point2d::kOrigin());
    
    //! �õ�ƽ�Ʊ任����
    /*!
        \param vec ƽ��ʸ��
        \return �µı任����
    */
    static Matrix2d translation(const Vector2d& vec);
    
    //! �õ���һ��Ϊ���ĵ���ת�任����
    /*!
        \param angle ��ת�Ƕȣ����ȣ���ʱ��Ϊ��
        \param center ��ת���ĵ�
        \return �µı任����
    */
    static Matrix2d rotation(double angle, 
        const Point2d& center = Point2d::kOrigin());
    
    //! �õ���һ��Ϊ���ĵķ����任����
    /*!
        \param scale ��������
        \param center �������ĵ�
        \return �µı任����
    */
    static Matrix2d scaling(double scale, 
        const Point2d& center = Point2d::kOrigin());
    
    //! �õ���һ��Ϊ���ĵķ����任����
    /*!
        \param scaleX ��X�����ϵķ�������
        \param scaleY ��Y�����ϵķ������������Ϊ0��ȡΪscaleX
        \param center �������ĵ�
        \return �µı任����
    */
    static Matrix2d scaling(double scaleX, double scaleY, 
        const Point2d& center = Point2d::kOrigin());
    
    //! �õ�����һ��ԳƵı任����
    /*!
        \param pnt �Գ����ĵ�
        \return �µı任����
    */
    static Matrix2d mirroring(const Point2d& pnt = Point2d::kOrigin());
    
    //! �õ���ֱ��(pnt,dir)Ϊ�����ߵĶԳƱ任����
    /*!
        \param pnt �Գ��������ϵ�һ��
        \param dir �Գ������ߵķ���ʸ��
        \return �µı任����
    */
    static Matrix2d mirroring(const Point2d& pnt, const Vector2d& dir);
    
    //! �õ����б任����
    /*!
        \param sx ��X�����ϵĴ��б���
        \param sy ��Y�����ϵĴ��б��������Ϊ0��ȡΪsx
        \param pnt ���л��㣬�ڸõ��ϵĵ�任��λ�ò���
        \return �µı任����
    */
    static Matrix2d shearing(double sx, double sy, 
        const Point2d& pnt = Point2d::kOrigin());
};

_GEOM_END
#endif // __GEOMETRY_MATRIX_H_