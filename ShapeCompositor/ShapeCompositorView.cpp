// ���� �������� ��� MFC Samples ������������� ���������������� ����������������� ���������� Fluent �� ������ MFC � Microsoft Office
// ("Fluent UI") � ��������������� ������������� ��� ���������� �������� � �������� ���������� �
// ����������� �� ������ Microsoft Foundation Classes � ��������� ����������� ������������,
// ���������� � ����������� ����������� ���������� MFC C++.  
// ������� ������������� ���������� �� �����������, ������������� ��� ��������������� Fluent UI �������� ��������.  
// ��� ��������� �������������� �������� � ����� ������������ ��������� Fluent UI �������� ���-����
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// (C) ���������� ���������� (Microsoft Corp.)
// ��� ����� ��������.

// ShapeCompositorView.cpp : ���������� ������ CShapeCompositorView
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "ShapeCompositor.h"
#endif

#include "ShapeCompositorDoc.h"
#include "ShapeCompositorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShapeCompositorView

IMPLEMENT_DYNCREATE(CShapeCompositorView, CScrollView)

BEGIN_MESSAGE_MAP(CShapeCompositorView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// ��������/����������� CShapeCompositorView

CShapeCompositorView::CShapeCompositorView()
{
}

CShapeCompositorView::~CShapeCompositorView()
{
}


// This method discards device-specific
// resources if the Direct3D device dissapears during execution and
// recreates the resources the next time it's invoked.
HRESULT CShapeCompositorView::Render()
{
	HRESULT hr = S_OK;

	CPoint point = GetScrollPosition();
	D2D1_MATRIX_3X2_F matrix = D2D1::Matrix3x2F::Translation((float)-point.x, (float)-point.y);
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->SetTransform(matrix);
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	hr = m_canvas.Render();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
	}

	return hr;
}

void CShapeCompositorView::SetRenderTarget(ID2D1HwndRenderTarget * pRenderTarget)
{
	m_pRenderTarget = pRenderTarget;
}

ID2D1HwndRenderTarget * CShapeCompositorView::GetRenderTarget()
{
	return m_pRenderTarget;
}

// ��������� CShapeCompositorView

void CShapeCompositorView::OnDraw(CDC* /*pDC*/)
{
	CShapeCompositorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//m_canvas.Render();
	// TODO: �������� ����� ��� ��������� ��� ����������� ������
}

void CShapeCompositorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
	RedrawWindow();
}

void CShapeCompositorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// ����������� CShapeCompositorView

#ifdef _DEBUG
void CShapeCompositorView::AssertValid() const
{
	CView::AssertValid();
}

void CShapeCompositorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShapeCompositorDoc* CShapeCompositorView::GetDocument() const // �������� ������������ ������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShapeCompositorDoc)));
	return (CShapeCompositorDoc*)m_pDocument;
}
#endif //_DEBUG


// ����������� ��������� CShapeCompositorView

int CShapeCompositorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	try
	{
		// Enable D2D support for this window:  
		EnableD2DSupport();

		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		// Create a Direct2D factory.
		//ATLENSURE_SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory));
		//ATLENSURE_SUCCEEDED(CreateDeviceResources());
		ATLENSURE_SUCCEEDED(m_canvas.CreateRecources(this));

	}
	catch (...)
	{
		return -1;
	}

	return 0;
}

BOOL CShapeCompositorView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cx = VIEW_WIDTH; // width
	cs.cy = VIEW_HEIGHT; // height
	cs.y = 0; // top position
	cs.x = 0; // left position
	if (!CScrollView::PreCreateWindow(cs))
		return FALSE;


	return TRUE;
}

void CShapeCompositorView::OnSize(UINT nType, int cx, int cy)
{
	CScrollView::OnSize(nType, cx, cy);

	SetScrollSizes(MM_TEXT, { VIEW_WIDTH, VIEW_HEIGHT });

	if (m_pRenderTarget)
	{
		// Note: This method can fail, but it's okay to ignore the
		// error here, because the error will be returned again
		// the next time EndDraw is called.
		m_pRenderTarget->Resize(D2D1::SizeU(cx, cy));
	}
	Render();
}


void CShapeCompositorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �������� ���� ��� ����������� ���������
					   // �� �������� CScrollView::OnPaint() ��� ��������� ���������

	Render();
}


BOOL CShapeCompositorView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������

	return CScrollView::PreTranslateMessage(pMsg);
}


BOOL CShapeCompositorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �������� ���� ��� ����������� ��������� ��� ����� ������������

	return CScrollView::OnEraseBkgnd(pDC);
}
