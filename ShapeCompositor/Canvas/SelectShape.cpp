#include "stdafx.h"
#include "SelectShape.h"

CSelectShape::CSelectShape(CShapeRender & shapeRenderer, const CShapeFactory & shapeFactory)
{
	SShapeData rectangleData;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	shapeFactory.CreateShape(TypeShape::Rectangle, Vec2f(), rectangleData, m_moveShape, shapeRenderer);

	
	SShapeData ellipseData;
	ellipseData.outlineColor = BLACK_COLOR;
	ellipseData.fillColor = BLACK_COLOR;

	for (size_t index = 0; index < 4; ++index)
	{
		shapeFactory.CreateShape(TypeShape::Ellipse, Vec2f(), ellipseData, m_resizeShape, shapeRenderer);
	}
}

void CSelectShape::SetShape(CShapePresenter * shape)
{
	m_selectPresenter = shape;
	m_frameData = shape->GetChangedData();
	shape->Update(m_frameData);// TODO : delete

	SetViewPosition();
}

CShapePresenter * CSelectShape::GetShape() const
{
	return m_selectPresenter;
}

void CSelectShape::ResetSelectShapePtr()
{
	m_selectPresenter = nullptr;
}

void CSelectShape::Render()
{
	if (m_selectPresenter != nullptr)
	{	
		for (auto & shape : m_moveShape.GetShapesData())
		{
			shape->NotifyObservers();
		}
		for (auto & shape : m_resizeShape.GetShapesData())
		{
			shape->NotifyObservers();
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

	m_moveShape.GetShapePreseneter(0)->Update(rectangleData);

}

void CSelectShape::SetResizeView()
{
	auto vertices = m_selectPresenter->GetFrameVertices();
	size_t indexEllipse = 0;
	for (const auto & vertex : vertices)
	{
		SShapeData ellipseData;
		ellipseData.position = vertex;
		ellipseData.size = SELECTED_ELLIPSE_SIZE;
		ellipseData.outlineColor = BLACK_COLOR;
		ellipseData.fillColor = BLACK_COLOR;

		m_resizeShape.GetShapePreseneter(indexEllipse++)->Update(ellipseData);
	}
}
