#include "stdafx.h"
#include "ShapeFactory.h"

CShapePtr CShapeFactory::CreateShape(const SShapeData & data)
{
	switch (data.type)
	{
	case ShapeType::Triangle:
		return std::make_shared<CTriangle>(
			data.position,
			data.size,
			data.fillColor,
			data.outlineColor,
			data.outlineThikness
			);
	case ShapeType::Rectangle:
		return std::make_shared<CRectangle>(
			data.position,
			data.size,
			data.fillColor,
			data.outlineColor,
			data.outlineThikness
			);
	case ShapeType::Ellipse:
		return std::make_shared<CEllipse>(
			data.position,
			data.size,
			data.fillColor,
			data.outlineColor,
			data.outlineThikness
			);
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	};
}