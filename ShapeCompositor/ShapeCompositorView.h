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
#include "Canvas\Canvas.h"

#pragma comment(lib, "d2d1")

static const FLOAT DEFAULT_DPI = 96.f;
static const LONG VIEW_WIDTH = 640;
static const LONG VIEW_HEIGHT = 480;

class CShapeCompositorView : public CScrollView
{
protected: // ������� ������ �� ������������
	CShapeCompositorView();
	DECLARE_DYNCREATE(CShapeCompositorView)

// ��������
public:
	CShapeCompositorDoc* GetDocument() const;


// ��������
public:
	HRESULT CreateDeviceResources();

	// TODO : transfer
	HRESULT	Render();
// ���������������
public:
	virtual void OnDraw(CDC* pDC);  // �������������� ��� ��������� ����� �������������
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	CCanvas m_canvas;

	CComPtr<ID2D1Factory>				m_pDirect2dFactory;
	CComPtr<ID2D1HwndRenderTarget>		m_pRenderTarget;
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // ���������� ������ � ShapeCompositorView.cpp
inline CShapeCompositorDoc* CShapeCompositorView::GetDocument() const
   { return reinterpret_cast<CShapeCompositorDoc*>(m_pDocument); }
#endif

