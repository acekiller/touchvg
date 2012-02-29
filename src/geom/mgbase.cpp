// mgbase.cpp: ʵ�ֻ������㹦�ܺ���
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#include "mgbase.h"

_GEOM_BEGIN

// ����ת������ֵ��Χ[tmin, tmax)��
GEOMAPI double mgToRange(double value, double tmin, double tmax)
{
    while (value < tmin)
        value += tmax - tmin;
    while (value >= tmax)
        value -= tmax - tmin;
    return value;
}

// ʹ�Ƕ���[0, 2PI)֮��
GEOMAPI double mgTo0_2PI(double angle)
{
    return mgToRange(angle, 0.0, _M_2PI);
}

// ʹ�Ƕ���[-PI, PI)֮��
GEOMAPI double mgToPI(double angle)
{
    return mgToRange(angle, -M_PI, M_PI);
}

// �ǶȴӶ�ת��������
GEOMAPI double mgDeg2Rad(double deg)
{
    return deg * _M_D2R;
}

// �Ƕȴӻ���ת������
GEOMAPI double mgRad2Deg(double rad)
{
    return rad * _M_R2D;
}

// �ȷ���ת�����Ƕ�(��)
GEOMAPI double mgDms2Deg(double angle)
{
    int nDeg, nMin;
    int sign = 1;
    
    if (angle < 0)
    {
        sign = -1;
        angle = -angle;
    }
    else if (angle == 0)
        return 0.0;
    
    nDeg = static_cast<int>(angle);
    angle -= nDeg;
    angle += 1e-13;
    angle -= 7e-14;
    angle *= 100.0;
    nMin = static_cast<int>(angle);
    angle -= nMin;
    angle *= 100.0;
    
    return sign * (nDeg + nMin / 60.0 + angle / 3600.0);
}

// �Ƕ�(��)ת�����ȷ���
GEOMAPI double mgDeg2Dms(double angle)
{
    int nDeg, nMin;
    double dSecond;
    int sign = 1;
    
    if (angle < 0)
    {
        sign = -1;
        angle = -angle;
    }
    else if (angle == 0)
        return 0.0;
    
    nDeg = static_cast<int>(angle);
    angle -= nDeg;
    nMin = static_cast<int>(angle * 60.0);
    angle -= nMin / 60.0;
    if (nMin == 60)
    {
        nDeg++;
        nMin = 0;
    }
    dSecond = angle * 3600.0;
    if (dSecond >= 60.0)
    {
        dSecond = 0.0;
        nMin++;
        if (nMin == 60)
        {
            nDeg++;
            nMin = 0;
        }
    }
    return sign * (nDeg + nMin / 100.0 + dSecond / 10000.0);
}

// �������ǶȵĽ�ƽ���߽Ƕ�, [0, 2PI)
GEOMAPI double mgMidAngle(double fromAngle, double toAngle)
{
    fromAngle = mgTo0_2PI(fromAngle);
    toAngle = mgTo0_2PI(toAngle);
    if (!mgIsZero(fromAngle - toAngle))
    {
        if (toAngle < fromAngle)
            return mgTo0_2PI((fromAngle + toAngle + _M_2PI) / 2);
    }
    return (fromAngle + toAngle) / 2;
}

// �������Ƕȵļн�, [-PI, PI)
GEOMAPI double mgDiffAngle(double fromAngle, double toAngle)
{
    fromAngle = mgTo0_2PI(fromAngle);
    toAngle = mgTo0_2PI(toAngle);
    if (mgIsZero(fromAngle - toAngle))
        return 0.0;
    if (toAngle < fromAngle)
        toAngle += _M_2PI;
    return mgToPI(toAngle - fromAngle);
}

// �������Լ��
GEOMAPI long mgGcd(long x, long y)
{
    while (x != y)
    {
        if (x > y) x -= y;
        else y -= x;
    }
    return x;
}

// ��������. С��λ[-6��7]. eg: mgRoundReal(1.25, 1)=1.3
GEOMAPI double mgRoundReal(double value, int decimal)
{
    if (decimal < -6) decimal = -6;
    else if (decimal > 7) decimal = 7;
    long double e10n = pow(10.0L, decimal);
    long double l = floorl(e10n * value + 0.5);
    return static_cast<double>(l / e10n);
}

_GEOM_END