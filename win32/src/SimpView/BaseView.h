// BaseView.h : interface of the CBaseView class
//
#pragma once

#include "RandomShape.h"
#include <graphwin.h>

class CBaseView : public CWnd
{
// Construction
public:
	CBaseView();
	virtual ~CBaseView();

    MgShapes*       m_shapes;           // 图形数据
    GiGraphWin*     m_graph;	        // 图形系统对象

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL
	virtual void DrawAll(GiGraphics* gs);
	virtual void OnDynDraw(GiGraphics* gs);
	virtual void OnZoomed();

// Implementation
protected:
    SIZE            m_pan;              // 动态平移显示的偏移

private:
    COLORREF        m_bkColor;	        // 窗口背景颜色
    bool            m_gdip;             // 是否使用GDI+显示

// Generated message map functions
protected:
	//{{AFX_MSG(CBaseView)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnUpdateViewGray(CCmdUI* pCmdUI);
	afx_msg void OnViewGray();
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
