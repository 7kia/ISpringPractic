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
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// создание/уничтожение CShapeCompositorView
namespace
{
	const SSize CANVAS_SIZE = SSize(640.f, 480.f);
	const float SCALE_FACTOR = 0.8f;
	const SSize MAX_SIZE = SSize(CANVAS_SIZE.width * SCALE_FACTOR, CANVAS_SIZE.height * SCALE_FACTOR);
}
CShapeCompositorView::CShapeCompositorView()
	: m_shapeFactory()
	, m_selectedShape(m_shapeFactory)
	, m_textureStorage(MAX_SIZE)
	, m_canvas(
		CANVAS_SIZE,
		m_shapeFactory.CreateShape(// TODO : see can rewrite astyle
			SShapeData(
				ShapeType::Rectangle,
				Vec2f(CANVAS_SIZE.width / 2.f, CANVAS_SIZE.height / 2.f),
				CANVAS_SIZE,
				NOT_COLOR,
				BLACK_COLOR,
				3.f
			)
		)
	)
{
	const SSize canvasSize = m_canvas.GetSize();
	D2D1_RECT_F rect;
	rect.left = 0.f;
	rect.right = canvasSize.width;
	rect.top = 0.f;
	rect.bottom = canvasSize.height;

	// TODO : if canvas resize, m_selectedShape will have incorrect BoundingRect
	m_selectedShape.SetBoundingRect(rect);

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

	m_objectRenderer.Draw(*m_canvas.GetView());

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
	m_history.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			m_canvas.GetShapeCollection()
			, ShapeType::Triangle
			, m_shapeFactory
			, m_selectedShape
		)
	);
	RedrawWindow();
}

void CShapeCompositorView::CreateRectangle()
{
	m_history.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			m_canvas.GetShapeCollection()
			, ShapeType::Rectangle
			, m_shapeFactory
			, m_selectedShape
		)
	);
	RedrawWindow();
}

void CShapeCompositorView::CreateEllipse()
{
	m_history.AddAndExecuteCommand(std::make_shared<CAddShapeCanvasCommand>(
		m_canvas.GetShapeCollection()
		, ShapeType::Ellipse
		, m_shapeFactory
		, m_selectedShape
		)
	);
	RedrawWindow();
}

void CShapeCompositorView::CreatePicture()
{
	auto picturePath = m_document.LoadTexture();
	const auto pictureName = picturePath.filename().generic_wstring();
	m_textureStorage.AddTexture(
		pictureName,
		m_imageFactory.CreateTexture(picturePath.generic_wstring())
	);

	m_canvas.PushBackShape(
		std::make_shared<CPicture>(
			m_textureStorage.GetTexture(pictureName),
			Vec2f(float(VIEW_WIDTH) / 2.f, float(VIEW_HEIGHT) / 2.f),
			m_textureStorage.GetCorrectSize(pictureName)
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
	//CShapeCompositorDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

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
//
//CShapeCompositorDoc* CShapeCompositorView::GetDocument() const // встроена неотлаженная версия
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShapeCompositorDoc)));
//	return (CShapeCompositorDoc*)m_pDocument;
//}
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
		ATLENSURE_SUCCEEDED(m_objectRenderer.CreateRecources(this));// TODO : delete dependment to this
		
		// TODO : rewrite Normal
		m_imageFactory.SetRenderTarget(m_pRenderTarget);

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
	if (m_document.OnFileSaveAs(m_canvas.GetShapes()))
	{
		m_history.DoSave();
		RedrawWindow();
	}
}

void CShapeCompositorView::OnFileOpen()
{
	if (CheckSaveDocument() != IDCANCEL)
	{
		if (m_document.OnFileOpen(CMyDocument::DataForAlteration(m_canvas, m_shapeFactory, m_history, m_selectedShape)))
		{
			SetWindowText(m_document.GetFileName());
			RedrawWindow();
		}
	}
}

void CShapeCompositorView::OnFileSave()
{
	if (m_document.OnFileSave(m_canvas.GetShapes()))
	{
		m_history.DoSave();
		SetWindowText(m_document.GetFileName());
		RedrawWindow();
	}
}

void CShapeCompositorView::OnFileNew()
{
	if (CheckSaveDocument() != IDCANCEL)
	{
		if (!(m_history.IsSave() && m_document.IsNewDocument()))
		{
			ResetApplication();
			m_document.ResetCurrentFolder();
			SetWindowText(CString("Безымянный"));
			RedrawWindow();
		}
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
		case WM_CLOSE:
		{
			CheckSaveDocument();

			//PostQuitMessage(0);
		}
		break;

	case WM_KEYDOWN:
		{
			switch (pMsg->wParam)
			{
				case VK_DELETE:
				{
					if (m_selectedShape.HaveSelectedShape())
					{
						m_history.AddAndExecuteCommand(
							std::make_shared<CDeleteShapeCanvasCommand>(
								m_canvas.GetShapeCollection()
								, m_selectedShape
								, m_shapeFactory
								)
						);
						
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
	m_history.Clear();
}

void CShapeCompositorView::ClearCanvas()
{
	m_canvas.Clear();
}

void CShapeCompositorView::ResetApplication()
{
	m_document.DeletePictures(m_textureStorage.GetDeletable());
	m_textureStorage.Clear();

	m_history.Clear();

	m_selectedShape.ResetUpdateParameters();
	m_selectedShape.ResetSelectShapePtr();

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
	case CSelectedShape::UpdateType::MarkerLeftTop:
	case CSelectedShape::UpdateType::MarkerLeftBottom:
	case CSelectedShape::UpdateType::MarkerRightBottom:
	case CSelectedShape::UpdateType::MarkerRightTop:
	{
		const auto finalFrame = m_selectedShape.GetCurrentFrame();
		m_selectedShape.ReturnToOldState();

		m_history.AddAndExecuteCommand(std::make_shared<CChangeShapeRectCanvasCommand>(
			m_canvas.GetShapeProvider(),
			m_selectedShape.GetOldFrame(),
			finalFrame,
			m_selectedShape
			));
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

Vec2f CShapeCompositorView::GetScreenPosition(const CPoint & point)
{
	POINT windowPos;
	GetCursorPos(&windowPos);
	ScreenToClient(&windowPos);

	const CPoint scrollPosition = GetDeviceScrollPosition();//GetDeviceScrollPosition();

	return Vec2f(float(windowPos.x + scrollPosition.x), float(windowPos.y + scrollPosition.y));
}

int CShapeCompositorView::CheckSaveDocument()
{
	int result = IDNO;
	if (!m_history.IsSave())
	{
		result = AfxMessageBox(L"Сохранить изменения?", MB_YESNOCANCEL);

		if (m_document.IsNewDocument())
		{
			if(result == IDYES)
			{
				if (m_document.OnFileSaveAs(m_canvas.GetShapes()))
				{
					m_history.DoSave();
				}
			}					
		}
		else
		{
			if (result == IDYES)
			{
				if (m_document.OnFileSave(m_canvas.GetShapes()))
				{
					m_history.DoSave();
				}
			}
		}
	}

	return result;
}

void CShapeCompositorView::OnClose()
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CheckSaveDocument();

	CScrollView::OnClose();
}
