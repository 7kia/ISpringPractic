// Этот исходный код MFC Samples демонстрирует функционирование пользовательского интерфейса Fluent на основе MFC в Microsoft Office
// ("Fluent UI") и предоставляется исключительно как справочный материал в качестве дополнения к
// справочнику по пакету Microsoft Foundation Classes и связанной электронной документации,
// включенной в программное обеспечение библиотеки MFC C++.  
// Условия лицензионного соглашения на копирование, использование или распространение Fluent UI доступны отдельно.  
// Для получения дополнительных сведений о нашей лицензионной программе Fluent UI посетите веб-узел
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// (C) Корпорация Майкрософт (Microsoft Corp.)
// Все права защищены.

// ShapeCompositorView.cpp : реализация класса CShapeCompositorView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
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
	ON_COMMAND(ID_ADD_TRIANGLE, CShapeCompositorView::CreateTriangle)
	ON_COMMAND(ID_ADD_RECTANGLE, CShapeCompositorView::CreateRectangle)
	ON_COMMAND(ID_ADD_ELLIPSE, CShapeCompositorView::CreateEllipse)
	ON_COMMAND(ID_UNDO, CShapeCompositorView::Undo)
	ON_COMMAND(ID_REDO, CShapeCompositorView::Redo)
	ON_COMMAND(ID_FILE_SAVE_AS, &CShapeCompositorView::OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, &CShapeCompositorView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CShapeCompositorView::OnFileSave)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// создание/уничтожение CShapeCompositorView

CShapeCompositorView::CShapeCompositorView()
	: m_shapeFactory()// TODO : see can rewrite
	, m_selectShape(m_shapeFactory)
{
}

CShapeCompositorView::~CShapeCompositorView()
{
}


// This method discards device-specific
// resources if the Direct3D device dissapears during execution and
// recreates the resources the next time it's invoked.
HRESULT CShapeCompositorView::Draw()
{
	HRESULT hr = S_OK;

	CPoint point = GetScrollPosition();
	D2D1_MATRIX_3X2_F matrix = D2D1::Matrix3x2F::Translation((float)-point.x, (float)-point.y);
	m_pRenderTarget->BeginDraw();
	m_pRenderTarget->SetTransform(matrix);
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

	m_objectRenderer.Draw(m_canvas);
	m_objectRenderer.Draw(m_selectShape);
	hr = m_objectRenderer.EndDraw();

	if (hr == D2DERR_RECREATE_TARGET)
	{
		hr = S_OK;
	}

	return hr;
}

void CShapeCompositorView::SetRenderTarget(ID2D1HwndRenderTarget * pRenderTarget)
{
	m_pRenderTarget = pRenderTarget;// TODO : need it
}

ID2D1HwndRenderTarget * CShapeCompositorView::GetRenderTarget()
{
	return m_pRenderTarget;
}

void CShapeCompositorView::CreateTriangle()
{
	m_history.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			&m_canvas
			, ShapeType::Triangle
			, m_shapeFactory
		)
	);
	RedrawWindow();
}

void CShapeCompositorView::CreateRectangle()
{
	m_history.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			&m_canvas
			, ShapeType::Rectangle
			, m_shapeFactory
		)
	);
	RedrawWindow();
}

void CShapeCompositorView::CreateEllipse()
{
	m_history.AddAndExecuteCommand(std::make_shared<CAddShapeCanvasCommand>(
		&m_canvas
		, ShapeType::Ellipse
		, m_shapeFactory
		)
	);
	RedrawWindow();
}

void CShapeCompositorView::Undo()
{
	m_history.Undo();
	RedrawWindow();
}

void CShapeCompositorView::Redo()
{
	m_history.Redo();
	RedrawWindow();
}


// рисование CShapeCompositorView

void CShapeCompositorView::OnDraw(CDC* /*pDC*/)
{
	CShapeCompositorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
}

void CShapeCompositorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CShapeCompositorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// диагностика CShapeCompositorView

#ifdef _DEBUG
void CShapeCompositorView::AssertValid() const
{
	CView::AssertValid();
}

void CShapeCompositorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShapeCompositorDoc* CShapeCompositorView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShapeCompositorDoc)));
	return (CShapeCompositorDoc*)m_pDocument;
}
#endif //_DEBUG


// обработчики сообщений CShapeCompositorView

int CShapeCompositorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	try
	{
		// Enable D2D support for this window:  

		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		// Create a Direct2D factory.
		ATLENSURE_SUCCEEDED(m_objectRenderer.CreateRecources(this));// TODO : delete dependment to this

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

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);


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
	GetDocument()->OnFileSave(m_canvas.GetShapes());
	RedrawWindow();
}

void CShapeCompositorView::OnFileOpen()
{
	GetDocument()->OnFileOpen(this);
	RedrawWindow();
}

void CShapeCompositorView::OnFileSave()
{
	GetDocument()->OnFileSave(m_canvas.GetShapes());
	RedrawWindow();
}


void CShapeCompositorView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: добавьте свой код обработчика сообщений
					   // Не вызывать CScrollView::OnPaint() для сообщений рисования

	Draw();
	
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
	// TODO: добавьте специализированный код или вызов базового класса

	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
				case VK_DELETE:
				{
					m_history.AddAndExecuteCommand(
						std::make_shared<CDeleteShapeCanvasCommand>(
							m_canvas
							, m_selectShape
							, m_shapeFactory
						)
					);
					RedrawWindow();
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
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CScrollView::OnLButtonDown(nFlags, point);

	ChangeCursor(point);
	//m_canvas.HandleLButtHandleDown(Vec2f(float(point.x), float(point.y)));

	const Vec2f mousePos = Vec2f(float(point.x), float(point.y));
	bool isResize = false;
	if (m_selectShape.HaveSelectedShape())
	{
		if (m_selectShape.IsResize(mousePos))
		{
			m_selectShape.SetUpdateState(true);
			isResize = true;
		}
	}

	if (!isResize)
	{
		ChangeSelectedShape(mousePos);

		if (m_selectShape.HaveSelectedShape())
		{
			if (m_selectShape.IsMove(mousePos))
			{
				m_selectShape.SetUpdateState(true);
			}
		}
	}


	RedrawWindow();
}

void CShapeCompositorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CView::OnMouseMove(nFlags, point);
	ChangeCursor(point);

	if (m_selectShape.HaveSelectedShape() && m_selectShape.IsUpdate())
	{
		m_selectShape.HandleMoveMouse(Vec2f(float(point.x), float(point.y)));
		RedrawWindow();
	}

}

void CShapeCompositorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CView::OnLButtonUp(nFlags, point);

	if (m_selectShape.HaveSelectedShape())
	{
		m_selectShape.SetUpdateState(false);
	}

	ChangeCursor(point);

	if (m_selectShape.DoneUpdate())
	{
		CreateCommandForSelectedShape();
		m_selectShape.ResetUpdateParameters();
	}

	RedrawWindow();
}

BOOL CShapeCompositorView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	return TRUE;//CScrollView::OnEraseBkgnd(pDC);
}

void CShapeCompositorView::ChangeCursor(const CPoint mousePos)
{
	const Vec2f position = Vec2f(float(mousePos.x), float(mousePos.y));
	//const auto pSelectShape = m_canvas.GetSelectShape();
	//const auto pFrameSelectShape = m_canvas.GetFrameSelectedShape();
	if (m_selectShape.GetShape())
	{
		CSelectShape::UpdateType updateType = m_selectShape.GetUpdateType();
		bool needChangeToNW = (updateType == CSelectShape::UpdateType::MarkerLeftTop)
			|| (updateType == CSelectShape::UpdateType::MarkerRightBottom)
			|| m_selectShape.InLeftTopMarker(position)
			|| m_selectShape.InRightBottomMarker(position);
		bool needChangeToNE = (updateType == CSelectShape::UpdateType::MarkerRightTop) 
			|| (updateType == CSelectShape::UpdateType::MarkerLeftBottom)
			|| m_selectShape.InRightTopMarker(position)
			|| m_selectShape.InLeftBottomMarker(position);

		if (needChangeToNW)
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
			return;
		}
		else if (needChangeToNE)
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
			return;
		}
		else if (m_canvas.GetShape(position) != nullptr)
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		}
	}
	else
	{
		if (m_canvas.GetShape(position) != nullptr)
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		}
		else
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		}
	}

}

void CShapeCompositorView::ClearHistory()
{
	m_history.Clear();
}

void CShapeCompositorView::ResetSelectedShape()
{
	m_selectShape.ResetSelectShapePtr();
}

CCanvas & CShapeCompositorView::GetCanvas()
{
	return m_canvas;
}

const CShapeFactory & CShapeCompositorView::GetShapeFactory() const
{
	return m_shapeFactory;
}

void CShapeCompositorView::CreateCommandForSelectedShape()
{
	switch (m_selectShape.GetUpdateType())
	{
	case CSelectShape::UpdateType::Move:
	{
		m_selectShape.ReturnToOldState();
		m_history.AddAndExecuteCommand(std::make_shared<CMoveShapeCanvasCommand>(
			m_selectShape.GetShape(),
			m_selectShape.GetShift(),
			m_selectShape
			));
	}
	break;
	case CSelectShape::UpdateType::MarkerLeftTop:
	case CSelectShape::UpdateType::MarkerLeftBottom:
	case CSelectShape::UpdateType::MarkerRightBottom:
	case CSelectShape::UpdateType::MarkerRightTop:
	{
		m_selectShape.ReturnToOldState();
		m_history.AddAndExecuteCommand(std::make_shared<CScaleShapeCanvasCommand>(
			m_selectShape.GetShape(),
			m_selectShape.GetOldFrameData(),// TODO : see can delete other arguments
			m_selectShape.GetNewFrameData(),
			m_selectShape
			));

	}
	break;
	case CSelectShape::UpdateType::None:
		break;
	default:
		break;
	}

}

void CShapeCompositorView::ChangeSelectedShape(const Vec2f mousePos)
{
	auto selectShape = m_canvas.GetShape(mousePos);

	if (selectShape.get() != nullptr)
	{
		if (m_selectShape.GetShape() != selectShape)
		{
			m_selectShape.SetShape(selectShape);
		}
	}
	else
	{
		m_selectShape.ResetSelectShapePtr();
	}
}
