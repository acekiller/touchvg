// BaseView.h : interface of the CBaseView class
//
#pragma once

#include "shape.h"

class CBaseView : public CWnd
{
// Construction
public:
	CBaseView(int shapeCount);
	virtual ~CBaseView();

    Shapes m_shapes;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	virtual void OnDraw(GiGraphics* gs);
	virtual void OnDynDraw(GiGraphics* gs);
	virtual void OnZoomed();

// Implementation
protected:
    GiTransform     m_xf;               // ����ϵ�������
	GiGraphWin*		m_gs;			    // �����ڵ�ͼ��ϵͳ����
	SIZE			m_sizePan;			// ��̬ƽ����ʾ�ľ���

private:
	COLORREF		m_crBkColor;		// ���ڱ�����ɫ
	bool			m_bGdip;

// Generated message map functions
protected:
	//{{AFX_MSG(CBaseView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateViewGdip(CCmdUI* pCmdUI);
	afx_msg void OnViewGdip();
	afx_msg void OnUpdateAntiAlias(CCmdUI* pCmdUI);
	afx_msg void OnViewAntiAlias();
	afx_msg void OnViewBkColor();
	afx_msg void OnUpdateViewScale(CCmdUI* pCmdUI);
	afx_msg void OnZoomExtent();
	afx_msg void OnZoomIn();
	afx_msg void OnZoomOut();
	afx_msg void OnPanLeft();
	afx_msg void OnPanRight();
	afx_msg void OnPanUp();
	afx_msg void OnPanDown();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

inline void CBaseView::OnDynDraw(GiGraphics*) {}
