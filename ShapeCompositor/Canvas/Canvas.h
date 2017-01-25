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

	void		SetHwnd(CShapeCompositorView * pWindow);

	//////////////////////////////////////////////////////////////////////
	// Data
public:
	class CController;
	std::unique_ptr<CController>				m_controller;


	//ID2D1HwndRenderTarget
	//
private:

	// TODO : add
	// Shapes
	// ShapeFactory
	// D2DFactory

	// TODO : see need it
	CShapeCompositorView *	m_pWindow = nullptr;

};

class CCanvas::CController
{
public:
	CController();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

};