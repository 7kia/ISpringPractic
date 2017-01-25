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
	HRESULT CreateDeviceResources();

	// TODO : transfer
	HRESULT	OnRender();
	void	OnResize(UINT width, UINT height);

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CCanvas m_canvas;
	CComPtr<ID2D1Factory>				m_pDirect2dFactory;
	CComPtr<ID2D1HwndRenderTarget>		m_pRenderTarget;

	// TODO : delete it
	// TODO : transfer

	CComPtr<ID2D1SolidColorBrush>						m_pLightSlateGrayBrush;
	CComPtr<ID2D1SolidColorBrush>						m_pCornflowerBlueBrush;

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
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // отладочная версия в ShapeCompositorView.cpp
inline CShapeCompositorDoc* CShapeCompositorView::GetDocument() const
   { return reinterpret_cast<CShapeCompositorDoc*>(m_pDocument); }
#endif

