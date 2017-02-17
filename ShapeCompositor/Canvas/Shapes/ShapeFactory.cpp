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
	, std::vector<CShapePtr> & shapes
	, CShapeRender & shapeRenderer
) const
{
	switch (type)
	{
	case TypeShape::Triangle:
		shapes.push_back(std::make_shared<CTriangle>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			));

		break;
	case TypeShape::Rectangle:
		shapes.push_back(std::make_shared<CRectangle>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			));

		break;
	case TypeShape::Ellipse:
		shapes.push_back(std::make_shared<CEllipse>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			));

		break;
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	}
}