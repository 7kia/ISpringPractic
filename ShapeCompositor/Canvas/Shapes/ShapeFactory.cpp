#include "stdafx.h"
#include "ShapeFactory.h"

CShapeFactory::CShapeFactory()
{
}

CShapePtr CShapeFactory::CreateShape(const SShapeData & data) const
{
	switch (data.type)
	{
	case ShapeType::Triangle:
		return std::make_shared<CTriangle>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			);
	case ShapeType::Rectangle:
		return std::make_shared<CRectangle>(
			data.position
			, data.size
			, data.fillColor
			, data.outlineColor
			);
	case ShapeType::Ellipse:
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