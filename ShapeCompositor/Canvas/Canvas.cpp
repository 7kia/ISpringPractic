#include "stdafx.h"
#include "Canvas.h"
#include "../ShapeCompositorView.h"

CCanvas::CCanvas()
{
}



HRESULT CCanvas::Render()
{
	D2D1_RECT_F rectangle2 = D2D1::RectF(
		2 - 100.0f,
		2 - 100.0f,
		2 + 100.0f,
		2 + 100.0f
	);

	// Draw the outline of a rectangle.
	m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush);

	return m_pRenderTarget->EndDraw();
}

HRESULT CCanvas::CreateRecources(CShapeCompositorView * window)
{
	ATLENSURE_SUCCEEDED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory));

	m_window = window;
	m_pRenderTarget = m_window->GetRenderTarget();

	HRESULT hr = S_OK;

	if (!m_pRenderTarget)
	{
		RECT rc;
		m_window->GetClientRect(&rc);// TODO : see can it rewrite

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
		);

		// Create a Direct2D render target.
		hr = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(window->m_hWnd, size),
			&m_pRenderTarget
		);

		window->SetRenderTarget(m_pRenderTarget);
	}

	// Create a gray brush.
	hr = m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::LightSlateGray),
		&m_pLightSlateGrayBrush
	);

	// Create a blue brush.
	hr = m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::CornflowerBlue),
		&m_pCornflowerBlueBrush
	);

	return hr;
}

void CCanvas::RenderShapes()
{
	for (const auto & shape : m_shapes)
	{

	}
}

