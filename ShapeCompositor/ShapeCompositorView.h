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
#include "Canvas\D2DObjectRenderer.h"
#include "Signal.h"
#include "FileWork\XMLReader.h"

#include <vector>
#include <memory>
#pragma comment(lib, "d2d1")

static const FLOAT DEFAULT_DPI = 96.f;

class CShapeCompositorModel;
class CShapeCompositorController;

class CShapeCompositorView : public CScrollView
{
public:
	CShapeCompositorView();

protected: // создать только из сериализации
	DECLARE_DYNCREATE(CShapeCompositorView)

// Атрибуты
public:
	//CShapeCompositorDoc* GetDocument() const;

	void SetBoundingRect(const D2D1_RECT_F & rect);

// Операции
public:
	// TODO : transfer
	HRESULT	Draw();

	void					SetRenderTarget(ID2D1HwndRenderTarget * pRenderTarget);
	ID2D1HwndRenderTarget * GetRenderTarget();

	void					CreateTriangle();
	void					CreateRectangle();
	void					CreateEllipse();
	void					CreatePicture();

	void					Undo();
	void					Redo();

	void					ChangeCursor(const Vec2f &  mousePos);

	// For document

	void					ResetSelectedShape();

private:
	void					CreateCommandForSelectedShape();
	void					ChangeSelectedShape(const Vec2f & mousePos);

	Vec2f					GetScreenPosition(const CPoint & point);

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	/////////////////////////////////////////////////
	// Signals
public:
	signal::Connection DoOnGetCanvasView(std::function<CShapePtr()> const & action);
	signal::Connection DoOnGetCanvasShapes(std::function<std::vector<CShapePtr>()> const & action);
	signal::Connection DoOnCreatePicture(std::function<void(CSelectedShape &)> const & action);

	signal::Connection DoOnSaveAsDocument(std::function<bool()> const & action);
	signal::Connection DoOnSaveDocument(std::function<bool()> const & action);
	signal::Connection DoOnOpenDocument(std::function<bool(CSelectedShape &)> const & action);
	signal::Connection DoOnNewDocument(std::function<bool()> const & action);

	signal::Connection DoOnUndoCommand(std::function<void()> const & action);
	signal::Connection DoOnRedoCommand(std::function<void()> const & action);


	signal::Connection DoOnDeleteShapeCommand(std::function<void(CSelectedShape &)> const & action);
	signal::Connection DoOnChangeRectCommand(std::function<void(const CFrame, CSelectedShape &)> const & action);
	signal::Connection DoOnCreateShapeCommand(std::function<void(ShapeType, CSelectedShape &)> const & action);
	signal::Connection DoOnSetRenderTargetForImageFactory(std::function<void(ID2D1HwndRenderTarget *)> const & action);


protected:
	signal::Signal<CShapePtr()> m_getCanvasView;
	signal::Signal<std::vector<CShapePtr>()> m_getCanvasShapes;
	signal::Signal<void(CSelectedShape &)> m_createPicture;

	signal::Signal<bool()> m_saveAsDocument;
	signal::Signal<bool()> m_saveDocument;
	signal::Signal<bool()> m_newDocument;
	signal::Signal<bool(CSelectedShape &)> m_openDocument;

	signal::Signal<void()> m_undoCommand;
	signal::Signal<void()> m_redoCommand;

	signal::Signal<void(CSelectedShape &)> m_deleteShapeCommand;
	signal::Signal<void(const CFrame, CSelectedShape &)> m_createChangeRectCommand;
	signal::Signal<void(ShapeType, CSelectedShape &)> m_createShapeCommand;
	signal::Signal<void(ID2D1HwndRenderTarget *)> m_setRenderTargetForImageFactory;

	std::unique_ptr<CShapeCompositorModel> m_model;
	std::unique_ptr<CShapeCompositorController> m_controller;
	/////////////////////////////////////////////////
protected:



	CSelectedShape m_selectedShape;
	// TODO : create Presenter
	CFrame m_oldFrame;


	CComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
	CD2DObjectRenderer		m_objectRenderer;// TODO : transfer to CShapeCompositiorView, fix Draw

// Реализация
public:
	virtual ~CShapeCompositorView();
	CShapeCompositorDoc * GetDocument() const;

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

	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileNew();

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
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // отладочная версия в ShapeCompositorView.cpp
inline CShapeCompositorDoc* CShapeCompositorView::GetDocument() const
   { return reinterpret_cast<CShapeCompositorDoc*>(m_pDocument); }
#endif

