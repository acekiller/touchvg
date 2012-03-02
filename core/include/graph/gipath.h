//! \file gipath.h
//! \brief ����ʸ��·���� GiPath
// Copyright (c) 2004-2012, Zhang Yungui
// License: GPL, https://github.com/rhcad/graph2d

#ifndef __GEOMETRY_PATH_H_
#define __GEOMETRY_PATH_H_

#include <mgpnt.h>

_GEOM_BEGIN

//! ʸ��·����
/*!
    \ingroup _GRAPH_INTERFACE_
    \see GiGraphics::drawPath
*/
class GiPath
{
public:
    //! Ĭ�Ϲ��캯��
    GiPath();

    //! �������캯��
    GiPath(const GiPath& src);

    //! ���캯����ָ���ڵ�����
    /*!
        \param count �ڵ����
        \param points �ڵ��������飬Ԫ�ظ���Ϊcount
        \param types �ڵ��������飬Ԫ�ظ���Ϊcount������ PT_LINETO ��ֵ
    */
    GiPath(int count, const Point2d* points, const UInt8* types);

    //! ��������
    virtual ~GiPath();

    //! ��ֵ����������
    GiPath& operator=(const GiPath& src);
    
    //! ���߹ս�Բ�ǻ�
    /*!
        \param count ���߶�����
        \param points �����������飬Ԫ�ظ���Ϊcount
        \param radius �ս����Բ�ǰ뾶
        \param closed �Ƿ�պ�
        \return �Ƿ�������·��
    */
    bool genericRoundLines(int count, const Point2d* points, 
        double radius, bool closed = false);

    //! ���ؽڵ����
    int getCount() const;

    //! ���ؽڵ���������
    const Point2d* getPoints() const;

    //! ���ؽڵ��������飬���� PT_LINETO ��ֵ
    const UInt8* getTypes() const;
    

    //! ������нڵ�
    void clear();

    //! �����нڵ������������任
    void transform(const Matrix2d& mat);

    //! ��ʼ�µ�һ��ͼԪ
    /*! ������� moveTo ����ܵ��� lineTo ��������ӻ�ͼָ��ĺ���
    */
    void startFigure();

    //! ����ƶ�����λ�õ�ָ��ڵ�
    /*! ������� moveTo ����ܵ��� lineTo ��������ӻ�ͼָ��ĺ���
        \param point ��λ��
        \return �Ƿ���ȷ���
    */
    bool moveTo(const Point2d& point);

    //! ��ӻ���ֱ�߶ε���λ�õ�ָ��ڵ�
    /*!
        \param point ֱ�߶ε��յ�λ��
        \return �Ƿ���ȷ���
    */
    bool lineTo(const Point2d& point);

    //! ��ӻ������ߵ���λ�õ�ָ��ڵ�
    /*!
        \param count ���ߵ�����������㣬����Ϊ1
        \param points ���߶������飬������㣬Ԫ�ظ���Ϊcount
        \return �Ƿ���ȷ���
    */
    bool linesTo(int count, const Point2d* points);

    //! ��ӻ��Ʊ��������ߵ���λ�õ�ָ��ڵ�
    /*!
        \param count ���߿��Ƶ�ĵ�����������㣬����Ϊ3�ı���
        \param points ���߿��Ƶ��λ�õ����飬������㣬Ԫ�ظ���Ϊcount
        \return �Ƿ���ȷ���
    */
    bool beziersTo(int count, const Point2d* points);

    //! ��ӻ�������Բ������λ�õ�ָ��ڵ�
    /*! ��Բ�������ΪͼԪ�ĵ�ǰλ�ã���ʼ������Ϊ��ĩһ��ֱ�߶εķ���\n
        ��ĩ�ڵ����� lineTo �� linesTo ��ӵ�ֱ�߶�ʱ���������ž����������á�
        \param point Բ���յ�
        \return �Ƿ���ȷ���
    */
    bool arcTo(const Point2d& point);

    //! ��ӻ�������Բ������λ�õ�ָ��ڵ�
    /*! ��Բ�������ΪͼԪ�ĵ�ǰλ�ã������м�һ�㵽��ָ���յ�
        \param point Բ���м侭����һ��
        \param end Բ���յ�
        \return �Ƿ���ȷ���
    */
    bool arcTo(const Point2d& point, const Point2d& end);

    //! ��ӱպϵ�ǰͼԪ��ָ��ڵ�
    /*!
        \return �Ƿ���ȷ���
    */
    bool closeFigure();

private:
    class Data;
    Data*   m_data;
};

_GEOM_END
#endif // __GEOMETRY_PATH_H_