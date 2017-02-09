#include "stdafx.h"
#include "SelectShape.h"

CSelectShape::CSelectShape(CShapeRender & shapeRenderer, const CShapeFactory & shapeFactory)
	: CObservable<SPresenterData>()
{
	SShapeData rectangleData;
	rectangleData.outlineColor = BLACK_COLOR;
	rectangleData.fillColor = NOT_COLOR;

	shapeFactory.CreateShape(TypeShape::Rectangle, Vec2f(), rectangleData, m_frameLayer, shapeRenderer);

	
	SShapeData ellipseData;
	ellipseData.outlineColor = BLACK_COLOR;
	ellipseData.fillColor = BLACK_COLOR;

	for (size_t index = 0; index < 4; ++index)
	{
		shapeFactory.CreateShape(TypeShape::Ellipse, Vec2f(), ellipseData, m_frameLayer, shapeRenderer);
	}

	// TODO : notify renderer
	//RegisterObserver(shapeRenderer);
}

void CSelectShape::SetShape(CShapePresenterPtr shape)
{

	if (shape != m_selectPresenter.lock())
	{
		if (!m_selectPresenter.expired())
		{
			RemoveObserver(*m_selectPresenter.lock().get());
		}

		RegisterObserver(*shape.get());
	}

	m_selectPresenter = shape;
	m_frameData = shape->GetChangedData();

	SetViewPosition();
}

CShapePresenterPtr CSelectShape::GetShape() const
{
	return CShapePresenterPtr(m_selectPresenter);
}

SPresenterData CSelectShape::GetChangedData() const
{ 
	return m_frameData;
}

void CSelectShape::Render()
{
}

void CSelectShape::SetViewPosition()
{
	m_frameLayer.GetShapePreseneter(0)->Update(m_frameData);

	Vec2f position = m_frameData.position;
	SSize size = m_frameData.size;


	auto vertices = {
		Vec2f(position.x - size.width / 2.f, position.y + size.height / 2.f)// Left bootom
		, Vec2f(position.x + size.width / 2.f, position.y + size.height / 2.f)// Right bootom
		, Vec2f(position.x + size.width / 2.f, position.y - size.height / 2.f)// Right top
		, Vec2f(position.x - size.width / 2.f, position.y - size.height / 2.f)// Left top
	};

	size_t indexEllipse = 1;
	for (const auto & vertex : vertices)
	{
		m_frameLayer.GetShapePreseneter(0)->Update(SPresenterData(vertex, SELECTED_ELLIPSE_SIZE));
	}
}
