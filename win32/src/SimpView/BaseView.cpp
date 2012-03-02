// BaseView.cpp : implementation of the CBaseView class
//

#include "stdafx.h"
#include "resource.h"
#include "BaseView.h"
#include <gidrgdip.h>
#include <gidrgdi.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CBaseView::CBaseView(long nShapeCount)
	: m_nShapeCount(0), m_pShapes(NULL)
{
	m_sizePan.cx = m_sizePan.cy = 0;
	m_bGdip = true;
	m_crBkColor = GetSysColor(COLOR_WINDOW);

	if (m_bGdip)
		m_gs = new GiGraphGdip(m_xf);
	else
		m_gs = new GiGraphGdi(m_xf);

	if (nShapeCount > 0)
	{
		m_nShapeCount = nShapeCount;
		m_pShapes = new ShapeItem*[m_nShapeCount];
		ZeroMemory(m_pShapes, sizeof(m_pShapes[0]) * m_nShapeCount);
	}
}

CBaseView::~CBaseView()
{
	delete m_gs;

	for (int i = 0; i < m_nShapeCount; i++)
		delete m_pShapes[i];
	delete[] m_pShapes;
}

BEGIN_MESSAGE_MAP(CBaseView, CWnd)
	//{{AFX_MSG_MAP(CBaseView)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(ID_VIEW_GDIP, OnUpdateViewGdip)
	ON_COMMAND(ID_VIEW_GDIP, OnViewGdip)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ANTIALIAS, OnUpdateAntiAlias)
	ON_COMMAND(ID_VIEW_ANTIALIAS, OnViewAntiAlias)
	ON_COMMAND(ID_VIEW_BKCOLOR, OnViewBkColor)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_VIEWSCALE, OnUpdateViewScale)
	ON_COMMAND(ID_ZOOM_EXTENT, OnZoomExtent)
	ON_COMMAND(ID_VIEW_ZOOMIN, OnZoomIn)
	ON_COMMAND(ID_VIEW_ZOOMOUT, OnZoomOut)
	ON_COMMAND(ID_PAN_LEFT, OnPanLeft)
	ON_COMMAND(ID_PAN_RIGHT, OnPanRight)
	ON_COMMAND(ID_PAN_UP, OnPanUp)
	ON_COMMAND(ID_PAN_DOWN, OnPanDown)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CBaseView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

BOOL CBaseView::OnEraseBkgnd(CDC*) 
{
	return TRUE;							// ��OnPaint�л��������
}

void CBaseView::OnPaint() 
{
	CPaintDC dc(this);

	dc.SetBkColor(m_crBkColor);				// Ϊͼ��ϵͳ���ñ���ɫ

	if (m_gs->beginPaint(dc.GetSafeHdc()))	// ׼����ͼ��ʹ�û�ͼ����
	{
		// ��ʾ��ǰ�������ʽͼ������
		if (m_sizePan.cx != 0 || m_sizePan.cy != 0)
			m_gs->clearWnd();			// �������
		if (!m_gs->drawCachedBitmap(m_sizePan.cx, m_sizePan.cy))
		{
			if (0 == m_sizePan.cx && 0 == m_sizePan.cy)
				m_gs->clearWnd();		// �������
			OnDraw(m_gs);				// ��ʾ��ʽͼ��
			m_gs->saveCachedBitmap();	// ������ʽͼ������
		}
		OnDynDraw(m_gs);				// ��ʾ��̬ͼ��

		m_gs->endPaint();				// �ύ��ͼ���������
	}
}

void CBaseView::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);

	// ������ʾ���ڵĴ�СΪ�ͻ�����С(������������)
	if (nType != SIZE_MINIMIZED && cx > 1 && cy > 1)
	{
		m_xf.setWndSize(cx, cy);
		OnZoomed();
	}
}

void CBaseView::OnZoomed()
{
	Invalidate();
}

long CBaseView::GetShapeCount() const
{
	return m_nShapeCount;
}

ShapeItem* CBaseView::GetShape(long nIndex) const
{
	return nIndex >= 0 && nIndex < m_nShapeCount ? m_pShapes[nIndex] : NULL;
}

Box2d CBaseView::GetExtent() const
{
	return m_rectExtent;
}

void CBaseView::RecalcExtent()
{
	m_rectExtent.empty();
	for (int i = 0; i < m_nShapeCount; i++)
	{
		m_rectExtent.unionWith(m_pShapes[i]->getExtent());
	}
}

void CBaseView::SetShape(long nIndex, ShapeItem* pShape)
{
	ASSERT(nIndex >= 0 && nIndex < m_nShapeCount);
	ASSERT(pShape != NULL && pShape != m_pShapes[nIndex]);

	delete m_pShapes[nIndex];
	m_pShapes[nIndex] = pShape;
}

void CBaseView::OnDraw(GiGraphics* gs)
{
	for (int i = 0; i < m_nShapeCount; i++)
	{
		m_pShapes[i]->draw(gs);
	}
	GiContext context(0, GiColor(128, 128, 128), kLineDot);
	context.setLineAlpha(150);
	gs->drawRect(&context, m_rectExtent);
}

void CBaseView::OnZoomExtent() 
{
	if (m_xf.zoomTo(m_rectExtent * m_xf.modelToWorld(), NULL))
	{
		OnZoomed();
	}
}

void CBaseView::OnUpdateViewGdip(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_bGdip ? 1 : 0);
}

void CBaseView::OnViewGdip() 
{
	m_bGdip = !m_bGdip;

	GiGraphics* gs = m_gs;

	if (m_bGdip)
		m_gs = new GiGraphGdip(m_xf);
	else
		m_gs = new GiGraphGdi(m_xf);

	*(GiGraphics*)m_gs = *gs;
	delete gs;

	Invalidate();
}

void CBaseView::OnUpdateAntiAlias(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_gs->isAntiAliasMode() ? 1 : 0);
}

void CBaseView::OnViewAntiAlias() 
{
	m_gs->setAntiAliasMode(!m_gs->isAntiAliasMode());
	m_gs->clearCachedBitmap();
	Invalidate();
}

void CBaseView::OnViewBkColor() 
{
	CColorDialog dlg (m_crBkColor);
	if (IDOK == dlg.DoModal())
	{
		m_crBkColor = dlg.GetColor();
		m_gs->clearCachedBitmap();
		Invalidate();
	}
}

void CBaseView::OnMouseMove(UINT nFlags, CPoint point) 
{
	CWnd::OnMouseMove(nFlags, point);

	CStatusBar* pStatusBar = DYNAMIC_DOWNCAST(CStatusBar, 
		AfxGetMainWnd()->GetDlgItem(AFX_IDW_STATUS_BAR));
	ASSERT(pStatusBar != NULL);

	Point2d pnt(point.x, point.y);
	pnt *= m_xf.displayToModel();

	CString str;
	int nIndex = pStatusBar->CommandToIndex(ID_INDICATOR_X);
	if (nIndex >= 0)
	{
		str.Format(_T("X: %.2lf"), pnt.x);
		pStatusBar->SetPaneText(nIndex, str);
	}

	nIndex = pStatusBar->CommandToIndex(ID_INDICATOR_Y);
	if (nIndex >= 0)
	{
		str.Format(_T("Y: %.2lf"), pnt.y);
		pStatusBar->SetPaneText(nIndex, str);
	}
}

void CBaseView::OnUpdateViewScale(CCmdUI* pCmdUI) 
{
	CString str;
	str.Format(_T("%.2lf%%"), m_xf.getViewScale() * 100.0);
	pCmdUI->SetText(str);
}

void CBaseView::OnZoomIn() 
{
	if (m_xf.zoomByFactor(0.2))
	{
		OnZoomed();
	}
}

void CBaseView::OnZoomOut() 
{
	if (m_xf.zoomByFactor(-0.2))
	{
		OnZoomed();
	}
}

void CBaseView::OnPanLeft() 
{
	if (m_xf.zoomPan(50, 0))
	{
		OnZoomed();
	}
}

void CBaseView::OnPanRight() 
{
	if (m_xf.zoomPan(-50, 0))
	{
		OnZoomed();
	}
}

void CBaseView::OnPanUp() 
{
	if (m_xf.zoomPan(0, 50))
	{
		OnZoomed();
	}
}

void CBaseView::OnPanDown() 
{
	if (m_xf.zoomPan(0, -50))
	{
		OnZoomed();
	}
}
