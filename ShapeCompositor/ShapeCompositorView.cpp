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
	, m_selectedShape(m_shapeFactory)
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

	for (const auto & shape : m_canvas.GetShapes())
	{
		m_objectRenderer.Draw(*shape);
	}

	if (m_selectedShape.HaveSelectedShape())
	{
		for (const auto & shape : m_selectedShape.GetShapes())
		{
			m_objectRenderer.Draw(*shape);
		}
	}

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
	m_canvas.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			&m_canvas
			, ShapeType::Triangle
			, m_shapeFactory
			, m_selectedShape
		)
	);
	RedrawWindow();
}

void CShapeCompositorView::CreateRectangle()
{
	m_canvas.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			&m_canvas
			, ShapeType::Rectangle
			, m_shapeFactory
			, m_selectedShape
		)
	);
	RedrawWindow();
}

void CShapeCompositorView::CreateEllipse()
{
	m_canvas.AddAndExecuteCommand(std::make_shared<CAddShapeCanvasCommand>(
		&m_canvas
		, ShapeType::Ellipse
		, m_shapeFactory
		, m_selectedShape
		)
	);
	RedrawWindow();
}

void CShapeCompositorView::Undo()
{
	m_canvas.UndoCommand();
	RedrawWindow();
}

void CShapeCompositorView::Redo()
{
	m_canvas.RedoCommand();
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
	GetDocument()->OnFileSaveAs(m_canvas.GetShapes());
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
					m_canvas.AddAndExecuteCommand(
						std::make_shared<CDeleteShapeCanvasCommand>(
							m_canvas
							, m_selectedShape
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
	if (m_selectedShape.HaveSelectedShape())
	{
		if (m_selectedShape.IsResize(mousePos))
		{
			m_selectedShape.SetUpdateState(true);
			isResize = true;
		}
	}

	if (!isResize)
	{
		ChangeSelectedShape(mousePos);

		if (m_selectedShape.HaveSelectedShape())
		{
			if (m_selectedShape.IsMove(mousePos))
			{
				m_selectedShape.SetUpdateState(true);
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

	if (m_selectedShape.HaveSelectedShape() && m_selectedShape.IsUpdate())
	{
		m_selectedShape.HandleMoveMouse(Vec2f(float(point.x), float(point.y)));
		RedrawWindow();
	}

}

void CShapeCompositorView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CView::OnLButtonUp(nFlags, point);

	if (m_selectedShape.HaveSelectedShape())
	{
		m_selectedShape.SetUpdateState(false);
	}

	ChangeCursor(point);

	if (m_selectedShape.DoneUpdate())
	{
		CreateCommandForSelectedShape();
		m_selectedShape.ResetUpdateParameters();
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
	if (m_selectedShape.GetShape())
	{
		CSelectedShape::UpdateType updateType = m_selectedShape.GetUpdateType();
		bool needChangeToNW = (updateType == CSelectedShape::UpdateType::MarkerLeftTop)
			|| (updateType == CSelectedShape::UpdateType::MarkerRightBottom)
			|| m_selectedShape.InLeftTopMarker(position)
			|| m_selectedShape.InRightBottomMarker(position);
		bool needChangeToNE = (updateType == CSelectedShape::UpdateType::MarkerRightTop) 
			|| (updateType == CSelectedShape::UpdateType::MarkerLeftBottom)
			|| m_selectedShape.InRightTopMarker(position)
			|| m_selectedShape.InLeftBottomMarker(position);

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
	m_canvas.ClearHistory();
}

void CShapeCompositorView::ClearCanvas()
{
	m_canvas.Clear();
}

void CShapeCompositorView::ResetSelectedShape()
{
	m_selectedShape.ResetSelectShapePtr();
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
	switch (m_selectedShape.GetUpdateType())
	{
	case CSelectedShape::UpdateType::Move:
	{
		m_selectedShape.ReturnToOldState();
		m_canvas.AddAndExecuteCommand(std::make_shared<CMoveShapeCanvasCommand>(
			m_selectedShape.GetShape(),
			m_selectedShape.GetFinalShift(),
			m_selectedShape
			));
		m_selectedShape.ResetUpdateParameters();

	}
	break;
	case CSelectedShape::UpdateType::MarkerLeftTop:
	case CSelectedShape::UpdateType::MarkerLeftBottom:
	case CSelectedShape::UpdateType::MarkerRightBottom:
	case CSelectedShape::UpdateType::MarkerRightTop:
	{
		m_selectedShape.ReturnToOldState();
		m_canvas.AddAndExecuteCommand(std::make_shared<CScaleShapeCanvasCommand>(
			m_selectedShape.GetShape(),
			m_selectedShape.GetOldFrameData(),// TODO : see can delete other arguments
			m_selectedShape.GetNewFrameData(),
			m_selectedShape
			));
		m_selectedShape.ResetUpdateParameters();
	}
	break;
	case CSelectedShape::UpdateType::None:
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
		if (m_selectedShape.GetShape() != selectShape)
		{
			m_selectedShape.SetShape(selectShape);
		}
	}
	else
	{
		m_selectedShape.ResetSelectShapePtr();
	}
}
