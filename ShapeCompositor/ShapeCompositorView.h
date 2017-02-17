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

// ShapeCompositorView.h : интерфейс класса CShapeCompositorView
//

#pragma once

#include "ShapeCompositorDoc.h"
#include "Canvas\Canvas.h"
#include "Canvas\History.h"
#pragma comment(lib, "d2d1")

static const FLOAT DEFAULT_DPI = 96.f;


class CShapeCompositorView : public CScrollView
{
protected: // создать только из сериализации
	CShapeCompositorView();
	DECLARE_DYNCREATE(CShapeCompositorView)

// Атрибуты
public:
	CShapeCompositorDoc* GetDocument() const;


// Операции
public:
	// TODO : transfer
	HRESULT	Render();

	void					SetRenderTarget(ID2D1HwndRenderTarget * pRenderTarget);
	ID2D1HwndRenderTarget * GetRenderTarget();

	void					CreateTriangle();
	void					CreateRectangle();
	void					CreateEllipse();
	void					Undo();
	void					Redo();

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


protected:
	CCanvas m_canvas;
	CHistory m_history;

	ID2D1HwndRenderTarget * m_pRenderTarget = nullptr;

	// For test OnMouseMove
	CPoint m_start;// TODO : delete
// Реализация
public:
	virtual ~CShapeCompositorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// buttons
	afx_msg void OnLButtonlClk(UINT, CPoint);	// виртуальная процедура ответа на левую кнопку
	afx_msg void OnKeyDown(UINT, UINT, UINT);	// виртуальная процедура ответа на клавишу
	//
	afx_msg void OnPaint();

	// Mouse events
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // отладочная версия в ShapeCompositorView.cpp
inline CShapeCompositorDoc* CShapeCompositorView::GetDocument() const
   { return reinterpret_cast<CShapeCompositorDoc*>(m_pDocument); }
#endif

