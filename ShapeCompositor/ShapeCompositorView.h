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
#include "Canvas\CanvasView.h"
#include "Signal.h"
#include "FileWork\XMLReader.h"

#include <vector>
#include <memory>
#pragma comment(lib, "d2d1")

static const FLOAT DEFAULT_DPI = 96.f;

class IViewReseter
{
public:
	virtual ~IViewReseter() = default;

	virtual void ResetView() = 0;
};

class IShapeViewManipulator
{
public:
	virtual ~IShapeViewManipulator() = default;

	virtual void AddShapeView(const CShapeViewPtr & pView, size_t insertIndex) = 0;
	virtual void DeleteShapeView(size_t index) = 0;
};

class IViewSignaller
{
public:
	virtual ~IViewSignaller() = default;

	virtual signal::Connection DoOnSaveAsDocument(std::function<bool()> const & action) = 0;
	virtual signal::Connection DoOnSaveDocument(std::function<bool()> const & action) = 0;
	virtual signal::Connection DoOnOpenDocument(std::function<bool()> const & action) = 0;
	virtual signal::Connection DoOnNewDocument(std::function<bool()> const & action) = 0;

	virtual signal::Connection DoOnUndoCommand(std::function<void()> const & action) = 0;
	virtual signal::Connection DoOnRedoCommand(std::function<void()> const & action) = 0;

	virtual signal::Connection DoOnDeleteShapeCommand(std::function<void(size_t)> const & action) = 0;
	virtual signal::Connection DoOnChangeRectCommand(std::function<void(const CFrame, const CFrame, size_t)> const & action) = 0;
	virtual signal::Connection DoOnCreateShapeCommand(std::function<void(ShapeType)> const & action) = 0;
	virtual signal::Connection DoOnSetRenderTargetForModel(std::function<void(ID2D1HwndRenderTarget *)> const & action) = 0;
};

class CShapeCompositorModel;
class CShapeCompositorPresenter;

class CShapeCompositorView 
	: public CScrollView
	, public IViewReseter
	, public IViewSignaller
	, public IShapeViewManipulator
{
public:
	CShapeCompositorView();

protected: // создать только из сериализации
	DECLARE_DYNCREATE(CShapeCompositorView)

// Атрибуты
public:
	//CShapeCompositorDoc* GetDocument() const;
// Операции
public:
	void CreateTriangle();
	void CreateRectangle();
	void CreateEllipse();
	void CreatePicture();

	void Undo();
	void Redo();

	//--------------------------------------------
	// IShapeViewManipulator
	void AddShapeView(const CShapeViewPtr & pView, size_t insertIndex) override;
	void DeleteShapeView(size_t index) override;
	//--------------------------------------------
	// IViewReseter
	void ResetView() override;
	//--------------------------------------------
	// IViewSignaller
	signal::Connection DoOnSaveAsDocument(std::function<bool()> const & action) override;
	signal::Connection DoOnSaveDocument(std::function<bool()> const & action) override;
	signal::Connection DoOnOpenDocument(std::function<bool()> const & action) override;
	signal::Connection DoOnNewDocument(std::function<bool()> const & action) override;

	signal::Connection DoOnUndoCommand(std::function<void()> const & action) override;
	signal::Connection DoOnRedoCommand(std::function<void()> const & action) override;

	signal::Connection DoOnDeleteShapeCommand(std::function<void(size_t)> const & action) override;
	signal::Connection DoOnChangeRectCommand(std::function<void(const CFrame, const CFrame, size_t)> const & action) override;
	signal::Connection DoOnCreateShapeCommand(std::function<void(ShapeType)> const & action) override;
	signal::Connection DoOnSetRenderTargetForModel(std::function<void(ID2D1HwndRenderTarget *)> const & action) override;
	//--------------------------------------------
private:
	Vec2f GetScreenPosition(const CPoint & point);
	void RecreateApplication();// TODO : see might trasfer create application to other place
	void SetWindowCursor(CursorType type);
// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);	
protected:
	signal::Signal<bool()> m_onSaveAsDocument;
	signal::Signal<bool()> m_onSaveDocument;
	signal::Signal<bool()> m_onNewDocument;
	signal::Signal<bool()> m_onOpenDocument;

	signal::Signal<void()> m_onUndoCommand;
	signal::Signal<void()> m_onRedoCommand;

	signal::Signal<void(size_t)> m_onDeleteShape;
	signal::Signal<void(const CFrame, const CFrame, size_t)> m_onChangeRectShape;
	signal::Signal<void(ShapeType)> m_onCreateShape;
	signal::Signal<void(ID2D1HwndRenderTarget *)> m_onSetRenderTargetForModel;// Render target create in the class and need in other
protected:
	CCanvasView m_canvasView;
	CComPtr<ID2D1HwndRenderTarget> m_pRenderTarget;
	CD2DObjectRenderer m_objectRenderer;
	///////////////////////////////////////////////////////////
	// TODO : see can it transfer
protected:
	std::unique_ptr<CShapeCompositorModel> m_model;
	std::unique_ptr<CShapeCompositorPresenter> m_controller;
	///////////////////////////////////////////////////////////

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

