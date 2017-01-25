#pragma once

#include <memory>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <afxwin.h>


class CShapeCompositorView;

class CCanvas
{
public:
	CCanvas();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	HRESULT		Render();

	HRESULT		CreateRecources(ID2D1HwndRenderTarget * renderTarget);
	//////////////////////////////////////////////////////////////////////
	// Data
public:
	class CController;
	std::unique_ptr<CController>				m_controller;

	// TODO : delete it
	// TODO : transfer

	CComPtr<ID2D1SolidColorBrush>						m_pLightSlateGrayBrush;
	CComPtr<ID2D1SolidColorBrush>						m_pCornflowerBlueBrush;

private:

	// TODO : add
	// Shapes
	// ShapeFactory
	// D2DFactory

	ID2D1HwndRenderTarget * m_pRenderTarget = nullptr;

};

class CCanvas::CController
{
public:
	CController();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

};