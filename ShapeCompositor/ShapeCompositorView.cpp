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

// создание/уничтожение CShapeCompositorView

CShapeCompositorView::CShapeCompositorView()
	: m_model(std::make_unique<CShapeCompositorModel>())
{
	m_controller = std::make_unique<CShapeCompositorPresenter>(this);

	SetBoundingRect(m_model->GetCanvasRect());

	m_controller->SetHistoryManipulator(m_model.get());
	m_controller->SetDocumentManipulator(m_model.get());
	m_controller->SetShapeManipulator(m_model.get());
	m_controller->SetDataForDraw(m_model.get());
	m_controller->SetHaveRenderTarget(m_model.get());
	m_controller->SetModelReseter(m_model.get(), this);
}

CShapeCompositorView::~CShapeCompositorView()
{
}


void CShapeCompositorView::SetBoundingRect(const D2D1_RECT_F & rect)
{
	m_selectedShape.SetBoundingRect(rect);
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

	m_objectRenderer.Draw(*m_getCanvasView().get());

	const auto canvasShapes = m_getCanvasShapes().get();
	for (const auto & shape : canvasShapes)
	{
		m_objectRenderer.Draw(*shape);
	}

	if (m_selectedShape.HaveSelectedShape())
	{
		m_objectRenderer.Draw(*m_selectedShape.GetFrameShape());
		for (const auto & shape : m_selectedShape.GetDragPoints())
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

void CShapeCompositorView::CreateTriangle()
{
	m_createShapeCommand(ShapeType::Triangle, m_selectedShape);
	RedrawWindow();
}

void CShapeCompositorView::CreateRectangle()
{
	m_createShapeCommand(ShapeType::Rectangle, m_selectedShape);
	RedrawWindow();
}

void CShapeCompositorView::CreateEllipse()
{
	m_createShapeCommand(ShapeType::Ellipse, m_selectedShape);
	RedrawWindow();
}

void CShapeCompositorView::CreatePicture()
{
	m_createShapeCommand(ShapeType::Picture, m_selectedShape);
	RedrawWindow();
}

void CShapeCompositorView::Undo()
{
	m_undoCommand();
	RedrawWindow();
}

void CShapeCompositorView::Redo()
{
	m_redoCommand();
	RedrawWindow();
}


void CShapeCompositorView::OnDraw(CDC* /*pDC*/)
{
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
		// TODO : not work set title
		SetWindowText(CString("Безымянный"));

		// Enable D2D support for this window:  

		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
		// Create a Direct2D factory.
		m_pRenderTarget = m_objectRenderer.CreateRenderTarget(this);
		ATLENSURE_SUCCEEDED(m_objectRenderer.CreateRecources());// TODO : delete dependment to this
		// TODO : rewrite Normal
		m_setRenderTargetForModel(m_pRenderTarget);

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
	if (m_saveAsDocument())
	{
		RedrawWindow();
	}

}

void CShapeCompositorView::OnFileOpen()
{
	if (m_openDocument(m_selectedShape))
	{
		//SetWindowText(m_document.GetFileName());
		RedrawWindow();
	}	
}

void CShapeCompositorView::OnFileSave()
{
	if (m_saveDocument())
	{
		//SetWindowText(m_document.GetFileName());
		RedrawWindow();
	}
}

void CShapeCompositorView::OnFileNew()
{
	if(m_newDocument())
	{
		//SetWindowText(CString("Безымянный"));
		RedrawWindow();
	}
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
					if (m_selectedShape.HaveSelectedShape())
					{
						m_deleteShapeCommand(m_selectedShape);					
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
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CScrollView::OnLButtonDown(nFlags, point);

	const Vec2f mousePos = GetScreenPosition(point);

	ChangeCursor(mousePos);

	bool isResize = false;
	if (m_selectedShape.HaveSelectedShape())
	{
		if (m_selectedShape.IsResize(mousePos))
		{
			m_selectedShape.SetUpdateState(true);
			isResize = true;
			m_oldFrame = m_selectedShape.GetShape()->GetFrame();
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
				m_oldFrame = m_selectedShape.GetShape()->GetFrame();
			}
		}
	}


	RedrawWindow();
}

void CShapeCompositorView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CView::OnMouseMove(nFlags, point);

	const Vec2f mousePosition = GetScreenPosition(point);
	ChangeCursor(mousePosition);

	if (m_selectedShape.HaveSelectedShape() && m_selectedShape.IsUpdate())
	{
		m_selectedShape.HandleMoveMouse(mousePosition);
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

	ChangeCursor(GetScreenPosition(point));

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

void CShapeCompositorView::ChangeCursor(const Vec2f & position)
{
	if (m_selectedShape.GetShape())
	{
		CSelectedShape::UpdateType updateType = m_selectedShape.GetUpdateType();
		bool needChangeToNW = (updateType == CSelectedShape::UpdateType::MarkerLeftTop)
			|| (updateType == CSelectedShape::UpdateType::MarkerRightBottom)
			|| m_selectedShape.InMarker(position, CSelectedShape::ShapeIndex::MarkerLeftTop)
			|| m_selectedShape.InMarker(position, CSelectedShape::ShapeIndex::MarkerRightBottom);
		bool needChangeToNE = (updateType == CSelectedShape::UpdateType::MarkerRightTop) 
			|| (updateType == CSelectedShape::UpdateType::MarkerLeftBottom)
			|| m_selectedShape.InMarker(position, CSelectedShape::ShapeIndex::MarkerRightTop)
			|| m_selectedShape.InMarker(position, CSelectedShape::ShapeIndex::MarkerLeftBottom);

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
		else if (GetShape(position, m_getCanvasShapes().get()) != nullptr)
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		}
	}
	else
	{
		if (GetShape(position, m_getCanvasShapes().get()) != nullptr)
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
		}
		else
		{
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
		}
	}

}



void CShapeCompositorView::ResetSelectedShape()
{
	m_selectedShape.ResetSelectShapePtr();
}

void CShapeCompositorView::CreateCommandForSelectedShape()
{
	switch (m_selectedShape.GetUpdateType())
	{
	case CSelectedShape::UpdateType::Move:
	case CSelectedShape::UpdateType::MarkerLeftTop:
	case CSelectedShape::UpdateType::MarkerLeftBottom:
	case CSelectedShape::UpdateType::MarkerRightBottom:
	case CSelectedShape::UpdateType::MarkerRightTop:
	{
		m_createChangeRectCommand(m_oldFrame, m_selectedShape);
	}
	break;
	case CSelectedShape::UpdateType::None:
		break;
	default:
		break;
	}

}

void CShapeCompositorView::ChangeSelectedShape(const Vec2f & mousePos)
{
	auto selectShape = GetShape(mousePos, m_getCanvasShapes().get());

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
	//m_document.DeletePictures(m_textureStorage.GetDeletable());
	//if (SaveChangeDocument() != IDCANCEL)
	//{
	//}
	
	CScrollView::OnDestroy();


	// TODO: добавьте свой код обработчика сообщений
}
