#pragma once

#include "Canvas\Shapes\AllShapes.h"

class CShapeCompositorView;
class CCanvas;

class IObjectRenderer
{
public:
	virtual ~IObjectRenderer() = default;

	virtual void Draw(const IDrawable & shape) = 0;
};

class CD2DObjectRenderer
	: public IObjectVisitor
	, public IObjectRenderer
{
public:
	CD2DObjectRenderer();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	HRESULT CreateRecources(CShapeCompositorView * window);
	void	ClearRecources();

	HRESULT	EndDraw();
	//--------------------------------------------
	// IObjectVisitor
	void Draw(const IDrawable & shape) override;
	//--------------------------------------------

private:
	//--------------------------------------------
	// IObjectVisitor

	void Visit(const CRectangle & shape) override;
	void Visit(const CEllipse & shape) override;
	void Visit(const CTriangle & shape) override;

	//--------------------------------------------

	void Visit(const CCanvas & canvas);// TODO : see need interface for canvas

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