#include "stdafx.h"
#include "../Canvas.h"
#include "ShapeFactory.h"

CShapeFactory::CShapeFactory(CCanvas * pCanvas)
	: IShapeFactory()
	, m_pCanvas(pCanvas)
{
}

void CShapeFactory::CreateShape(
	TypeShape type
	, const Vec2f position
	, CShapeLayer & layer
	, CShapeRender & shapeRenderer
)
{
	CShapeDataPtr lastData;
	CShapePresenterPtr lastPresenter;
	switch (type)
	{
	case TypeShape::Triangle:
		layer.PushBackShapeData(std::make_shared<CTriangleShapeData>(
			position
			, DEFAULT_SIZE
			, DEFAULT_FILL_COLOR
			, DEFAULT_OUTLINE_COLOR
			));

		layer.PushBackShapePreseneter(std::make_shared<CTrianglePresenter>(
			position
			, DEFAULT_SIZE
			));

		BindPresenterWithModel(layer, shapeRenderer);
		break;
	case TypeShape::Rectangle:
		layer.PushBackShapeData(std::make_shared<CRectangleShapeData>(
			position
			, DEFAULT_SIZE
			, DEFAULT_FILL_COLOR
			, DEFAULT_OUTLINE_COLOR
			));
		layer.PushBackShapePreseneter(std::make_shared<CRectanglePresenter>(
			position
			, DEFAULT_SIZE
			));

		BindPresenterWithModel(layer, shapeRenderer);
		break;
	case TypeShape::Ellipse:
		layer.PushBackShapeData(std::make_shared<CEllipseDataShape>(
			position
			, DEFAULT_SIZE
			, DEFAULT_FILL_COLOR
			, DEFAULT_OUTLINE_COLOR
			));
		layer.PushBackShapePreseneter(std::make_shared<CEllipsePresenter>(
			position
			, DEFAULT_SIZE
			));

		BindPresenterWithModel(layer, shapeRenderer);
		break;
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	}

	//return CShapeDataPtr();
}

void CShapeFactory::BindPresenterWithModel(CShapeLayer & layer, CShapeRender & shapeRenderer)
{
	CShapeDataPtr lastData = layer.GetBackShapeData();
	CShapePresenterPtr lastPresenter = layer.GetBackShapePreseneter();

	lastPresenter->RegisterObserver(*lastData.get());
	lastData->RegisterObserver(shapeRenderer);
}
