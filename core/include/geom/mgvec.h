//! \file mgvec.h
//! \brief �����άʸ���� Vector2d
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_VECTOR_H_
#define __GEOMETRY_VECTOR_H_

#include "mgtol.h"

_GEOM_BEGIN

class Matrix2d;

//! ��άʸ����
/*!
    ��������������άƽ���Ͼ��з���ͳ��ȵ�ʸ��������x��y�����������
    \ingroup _GEOM_CLASS_
*/
class Vector2d : public VECTOR2D
{
public:
    //! ��ʸ��(0,0)
    static const Vector2d& kIdentity()
    {
        static const Vector2d vec (0.0, 0.0);
        return vec;
    }
    
    //! X�ᵥλʸ��(1,0)
    static const Vector2d& kXAxis()
    {
        static const Vector2d vec (1.0, 0.0);
        return vec;
    }
    
    //! Y�ᵥλʸ��(0,1)
    static const Vector2d& kYAxis()
    {
        static const Vector2d vec (0.0, 1.0);
        return vec;
    }
    
    //! ����Ϊ��ʸ��
    Vector2d()
    {
        x = y = 0.0;
    }
    
    //! ����Ϊʸ��(xx, yy)
    Vector2d(double xx, double yy)
    {
        x = xx; y = yy;
    }
    
    //! �������캯��
    Vector2d(const VECTOR2D& src)
    {
        x = src.x; y = src.y;
    }

    //! ����任, ʸ�� * ����
    Vector2d operator*(const Matrix2d& m) const;

    //! ����任, ʸ�� *= ����
    Vector2d& operator*=(const Matrix2d& m);

    //! ����任, ���� * ʸ��
    friend Vector2d operator*(const Matrix2d& m, const Vector2d& v)
    {
        return v * m;
    }
    
    //! ʸ���ӷ�
    Vector2d operator+(const Vector2d& v) const
    {
        return Vector2d(x + v.x, y + v.y);
    }
    
    //! ʸ���ӷ�
    Vector2d& operator+=(const Vector2d& v)
    {
        x += v.x; y += v.y; return *this;
    }
    
    //! ʸ������
    Vector2d operator-(const Vector2d& v) const
    {
        return Vector2d(x - v.x, y - v.y);
    }
    
    //! ʸ������
    Vector2d& operator-=(const Vector2d& v)
    {
        x -= v.x; y -= v.y; return *this;
    }
    
    //! ���ظ�ʸ��
    Vector2d operator-() const
    {
        return Vector2d(-x, -y);
    }
    
    //! ʸ�����򣬼�����ʸ������Ϊ(-x, -y)
    Vector2d& negate()
    {
        x = -x; y = -y; return *this;
    }
    
    //! ��������ʸ��, ����ʱ����ת90�ȣ�Ϊ(-y, x)
    Vector2d perpVector() const
    {
        return Vector2d(-y, x);
    }
    
    //! ������, �� * ʸ��
    friend Vector2d operator*(double s, const Vector2d& v)
    {
        return Vector2d(v.x * s, v.y * s);
    }
    
    //! ������, ʸ�� * ��
    Vector2d operator*(double s) const
    {
        return Vector2d(x * s, y * s);
    }
    
    //! ������, ʸ�� *= ��
    Vector2d& operator*=(double s)
    {
        x *= s; y *= s; return *this;
    }
    
    //! ������, ʸ�� / ��
    Vector2d operator/(double s) const
    {
        s = 1.0 / s;
        return Vector2d(x * s, y * s);
    }
    
    //! ������, ʸ�� /= ��
    Vector2d& operator/=(double s)
    {
        s = 1.0 / s;
        x *= s; y *= s; return *this;
    }

    //! ��������
    Vector2d& scaleBy(double sx, double sy)
    {
        x *= sx; y *= sy; return *this;
    }
    
    //! ʸ�����, A��B
    double dotProduct(const Vector2d& v) const
    {
        return (x * v.x + y * v.y);
    }
    
    //! ʸ�����, A��B
    double operator/(const Vector2d& v) const
    {
        return dotProduct(v);
    }
    
    //! ʸ�����(0,0,z)�е�z, |A��B|
    double crossProduct(const Vector2d& v) const
    {
        return (x * v.y - y * v.x);
    }
    
    //! ʸ�����(0,0,z)�е�z, |A��B|
    double operator*(const Vector2d& v) const
    {
        return crossProduct(v);
    }    
    
    //! ʸ���Ƕ�, ��X��ļн�, [0, PI)
    /*!
        ��+X�᷽����ʱ����ת����ʸ�����ڷ���ʱΪ����˳ʱ��Ϊ��
    */
    double angle() const
    {
        double len = mgHypot(x, y);
        return len < _MGZERO ? 0.0 : acos(x / len);
    }
    
    //! ʸ���Ƕ�, ��X����ʱ�뷽��Ϊ��, [-PI, PI)
    double angle2() const
    {
        return (mgIsZero(x) && mgIsZero(y)) ? 0.0 : atan2(y, x);
    }
    
    //! ʸ���н�, [0, PI)
    /*!
        �ӱ�ʸ��������ʱ����ת����һ��ʸ�� v ���ڷ���ʱΪ����˳ʱ��Ϊ��
    */
    double angleTo(const Vector2d& v) const
    {
        double len = mgHypot(x, y) * mgHypot(v.x, v.y);
        return len < _MGZERO ? 0.0 : acos(dotProduct(v) / len);
    }
    
    //! ����ʱ�뷽��ָ��ʸ����ת��, [-PI, PI)
    double angleTo2(const Vector2d& v) const
    {
        double crossz = crossProduct(v);
        double dot = dotProduct(v);
        return (mgIsZero(dot) && mgIsZero(crossz)) ? 0.0 : atan2(crossz, dot);
    }
    
    //! ʸ������
    double length() const
    {
        return mgHypot(x, y);
    }
    
    //! ʸ�����ȵ�ƽ��
    double lengthSqrd() const
    {
        return mgSquare(x, y);
    }
    
    //! ���ص�λʸ��
    /*! �����ʸ��Ϊ��ʸ�������Ʊ�ʸ��
    */
    Vector2d unitVector() const
    {
        double len = mgHypot(x, y);
        if (len >= _MGZERO)
            return Vector2d(x / len, y / len);
        else
            return *this;
    }
    
    //! ʸ����λ��
    /*! ������ʸ���ĳ��ȸĳ�1�������ʸ��Ϊ��ʸ�����򲻸ı䱾ʸ��
        \param tol �жϵ��ݲ�õ��䳤���ݲ�
        \return �����ʸ��Ϊ��ʸ�����򷵻�false�����򷵻�true
    */
    bool normalize(const Tol& tol = Tol::gTol())
    {
        double len = mgHypot(x, y);
        bool ret = (len >= tol.equalPoint());
        if (ret)
            set(x / len, y / len);
        return ret;
    }
    
    //! �ж��Ƿ��ǵ�λʸ��
    /*! �����ʸ���ĳ��Ⱥ�1���С�ڳ����ݲ��ҲΪ��λʸ��
        \param tol �жϵ��ݲ�õ��䳤���ݲ�
        \return �����ʸ��Ϊ��λʸ�����򷵻�true�����򷵻�false
    */
    bool isUnitVector(const Tol& tol = Tol::gTol()) const
    {
        return fabs(mgHypot(x, y) - 1.0) < tol.equalPoint();
    }
    
    //! �ж��Ƿ�����ʸ��
    /*! �����ʸ���ĳ���С�ڳ����ݲ��Ϊ��ʸ��
        \param tol �жϵ��ݲ�õ��䳤���ݲ�
        \return �����ʸ��Ϊ��ʸ�����򷵻�true�����򷵻�false
    */
    bool isZeroVector(const Tol& tol = Tol::gTol()) const
    {
        return mgHypot(x, y) < tol.equalPoint();
    }
    
    //! �ж�����ʸ���Ƿ����
    bool operator==(const Vector2d& v) const
    {
        return isEqualTo(v);
    }
    
    //! �ж�����ʸ���Ƿ����
    bool operator!=(const Vector2d& v) const
    {
        return !isEqualTo(v);
    }
    
    //! ��ŷ�������ж�����ʸ���Ƿ����
    /*! �������ʸ������Ĳ�ʸ���ĳ��Ȳ�����ʸ���ݲ�����
        \param v �Ƚϵ���һ��ʸ��
        \param tol �жϵ��ݲ�õ���ʸ���ݲ�
        \return �����ȣ��򷵻�true�����򷵻�false
    */
    bool isEqualTo(const Vector2d& v, const Tol& tol = Tol::gTol()) const
    {
        return mgHypot(x - v.x, y - v.y) <= tol.equalVector();
    }
    
    //! ����Ϊʸ��(xx, yy)
    Vector2d& set(double xx, double yy)
    {
        x = xx; y = yy; return *this;
    }
    
    //! ����ʸ���ĽǶȺͳ���
    /*!
        \param angle ʸ���ĽǶȣ�����
        \param len ʸ���ĳ���
        \return ��ʸ��������
    */
    Vector2d& setAngleLength(double angle, double len)
    {
        return set(len * cos(angle), len * sin(angle));
    }
    
    //! �õ�����������������С
    /*! ���øú������Խ�ʸ��ת��ΪSIZE��CSizeֵ
        \param[out] cx ����������X�������
        \param[out] cy ����������Y�������
    */
    void get(long& cx, long& cy) const
    {
        cx = mgRound(x); cy = mgRound(y);
    }

    //! �ж��Ƿ���ָ��ʸ�����Ҳ࣬������ʱ�뷽��ת��ָ��ʸ��ʱ���
    bool isRightOf(const Vector2d& vec) const
    {
        return crossProduct(vec) > 0.0;
    }

    //! �ж��Ƿ���ָ��ʸ������࣬����˳ʱ�뷽��ת��ָ��ʸ��ʱ���
    bool isLeftOf(const Vector2d& vec) const
    {
        return crossProduct(vec) < 0.0;
    }
    
    //! �ж�����ʸ���Ƿ�ƽ��
    /*! �жϱ�ʸ������һ��ʸ���Ƿ�ƽ�У���ʸ�����κ�ʸ��ƽ��
        \param[in] vec ��һ��ʸ��
        \param[in] tol �жϵ��ݲ�õ���ʸ���ݲ�ֵ
        \return �Ƿ�ƽ��
    */
    bool isParallelTo(const Vector2d& vec, const Tol& tol = Tol::gTol()) const;
    
    //! �ж�����ʸ���Ƿ�ƽ��
    /*! �жϱ�ʸ������һ��ʸ���Ƿ�ƽ�У��������ʸ����
        ��ʸ�����κ�ʸ��ƽ��
        \param[in] vec ��һ��ʸ��
        \param[in] tol �жϵ��ݲ�õ���ʸ���ݲ�ֵ
        \param[out] nonzero ������ʸ�����Ƿ�û����ʸ��
        \return �Ƿ�ƽ��
    */
    bool isParallelTo(const Vector2d& vec, const Tol& tol, bool& nonzero) const;
    
    //! �ж�����ʸ���Ƿ�ͬ��
    /*! �жϱ�ʸ������һ��ʸ���Ƿ�ͬ����ʸ�����κ�ʸ������ͬ��
        \param[in] vec ��һ��ʸ��
        \param[in] tol �жϵ��ݲ�õ���ʸ���ݲ�ֵ
        \return �Ƿ�ͬ��
    */
    bool isCodirectionalTo(const Vector2d& vec, const Tol& tol = Tol::gTol()) const;
    
    //! �ж�����ʸ���Ƿ�ͬ��
    /*! �жϱ�ʸ������һ��ʸ���Ƿ�ͬ�򣬲������ʸ����
        ��ʸ�����κ�ʸ������ͬ��
        \param[in] vec ��һ��ʸ��
        \param[in] tol �жϵ��ݲ�õ���ʸ���ݲ�ֵ
        \param[out] nonzero ������ʸ�����Ƿ�û����ʸ��
        \return �Ƿ�ͬ��
    */
    bool isCodirectionalTo(const Vector2d& vec, const Tol& tol, bool& nonzero) const;
    
    //! �ж�����ʸ���Ƿ���
    /*! �жϱ�ʸ������һ��ʸ���Ƿ�����ʸ�����κ�ʸ����������
        \param[in] vec ��һ��ʸ��
        \param[in] tol �жϵ��ݲ�õ���ʸ���ݲ�ֵ
        \return �Ƿ���
    */
    bool isOppositeTo(const Vector2d& vec, const Tol& tol = Tol::gTol()) const;
    
    //! �ж�����ʸ���Ƿ���
    /*! �жϱ�ʸ������һ��ʸ���Ƿ��򣬲������ʸ����
        ��ʸ�����κ�ʸ����������
        \param[in] vec ��һ��ʸ��
        \param[in] tol �жϵ��ݲ�õ���ʸ���ݲ�ֵ
        \param[out] nonzero ������ʸ�����Ƿ�û����ʸ��
        \return �Ƿ���
    */
    bool isOppositeTo(const Vector2d& vec, const Tol& tol, bool& nonzero) const;
    
    //! �ж�����ʸ���Ƿ�ֱ
    /*! �жϱ�ʸ������һ��ʸ���Ƿ�ƽ�У���ʸ�����κ�ʸ��������ֱ
        \param[in] vec ��һ��ʸ��
        \param[in] tol �жϵ��ݲ�õ���ʸ���ݲ�ֵ
        \return �Ƿ�ֱ
    */
    bool isPerpendicularTo(const Vector2d& vec, const Tol& tol = Tol::gTol()) const;
    
    //! �ж�����ʸ���Ƿ�ֱ
    /*! �жϱ�ʸ������һ��ʸ���Ƿ�ƽ�У��������ʸ����
        ��ʸ�����κ�ʸ��������ֱ
        \param[in] vec ��һ��ʸ��
        \param[in] tol �жϵ��ݲ�õ���ʸ���ݲ�ֵ
        \param[out] nonzero ������ʸ�����Ƿ�û����ʸ��
        \return �Ƿ�ֱ
    */
    bool isPerpendicularTo(const Vector2d& vec, const Tol& tol, bool& nonzero) const;

    //! ��ʸ��ͶӰ��ʸ��xAxis�ϵĴ�ֱ����
    /*! ��xAxis����ʱ�뷽��ʱ������ֵ��˳ʱ���򷵻ظ�ֵ
        \param[in] xAxis ͶӰ����ʸ��
        \return ��ֱͶӰ���룬������
    */
    double distanceToVector(const Vector2d& xAxis) const;
    
    //! ��ʸ����ʸ��xAxis�ϵ�ͶӰ����
    /*! ͶӰʸ�� = xAxis * ͶӰ���� \n
        ͶӰ������0��1֮��ʱ��ʾͶӰʸ����xAxis�ڵ�һ����
        \param[in] xAxis ͶӰ����ʸ��
        \return ͶӰ������������
    */
    double projectScaleToVector(const Vector2d& xAxis) const;
    
    //! ��ʸ����ʸ��xAxis�ϵ�ͶӰʸ���ʹ�ֱʸ��
    /*! ����ʸ��ͶӰ��xAxis������ͶӰ������
        ��ͶӰʸ�� = xAxis * ͶӰ��������ʸ�� = proj + perp
        \param[in] xAxis ͶӰ����ʸ��
        \param[out] proj ��ͶӰʸ��
        \param[out] perp ��ֱͶӰʸ��
        \return ͶӰ������������
    */
    double projectResolveVector(const Vector2d& xAxis, 
        Vector2d& proj, Vector2d& perp) const;
    
    //! ʸ���ֽ�
    /*! ����ʸ�������������ߵķ���ʸ���Ͻ���ʸ���ֽ�, ��ʸ�� = u*uAxis+v*vAxis
        \param[in] uAxis u��ʸ��
        \param[in] vAxis v��ʸ��
        \param[out] u ��u���ϵ�ʸ������ϵ����ʸ������ = uAxis * u
        \param[out] v ��v���ϵ�ʸ������ϵ����ʸ������ = vAxis * v
        \return �Ƿ����ɹ���uAxis��vAxis����ʱʧ��
    */
    bool resolveVector(const Vector2d& uAxis, const Vector2d& vAxis, 
        double& u, double& v) const;
};

_GEOM_END
#endif // __GEOMETRY_VECTOR_H_