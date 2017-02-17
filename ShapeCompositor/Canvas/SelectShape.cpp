#include "stdafx.h"
#include "SelectShape.h"

CSelectShape::CSelectShape(CShapeRender & shapeRenderer, const CShapeFactory & shapeFactory)
	: IDrawable()
{
	SShapeData rectangleData;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	shapeFactory.CreateShape(TypeShape::Rectangle, rectangleData, m_moveShape, shapeRenderer);

	
	SShapeData ellipseData;
	ellipseData.outlineColor = BLACK_COLOR;
	ellipseData.fillColor = BLACK_COLOR;

	for (size_t index = 0; index < 4; ++index)
	{
		shapeFactory.CreateShape(TypeShape::Ellipse, ellipseData, m_resizeShapes, shapeRenderer);
	}
}

void CSelectShape::SetShape(CShapePtr shape)
{
	m_selectShape = shape;
	m_frameData = shape->GetShapeData();

	SetViewPosition();
}

CShapePtr CSelectShape::GetShape() const
{
	return m_selectShape;
}

void CSelectShape::ResetSelectShapePtr()
{
	m_selectShape = nullptr;
}

void CSelectShape::Draw(IRenderShape & renderer) const
{
	if (m_selectShape != nullptr)
	{
		for (auto & shape : m_moveShape)
		{
			shape->Draw(renderer);
		}
		for (auto & shape : m_resizeShapes)
		{
			shape->Draw(renderer);
		}
	}
}

void CSelectShape::SetViewPosition()
{
	SetMoveView();
	SetResizeView();
}

void CSelectShape::SetMoveView()
{
	SShapeData rectangleData = m_frameData;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	m_moveShape[0]->SetShapeData(rectangleData);

}

void CSelectShape::SetResizeView()
{
	auto vertices = m_selectShape->GetFrameVertices();
	size_t indexEllipse = 0;
	for (const auto & vertex : vertices)
	{
		SShapeData ellipseData;
		ellipseData.position = vertex;
		ellipseData.size = SELECTED_ELLIPSE_SIZE;
		ellipseData.outlineColor = BLACK_COLOR;
		ellipseData.fillColor = BLACK_COLOR;

		m_resizeShapes[indexEllipse++]->SetShapeData(ellipseData);
	}
}
