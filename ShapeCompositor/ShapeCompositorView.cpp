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

IMPLEMENT_DYNCREATE(CShapeCompositorView, CView)

BEGIN_MESSAGE_MAP(CShapeCompositorView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// создание/уничтожение CShapeCompositorView

CShapeCompositorView::CShapeCompositorView()
{
	// TODO: добавьте код создания

}

CShapeCompositorView::~CShapeCompositorView()
{
}

BOOL CShapeCompositorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
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
