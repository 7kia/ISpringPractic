#include "stdafx.h"
#include "SelectShape.h"

CSelectShape::CSelectShape(CD2DObjectRenderer & shapeRenderer, const CShapeFactory & shapeFactory)
	: IDrawable()
{
	SShapeData rectangleData;
	rectangleData.type = TypeShape::Rectangle;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	m_moveShape.push_back(shapeFactory.CreateShape(rectangleData, shapeRenderer));
	
	SShapeData ellipseData;
	ellipseData.type = TypeShape::Ellipse;
	ellipseData.outlineColor = BLACK_COLOR;
	ellipseData.fillColor = BLACK_COLOR;

	for (size_t index = 0; index < 4; ++index)
	{
		m_resizeShapes.push_back(shapeFactory.CreateShape(ellipseData, shapeRenderer));
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

void CSelectShape::Accept(IShapeVisitor & renderer) const
{
	if (m_selectShape != nullptr)
	{
		for (auto & shape : m_moveShape)
		{
			shape->Accept(renderer);
		}
		for (auto & shape : m_resizeShapes)
		{
			shape->Accept(renderer);
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
