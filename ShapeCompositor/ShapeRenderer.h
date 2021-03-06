#pragma once

#include "RenderShapeVisitor.h"

class CShapeCompositorView;

class CShapeRender 
	: public IRenderShapeVisitor
{
public:
	CShapeRender();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	HRESULT CreateRecources(CShapeCompositorView * window);

	//--------------------------------------------
	// IRenderShapeVisitor

	void Visit(const CRectangleView & shape) override;
	void Visit(const CEllipseView & shape) override;
	void Visit(const CTriangleView & shape) override;


	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CShapeCompositorView *						m_window = nullptr;

	CComPtr<ID2D1Factory>						m_pDirect2dFactory;
	CComPtr<ID2D1HwndRenderTarget>				m_pRenderTarget;

	CComPtr<ID2D1SolidColorBrush>				m_fillBrush;;
	CComPtr<ID2D1SolidColorBrush>				m_outlineBrush;
	CComPtr<ID2D1PathGeometry>					m_pathGeometry;
	CComPtr<ID2D1GeometrySink>					m_geometrySink;

	CComPtr<ID2D1SolidColorBrush>				m_pLightSlateGrayBrush;
	CComPtr<ID2D1SolidColorBrush>				m_pCornflowerBlueBrush;

};