#include "stdafx.h"
#include "Canvas.h"
#include "../ShapeCompositorView.h"

CCanvas::CCanvas()
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


void CCanvas::AddShape(TypeShape type)
{
	m_shapes.push_back(m_shapeFactory.CreateShape(
		type, 
		Vec2f(float(VIEW_WIDTH) / 2.f, float(VIEW_HEIGHT) / 2.f)
	));
}

void CCanvas::DeleteShape(PCShape pShape)
{
	// TODO : the code might will be need to other place
	size_t deleteIndex = std::find(m_shapes.begin(), m_shapes.end(), pShape) - m_shapes.begin();

	m_shapes.erase(m_shapes.begin() + deleteIndex);
}

void CCanvas::DeleteLastShape()
{
	m_shapes.pop_back();
}

HRESULT CCanvas::RenderShapes()
{
	for (const auto & shape : m_shapes)
	{
		shape->Accept(m_shapeRenderer);
	}

	return m_shapeRenderer.EndDraw();
}
