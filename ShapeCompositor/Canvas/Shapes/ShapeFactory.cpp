#include "stdafx.h"
#include "../Canvas.h"
#include "ShapeFactory.h"

CShapeFactory::CShapeFactory()
{
}

CShapePtr CShapeFactory::CreateShape(
	TypeShape type
	, const SShapeData & data
	, CShapeRender & shapeRenderer
) const
{
	switch (type)
	{
	case TypeShape::Triangle:
		return std::make_shared<CTriangle>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			);
	case TypeShape::Rectangle:
		return std::make_shared<CRectangle>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			);
	case TypeShape::Ellipse:
		return std::make_shared<CEllipse>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			);
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	};
}