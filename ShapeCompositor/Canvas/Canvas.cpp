#include "stdafx.h"
#include "Canvas.h"
#include "../ShapeCompositorView.h"

CCanvas::CCanvas()
	: IRenderShapeVisitor()
{
	{
		/*
				auto rectangle = std::make_shared<CRectangleShape>(90.f, 25.f);
		rectangle->SetPosition(Vec2f(200.f, 200.f));
		rectangle->SetOutlineColor(Color(0.25f, 0.25f, 0.25f));
		rectangle->SetFillColor(Color(0.55f, 0.55f, 0.55f));

		*/

		m_shapes.push_back(m_shapeFactory.CreateShape(TypeShape::Rectangle, Vec2f(200.f, 200.f)));
	}

	{
		/*
		auto circle = std::make_shared<CEllipseShape>();

		circle->SetPosition(Vec2f(250.f, 200.f));
		circle->SetRadius(20.f);
		circle->SetOutlineColor(Color(0.25f, 0.25f, 0.25f));
		circle->SetFillColor(Color(0.55f, 0.55f, 0.55f));
		*/

		m_shapes.push_back(m_shapeFactory.CreateShape(TypeShape::Ellipse, Vec2f(250.f, 200.f)));
	}

	{
		/*
		auto triangle = std::make_shared<CTriangleShape>(Vec2f(250.f, 250.f), 25.f, 54.f);

		triangle->SetOutlineColor(Color(0.25f, 0.25f, 0.25f));
		triangle->SetFillColor(Color(0.85f, 0.55f, 0.25f));
		*/

		m_shapes.push_back(m_shapeFactory.CreateShape(TypeShape::Triangle, Vec2f(250.f, 250.f)));
	}

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

	RenderShapes();

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

void CCanvas::AddShape(TypeShape type)
{
	m_shapes.push_back(m_shapeFactory.CreateShape(
		type, 
		Vec2f(float(VIEW_WIDTH) / 2.f, float(VIEW_HEIGHT) / 2.f)
	));
}

void CCanvas::RenderShapes()
{
	for (const auto & shape : m_shapes)
	{
		shape->Accept(*this);
	}
}

void CCanvas::Visit(const CRectangleShape & shape)
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

void CCanvas::Visit(const CEllipseShape & shape)
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
		, size.width
		, size.height
	);
	m_pRenderTarget->FillEllipse(ellipse, m_fillBrush);
	m_pRenderTarget->DrawEllipse(ellipse, m_outlineBrush);

	m_fillBrush.Release();
	m_outlineBrush.Release();

}

void CCanvas::Visit(const CTriangleShape & shape)
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