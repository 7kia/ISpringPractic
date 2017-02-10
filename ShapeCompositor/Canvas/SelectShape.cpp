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

void CSelectShape::SetShape(CShapePresenterPtr shape)
{
	m_selectPresenter = shape;
	m_frameData = shape->GetChangedData();
	shape->Update(m_frameData);// TODO : delete

	SetViewPosition();
}

CShapePresenterPtr CSelectShape::GetShape() const
{
	return CShapePresenterPtr(m_selectPresenter);
}

void CSelectShape::ResetSelectShapePtr()
{
	m_selectPresenter.reset();
}

void CSelectShape::Render()
{
	if (!m_selectPresenter.expired())
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
	m_moveShape.GetShapePreseneter(0)->Update(m_frameData);

	Vec2f position = m_frameData.position;
	SSize size = m_frameData.size;


	auto vertices = {
		Vec2f(position.x - size.width / 2.f, position.y + size.height / 2.f)// Left bootom
		, Vec2f(position.x + size.width / 2.f, position.y + size.height / 2.f)// Right bootom
		, Vec2f(position.x + size.width / 2.f, position.y - size.height / 2.f)// Right top
		, Vec2f(position.x - size.width / 2.f, position.y - size.height / 2.f)// Left top
	};

	size_t indexEllipse = 0;
	for (const auto & vertex : vertices)
	{
		m_resizeShape.GetShapePreseneter(indexEllipse)->Update(SPresenterData(vertex, SELECTED_ELLIPSE_SIZE));
	}
}
