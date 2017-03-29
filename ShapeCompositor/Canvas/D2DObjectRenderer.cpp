#include "stdafx.h"
#include "D2DObjectRenderer.h"
#include "../ShapeCompositorView.h"
#include "Canvas.h"
#include "SelectedShape.h"

CD2DObjectRenderer::CD2DObjectRenderer()
	: IShapeVisitor()
	, IShapeRenderer()
{
}

HRESULT CD2DObjectRenderer::CreateRecources(CShapeCompositorView * window)
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

void CD2DObjectRenderer::ClearRecources()
{
	SafeRelease(&m_pRenderTarget);
	SafeRelease(&m_pDirect2dFactory);
}

HRESULT CD2DObjectRenderer::EndDraw()
{
	return m_pRenderTarget->EndDraw();
}

void CD2DObjectRenderer::Draw(const IShape & shape)
{
	shape.Accept(*this);
}


void CD2DObjectRenderer::Visit(const CRectangle & shape)
{
	auto vertices = shape.GetVertices();

	Color fillColor = shape.GetFillColor();
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(fillColor.r, fillColor.g, fillColor.b, fillColor.a)),
		&m_fillBrush
	);

	Color outlineColor = shape.GetOutlineColor();
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a)),
		&m_outlineBrush
	);

	m_pDirect2dFactory->CreatePathGeometry(&m_pathGeometry);
	m_pathGeometry->Open(&m_geometrySink);
	m_geometrySink->BeginFigure({ vertices[0].x, vertices[0].y }, D2D1_FIGURE_BEGIN_FILLED);
	for (size_t i = 1; i < vertices.size(); ++i)
	{
		m_geometrySink->AddLine({ vertices[i].x, vertices[i].y });
	}
	m_geometrySink->EndFigure(D2D1_FIGURE_END_CLOSED);
	m_geometrySink->Close();
	m_pRenderTarget->FillGeometry(m_pathGeometry, m_fillBrush);
	m_pRenderTarget->DrawGeometry(m_pathGeometry, m_outlineBrush);

	m_fillBrush.Release();
	m_outlineBrush.Release();
	m_pathGeometry.Release();
	m_geometrySink.Release();
}

void CD2DObjectRenderer::Visit(const CEllipse & shape)
{
	auto position = shape.GetPosition();
	SSize size = shape.GetSize();

	Color fillColor = shape.GetFillColor();
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(fillColor.r, fillColor.g, fillColor.b, fillColor.a)),
		&m_fillBrush
	);

	Color outlineColor = shape.GetOutlineColor();
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a)),
		&m_outlineBrush
	);

	D2D1_ELLIPSE ellipse = D2D1::Ellipse(
		{ position.x, position.y }
		, size.width / 2.f
		, size.height / 2.f
	);
	m_pRenderTarget->FillEllipse(ellipse, m_fillBrush);
	m_pRenderTarget->DrawEllipse(ellipse, m_outlineBrush);

	m_fillBrush.Release();
	m_outlineBrush.Release();
}

void CD2DObjectRenderer::Visit(const CTriangle & shape)
{
	auto vertices = shape.GetVertices();

	Color fillColor = shape.GetFillColor();
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(fillColor.r, fillColor.g, fillColor.b, fillColor.a)),
		&m_fillBrush
	);

	Color outlineColor = shape.GetOutlineColor();
	m_pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a)),
		&m_outlineBrush
	);

	m_pDirect2dFactory->CreatePathGeometry(&m_pathGeometry);
	m_pathGeometry->Open(&m_geometrySink);
	m_geometrySink->BeginFigure({ vertices[0].x, vertices[0].y }, D2D1_FIGURE_BEGIN_FILLED);
	for (size_t i = 1; i < vertices.size(); ++i)
	{
		m_geometrySink->AddLine({ vertices[i].x, vertices[i].y });
	}
	m_geometrySink->EndFigure(D2D1_FIGURE_END_CLOSED);
	m_geometrySink->Close();
	m_pRenderTarget->FillGeometry(m_pathGeometry, m_fillBrush);
	m_pRenderTarget->DrawGeometry(m_pathGeometry, m_outlineBrush);

	m_fillBrush.Release();
	m_outlineBrush.Release();
	m_pathGeometry.Release();
	m_geometrySink.Release();
}

void CD2DObjectRenderer::Visit(const CBuilding & shape)
{
	const SSize size = shape.GetSize();
	const Vec2f position = shape.GetPosition();
	auto shapeType = shape.GetBuildingType();

	const auto frame = GetFrameRect(shape);
	auto rectangle = D2D1::RectF(
		frame.left
		, frame.top
		, frame.right
		, frame.bottom
	);
	m_pRenderTarget->DrawBitmap(shapeType->GetTexture(), rectangle);

}

void CD2DObjectRenderer::Visit(const CPicture & shape)
{
	auto vertices = shape.GetVertices();

	const SSize size = shape.GetSize();
	const Vec2f position = shape.GetPosition();
	auto rectangle = D2D1::RectF(
		position.x - size.width / 2.f
		, position.y - size.height / 2.f
		, size.width
		, size.height
	);

	m_pRenderTarget->DrawBitmap(shape.GetTexture(), rectangle);
}

