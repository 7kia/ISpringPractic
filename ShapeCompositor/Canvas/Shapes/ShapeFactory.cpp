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
	, const SShapeData & data
	, CShapeLayer & layer
	, CShapeRender & shapeRenderer
) const
{
	CShapeDataPtr lastData;
	CShapePresenterPtr lastPresenter;
	switch (type)
	{
	case TypeShape::Triangle:
		layer.PushBackShapeData(std::make_shared<CTriangleShapeData>(
			position
			, data.size
			, data.fillColor
			, data.outlineColor
			));

		layer.PushBackShapePreseneter(std::make_shared<CTrianglePresenter>(
			position
			, data.size
			));

		BindPresenterWithModel(layer, shapeRenderer);
		break;
	case TypeShape::Rectangle:
		layer.PushBackShapeData(std::make_shared<CRectangleShapeData>(
			position
			, data.size
			, data.fillColor
			, data.outlineColor
			));
		layer.PushBackShapePreseneter(std::make_shared<CRectanglePresenter>(
			position
			, data.size
			));

		BindPresenterWithModel(layer, shapeRenderer);
		break;
	case TypeShape::Ellipse:
		layer.PushBackShapeData(std::make_shared<CEllipseDataShape>(
			position
			, data.size
			, data.fillColor
			, data.outlineColor
			));
		layer.PushBackShapePreseneter(std::make_shared<CEllipsePresenter>(
			position
			, data.size
			));

		BindPresenterWithModel(layer, shapeRenderer);
		break;
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	}

	//return CShapeDataPtr();
}

void CShapeFactory::BindPresenterWithModel(CShapeLayer & layer, CShapeRender & shapeRenderer) const
{
	CShapeDataPtr lastData = layer.GetBackShapeData();
	CShapePresenterPtr lastPresenter = layer.GetBackShapePreseneter();

	lastPresenter->RegisterObserver(*lastData.get());
	lastData->RegisterObserver(shapeRenderer);
}
