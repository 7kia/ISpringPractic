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

// ShapeCompositorView.h : ��������� ������ CShapeCompositorView
//

#pragma once

#include "ShapeCompositorDoc.h"
#include "FileWork\MyDocument.h"
#include "Canvas\D2DObjectRenderer.h"
#include "Canvas\Picture\Picture.h"
#include "Canvas\Picture\D2DImageFactory.h"
#include "Canvas\Picture\TextureStorage.h"

#pragma comment(lib, "d2d1")

static const FLOAT DEFAULT_DPI = 96.f;


class CShapeCompositorView : public CScrollView
{
protected: // ������� ������ �� ������������
	CShapeCompositorView();
	DECLARE_DYNCREATE(CShapeCompositorView)

// ��������
public:
	//CShapeCompositorDoc* GetDocument() const;


// ��������
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
	void					ClearHistory();
	void					ClearCanvas();
	void					ResetApplication();
	void					ResetSelectedShape();
	CCanvas &				GetCanvas();
	const CShapeFactory &	GetShapeFactory() const;

private:
	void					CreateCommandForSelectedShape();
	void					ChangeSelectedShape(const Vec2f & mousePos);

	void					LoadTexture(const std::string & name);
	Vec2f					GetScreenPosition(const CPoint & point);

	int						CheckSaveDocument();
// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);


protected:
	CCanvas m_canvas;
	CHistory m_history;
	CMyDocument m_document;

	CSelectedShape m_selectedShape;
	CShapeFactory m_shapeFactory;

	TextureStorage m_textureStorage;

	ID2D1HwndRenderTarget * m_pRenderTarget = nullptr;
	CD2DObjectRenderer		m_objectRenderer;// TODO : transfer to CShapeCompositiorView, fix Draw
	CD2DImageFactory		m_imageFactory;
// ����������
public:
	virtual ~CShapeCompositorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ��������� ������� ����� ���������
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
	afx_msg void OnLButtonlClk(UINT, CPoint);	// ����������� ��������� ������ �� ����� ������
	afx_msg void OnKeyDown(UINT, UINT, UINT);	// ����������� ��������� ������ �� �������
	//
	afx_msg void OnPaint();

	// Mouse events
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
};

#ifndef _DEBUG  // ���������� ������ � ShapeCompositorView.cpp
inline CShapeCompositorDoc* CShapeCompositorView::GetDocument() const
   { return reinterpret_cast<CShapeCompositorDoc*>(m_pDocument); }
#endif

