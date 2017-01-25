#include "stdafx.h"
#include "Canvas.h"
#include "../ShapeCompositorView.h"

CCanvas::CCanvas()//HWND *pHwnd)
	//: m_pWindow(pHwnd)
{
}


void CCanvas::SetHwnd(CShapeCompositorView * pHwnd)
{
	m_pWindow = pHwnd;
}

