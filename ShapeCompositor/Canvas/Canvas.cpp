#include "stdafx.h"
#include "Canvas.h"
#include "../ShapeCompositorView.h"

CCanvas::CCanvas()
	: m_shapeFactory(this)
	, m_selectShape(m_shapeRenderer, m_shapeFactory)
{
}



HRESULT CCanvas::Render()
{
	/*
		D2D1_RECT_F rectangle2 = D2D1::RectF(
		2 - 100.0f,
		2 - 100.0f,
		2 + 100.0f,
		2 + 100.0f
	);

	// Draw the outline of a rectangle.
	m_pRenderTarget->DrawRectangle(&rectangle2, m_pCornflowerBlueBrush, 2.9f);

	*/

	return RenderShapes();
}

HRESULT CCanvas::CreateRecources(CShapeCompositorView * window)
{
	return m_shapeRenderer.CreateRecources(window);
}

void CCanvas::ClearRecources()
{
	m_shapeRenderer.ClearRecources();
}

void CCanvas::AddShape(TypeShape type)
{
	m_shapeFactory.CreateShape(
		type
		, Vec2f(float(VIEW_WIDTH) / 2.f, float(VIEW_HEIGHT) / 2.f)
		, SShapeData()
		, m_shapeLayer
		, m_shapeRenderer
	);
}

void CCanvas::DeleteShape(CShapePresenterPtr pShape)
{
	m_shapeLayer.DeleteShape(pShape);
}

void CCanvas::DeleteLastShape()
{
	m_shapeLayer.DeleteLastShape();
}

CShapePresenterPtr CCanvas::GetShapePresenter(const Vec2f mousePosition)
{
	return m_shapeLayer.GetShapePreseneter(mousePosition);
}


HRESULT CCanvas::RenderShapes()
{
	for (const auto & shape : m_shapeLayer.GetShapesData())////m_shapeRenderer.m_renderShapes
	{
		shape->Accept(m_shapeRenderer);
	}
	m_shapeRenderer.m_renderShapes.clear();

	

	return m_shapeRenderer.EndDraw();
}
