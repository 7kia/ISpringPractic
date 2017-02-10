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
	, const SShapeData & data
	, CShapeLayer & layer
	, CShapeRender & shapeRenderer
) const
{
	CShapeDataPtr lastData;
	CShapePresenterPtr lastPresenter;
	// TODO : fix transfer by use pack
	switch (type)
	{
	case TypeShape::Triangle:
		layer.PushBackShapeData(std::make_shared<CTriangleShapeData>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			));

		layer.PushBackShapePreseneter(std::make_shared<CTrianglePresenter>(
			data.position
			, data.size
			));

		BindPresenterWithModel(layer, shapeRenderer);
		break;
	case TypeShape::Rectangle:
		layer.PushBackShapeData(std::make_shared<CRectangleShapeData>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			));
		layer.PushBackShapePreseneter(std::make_shared<CRectanglePresenter>(
			data.position
			, data.size
			));

		BindPresenterWithModel(layer, shapeRenderer);
		break;
	case TypeShape::Ellipse:
		layer.PushBackShapeData(std::make_shared<CEllipseDataShape>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			));
		layer.PushBackShapePreseneter(std::make_shared<CEllipsePresenter>(
			data.position
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
