#pragma once

#include <memory>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

class CCanvas
{
public:
	CCanvas(HWND *pHwnd);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	HRESULT	OnRender();
	HRESULT CreateDeviceResources();
	void	OnResize(UINT width, UINT height);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	class CController;
	std::unique_ptr<CController>				m_controller;

	CComPtr<ID2D1Factory>				m_pDirect2dFactory;
	CComPtr<ID2D1HwndRenderTarget>		m_pRenderTarget;

	// TODO : add
	// Shapes
	// ShapeFactory
	// D2DFactory

	// TODO : see need it
	HWND *	m_pHwnd = nullptr;
	CComPtr<ID2D1SolidColorBrush>						m_pLightSlateGrayBrush;
	CComPtr<ID2D1SolidColorBrush>						m_pCornflowerBlueBrush;

};

class CCanvas::CController
{
public:
	CController();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

};