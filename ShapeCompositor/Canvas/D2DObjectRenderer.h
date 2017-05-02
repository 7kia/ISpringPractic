#pragma once

#include "Canvas\ObjectRenderer.h"
#include "Canvas\Picture\Picture.h"

class CD2DObjectRenderer
	: public IShapeVisitor
	, public IShapeRenderer
{
public:
	CD2DObjectRenderer();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	ID2D1HwndRenderTarget *	CreateRenderTarget(CWnd * window);
	HRESULT CreateRecources();

	HRESULT	EndDraw();
	//--------------------------------------------
	// IShapeRenderer
	void Draw(const IShape & shape) override;
	//--------------------------------------------
private:
	//--------------------------------------------
	// IShapeVisitor
	void Visit(const CRectangle & shape) override;
	void Visit(const CEllipse & shape) override;
	void Visit(const CTriangle & shape) override;
	void Visit(const CPicture & shape) override;
	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CComPtr<ID2D1Factory>						m_pDirect2dFactory;
	ID2D1HwndRenderTarget *						m_pRenderTarget;

	CComPtr<ID2D1SolidColorBrush>				m_fillBrush;;
	CComPtr<ID2D1SolidColorBrush>				m_outlineBrush;
	CComPtr<ID2D1PathGeometry>					m_pathGeometry;
	CComPtr<ID2D1GeometrySink>					m_geometrySink;

	CComPtr<ID2D1SolidColorBrush>				m_pLightSlateGrayBrush;
	CComPtr<ID2D1SolidColorBrush>				m_pCornflowerBlueBrush;

};