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
#include "ShapeCompositorModel.h"
#include "ShapeCompositorPresenter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CShapeCompositorView

IMPLEMENT_DYNCREATE(CShapeCompositorView, CScrollView)

BEGIN_MESSAGE_MAP(CShapeCompositorView, CScrollView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_COMMAND(ID_ADD_TRIANGLE, CShapeCompositorView::CreateTriangle)
	ON_COMMAND(ID_ADD_RECTANGLE, CShapeCompositorView::CreateRectangle)
	ON_COMMAND(ID_ADD_ELLIPSE, CShapeCompositorView::CreateEllipse)
	ON_COMMAND(ID_ADD_PICTURE, CShapeCompositorView::CreatePicture)
	ON_COMMAND(ID_UNDO, CShapeCompositorView::Undo)
	ON_COMMAND(ID_REDO, CShapeCompositorView::Redo)
	ON_COMMAND(ID_FILE_SAVE_AS, &CShapeCompositorView::OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, &CShapeCompositorView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CShapeCompositorView::OnFileSave)
	ON_COMMAND(ID_FILE_NEW, &CShapeCompositorView::OnFileNew)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// ��������/����������� CShapeCompositorView

CShapeCompositorView::CShapeCompositorView()
	: m_model(std::make_unique<CShapeCompositorModel>())
{
	RecreateApplication();
}

void CShapeCompositorView::RecreateApplication()
{
	m_canvasView = CCanvasView();

	m_controller = std::make_unique<CShapeCompositorPresenter>(this);//this - IViewSignaller *

	m_canvasView.SetBoundingRect(m_model->GetCanvasRect());

	m_controller->SetHistoryManipulator(m_model.get());
	m_controller->SetDocumentManipulator(m_model.get());
	m_controller->SetShapeManipulator(m_model.get());
	m_controller->SetHaveRenderTarget(m_model.get());
	m_controller->SetModelReseter(m_model.get(), this);
	m_controller->SetShapeViewManipulator(this);//this - IShapeViewManipulator *
}

void CShapeCompositorView::SetWindowCursor(CursorType type)
{
	switch (type)
	{
	case CursorType::SIZENWSE:
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
		break;
	case CursorType::SIZENESW:
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
		break;
	case CursorType::SIZEALL:
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		break;
	case CursorType::ARROW:
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		break;
	}
}

CShapeCompositorView::~CShapeCompositorView()
{
}

void CShapeCompositorView::CreateTriangle()
{
	m_onCreateShape(ShapeType::Triangle);
	RedrawWindow();
}

void CShapeCompositorView::CreateRectangle()
{
	m_onCreateShape(ShapeType::Rectangle);
	RedrawWindow();
}

void CShapeCompositorView::CreateEllipse()
{
	m_onCreateShape(ShapeType::Ellipse);
	RedrawWindow();
}

void CShapeCompositorView::CreatePicture()
{
	m_onCreateShape(ShapeType::Picture);
	RedrawWindow();
}

void CShapeCompositorView::Undo()
{
	m_onUndoCommand();
	RedrawWindow();
}

void CShapeCompositorView::Redo()
{
	m_onRedoCommand();
	RedrawWindow();
}


void CShapeCompositorView::OnDraw(CDC* /*pDC*/)
{
}

void CShapeCompositorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);

	// TODO : see need it function
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
		// TODO : not work set title
		SetWindowText(CString("����������"));

		// Enable D2D support for this window:  

		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		// Create a Direct2D factory.
		m_pRenderTarget = m_objectRenderer.CreateRenderTarget(this);
		ATLENSURE_SUCCEEDED(m_objectRenderer.CreateRecources());
		// TODO : rewrite Normal
		m_onSetRenderTargetForModel(m_pRenderTarget);

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
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

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
	//RedrawWindow();
}

void CShapeCompositorView::OnFileSaveAs()
{
	if (m_onSaveAsDocument())
	{
		RedrawWindow();
	}

}

void CShapeCompositorView::OnFileOpen()
{
	m_canvasView.ResetSelectShapePtr();
	if (m_onOpenDocument())
	{
		//SetWindowText(m_document.GetFileName());
		RedrawWindow();
	}	
}

void CShapeCompositorView::OnFileSave()
{
	if (m_onSaveDocument())
	{
		//SetWindowText(m_document.GetFileName());
		RedrawWindow();
	}
}

void CShapeCompositorView::OnFileNew()
{
	if(m_onNewDocument())
	{
		//SetWindowText(CString("����������"));
		RedrawWindow();
	}
}


void CShapeCompositorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �������� ���� ��� ����������� ���������
					   // �� �������� CScrollView::OnPaint() ��� ��������� ���������

	HRESULT hr = S_OK;

	CPoint point = GetScrollPosition();
	D2D1_MATRIX_3X2_F matrix = D2D1::Matrix3x2F::Translation((float)-point.x, (float)-point.y);
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->SetTransform(matrix);
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	m_canvasView.Draw(m_objectRenderer);

	hr = m_objectRenderer.EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
	}
	
}

void CShapeCompositorView::OnLButtonlClk(UINT, CPoint)
{
	// TODO
}

void CShapeCompositorView::OnKeyDown(UINT, UINT, UINT)
{
	MessageBox(_T("Key Button Down."), _T("Debug"),
		MB_ICONINFORMATION | MB_OK);

}


BOOL CShapeCompositorView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �������� ������������������ ��� ��� ����� �������� ������

	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
				case VK_DELETE:
				{
					if (m_canvasView.HaveSelectedShape())
					{
						m_onDeleteShape(m_canvasView.GetIndexSelectedShape());
						RedrawWindow();
					}			
				}
				break;
			default:
				break;
			}
		}
		break;
	
	default:
		break;
	}

	return CScrollView::PreTranslateMessage(pMsg);
}

//
// Mouse events
//
void CShapeCompositorView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CScrollView::OnLButtonDown(nFlags, point);

	const Vec2f mousePosition = GetScreenPosition(point);
	SetWindowCursor(m_canvasView.ChangeCursor(mousePosition));
	if (m_canvasView.HandleLButtonDown(mousePosition))
	{
		const auto oldFrame = m_canvasView.GetOldFrameSelectedShape();
		const auto newFrame = m_canvasView.GetFrameSelectedShape();
		if (oldFrame != newFrame)
		{
			m_onChangeRectShape(oldFrame, newFrame, m_canvasView.GetIndexSelectedShape());
		}
	}

	RedrawWindow();
}

void CShapeCompositorView::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);

	const Vec2f mousePosition = GetScreenPosition(point);
	SetWindowCursor(m_canvasView.ChangeCursor(mousePosition));
	if (m_canvasView.HandleMouseMove(mousePosition))
	{
		RedrawWindow();
	}
}

void CShapeCompositorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);

	const Vec2f mousePosition = GetScreenPosition(point);
	SetWindowCursor(m_canvasView.ChangeCursor(mousePosition));
	if (m_canvasView.HandleLButtonUp(mousePosition))
	{
		m_onChangeRectShape(
			m_canvasView.GetOldFrameSelectedShape(),
			m_canvasView.GetFrameSelectedShape(),
			m_canvasView.GetIndexSelectedShape()
		);
		m_canvasView.ResetSelectedShapeUpdateParameters();
	}

	RedrawWindow();
}

BOOL CShapeCompositorView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;//CScrollView::OnEraseBkgnd(pDC);
}

void CShapeCompositorView::AddShapeView(const CShapeViewPtr & pView, size_t insertIndex)
{
	m_canvasView.AddShapeView(pView, insertIndex);
}

void CShapeCompositorView::DeleteShapeView(size_t index)
{
	m_canvasView.DeleteShapeView(index);
}

void CShapeCompositorView::ResetView()
{
	RecreateApplication();
}

Vec2f CShapeCompositorView::GetScreenPosition(const CPoint & point)
{
	POINT windowPos;
	GetCursorPos(&windowPos);
	ScreenToClient(&windowPos);

	const CPoint scrollPosition = GetDeviceScrollPosition();//GetDeviceScrollPosition();

	return Vec2f(float(windowPos.x + scrollPosition.x), float(windowPos.y + scrollPosition.y));
}

void CShapeCompositorView::OnDestroy()
{	
	CScrollView::OnDestroy();
}
