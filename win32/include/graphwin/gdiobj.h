//! \file gdiobj.h
//! \brief �����ʵ��GDI��Դ������ KGDIObject

#ifndef __GDIOBJ_H_
#define __GDIOBJ_H_

//! GDI��Դ������
class KGDIObject
{
public:
    //! Ĭ�Ϲ��캯��
    KGDIObject() : m_hOld(NULL), m_hdc(NULL), m_hObj(NULL), m_bCreated(false)
    {
    }
    
    //! ָ����Դ����Ĺ��캯��
    /*! ���hdc��hObjΪ�գ��򲻽���Դѡ���豸��������������ֵ
        \param hdc �豸������ľ��
        \param hObj GDI��Դ��������续�ʡ���ˢ��������Դ���
        \param bCreated ������GDI��Դ����Ƿ���Ҫ�Զ��ͷ�
    */
    KGDIObject(HDC hdc, HGDIOBJ hObj, bool bCreated = true)
        : m_hOld(NULL), m_hdc(hdc), m_hObj(hObj), m_bCreated(bCreated)
    {
        if (hObj != NULL && hdc != NULL)
            m_hOld = ::SelectObject(hdc, hObj);
    }
    
    //! �����������Զ��ͷ�
    ~KGDIObject()
    {
        Detach();
    }
    
    //! ָ���µ�GDI��Դ���ͷ�ԭ������Դ����
    /*!
        \param hObj GDI��Դ��������续�ʡ���ˢ��������Դ���
        \param bCreated ������GDI��Դ����Ƿ���Ҫ�Զ��ͷ�
    */
    void Attach(HGDIOBJ hObj, bool bCreated = true)
    {
        if (hObj == m_hObj)
            return;
        Detach();
        m_hObj = hObj;
        m_bCreated = bCreated;
        if (hObj != NULL && m_hdc != NULL)
            m_hOld = ::SelectObject(m_hdc, hObj);
    }
    
    //! �ͷŶ���Դ������
    /*! ����ڹ����Attach������ָ��bCreatedΪtrue�����Զ�ɾ��GDI��Դ
    */
    void Detach()
    {
        if (m_hObj != NULL)
        {
            if (m_hdc != NULL)
                ::SelectObject(m_hdc, m_hOld);
            if (m_bCreated)
                ::DeleteObject(m_hObj);
            m_hObj = NULL;
            m_hOld = NULL;
        }
    }
    
    //! ����GDI��Դ���
    HGDIOBJ GetHandle() const
    {
        return m_hObj;
    }
    
    //! �����µ��豸������, ��������δ����GDI��Դʱʹ��
    void SetHDC(HDC hdc)
    {
        if (m_hObj == NULL)
            m_hdc = hdc;
    }

private:
    HGDIOBJ     m_hOld;
    HDC         m_hdc;
    HGDIOBJ     m_hObj;
    bool        m_bCreated;
};

#endif // __GDIOBJ_H_