//! \file mgtol.h
//! \brief �����ݲ��� Tol
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_MGTOL_H_
#define __GEOMETRY_MGTOL_H_

#include "mgdef.h"

_GEOM_BEGIN

//! �ݲ���
/*!
    \ingroup _GEOM_CLASS_
    �ݲ��ຬ�г����ݲ��ʸ���ݲ\n
    �����ݲ��ʾ����С�ڸ�ֵ����Ϊ���㳤�ȣ����������С�ڸ�ֵ����Ϊ�غϡ�\n
    ʸ���ݲ��ʾ�������ȽǶ�С�ڸ�ֵ����Ϊ����ȣ�����ʸ���ݲ�һ���С��
    �ʶ���ʸ���ݲ�a����a��sin(a)��tan(a)��cos(a)��1��
*/
class Tol
{
public:
    //! ȫ��ȱʡ�ݲ�
    /*! ���ݲ�����ѧ���ο��кܶຯ����Ĭ���ݲ�����޸ĸö�����ݲ�ֵ
    */
    static Tol& gTol()
    {
        static Tol tol;
        return tol;
    }
    
    //! ��С�ݲ�
    /*! ���ݲ�ĳ����ݲ�ֵ��ʸ���ݲ�ֵ��Ϊ1e-10
    */
    static const Tol& minTol()
    {
        static const Tol tol(0, 0);
        return tol;
    }
    
    //! ����Ĭ���ݲ�
    /*! Ĭ�Ϲ��캯��������ĳ����ݲ�ֵΪ1e-7��ʸ���ݲ�ֵΪ1e-4
    */
    Tol() : mTolPoint(1e-7), mTolVector(1e-4)
    {
    }
    
    //! �����ݲ��
    /*! ��������ݲ�ֵС��1e-10����ȡ��С�ݲ�ֵ1e-10
        \param tolPoint �����ݲ�ֵ������
        \param tolVector ʸ���ݲ�ֵ��������һ��ȡС��0.1����
    */
    Tol(double tolPoint, double tolVector)
    {
        setEqualPoint(tolPoint);
        setEqualVector(tolVector);
    }
    
    //! ���س����ݲ�
    double equalPoint() const
    {
        return mTolPoint;
    }
    
    //! ����ʸ���ݲ�
    double equalVector() const
    {
        return mTolVector;
    }
    
    //! ���ó����ݲ�
    /*! ��������ݲ�ֵС��1e-10����ȡ��С�ݲ�ֵ1e-10
        \param tol �����ݲ�ֵ������
    */
    void setEqualPoint(double tol)
    {
        if (tol < 1e-10)
            tol = 1e-10;
        mTolPoint = tol;
    }
    
    //! ����ʸ���ݲ�
    /*! ��������ݲ�ֵС��1e-10����ȡ��С�ݲ�ֵ1e-10
        \param tol ʸ���ݲ�ֵ��������һ��ȡС��0.1����
    */
    void setEqualVector(double tol)
    {
        if (tol < 1e-10)
            tol = 1e-10;
        mTolVector = tol;
    }
    
private:
    double  mTolPoint;      //!< �����ݲ�
    double  mTolVector;     //!< ʸ���ݲ�
};

_GEOM_END
#endif // __GEOMETRY_MGTOL_H_