#pragma once

#include <memory>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <afxwin.h>

#include <vector>

#include "Shapes\RectangleShape.h"

class CShapeCompositorView;

class CCanvas
{
public:
	CCanvas();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	HRESULT		Render();

	HRESULT		CreateRecources(CShapeCompositorView * window);

private:
	void		RenderShapes();

	//////////////////////////////////////////////////////////////////////
	// Data
public:
	class CController;
	std::unique_ptr<CController>				m_controller;

	CComPtr<ID2D1Factory>						m_pDirect2dFactory;
	CComPtr<ID2D1HwndRenderTarget>				m_pRenderTarget;

	// TODO : delete it
	// TODO : transfer

	CComPtr<ID2D1SolidColorBrush>						m_pLightSlateGrayBrush;
	CComPtr<ID2D1SolidColorBrush>						m_pCornflowerBlueBrush;

private:

	// TODO : add
	// Shapes
	// ShapeFactory
	// D2DFactory

	CShapeCompositorView *	m_window = nullptr;
	std::vector<PCShape>	m_shapes;
};

class CCanvas::CController
{
public:
	CController();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

};