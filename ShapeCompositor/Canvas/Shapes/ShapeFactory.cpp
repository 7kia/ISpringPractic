#include "stdafx.h"
#include "ShapeFactory.h"

CShapeFactory::CShapeFactory()
	: IShapeFactory()
{
}

PCShape CShapeFactory::CreateShape(TypeShape type, const Vec2f position)
{
	PCShape createShape;

	switch (type)
	{
	case TypeShape::Triangle:
		return std::make_shared<CTriangleShape>(position, DEFAULT_SIZE, DEFAULT_FILL_COLOR, DEFAULT_OUTLINE_COLOR);
		break;
	case TypeShape::Rectangle:
		return std::make_shared<CRectangleShape>(position, DEFAULT_SIZE, DEFAULT_FILL_COLOR, DEFAULT_OUTLINE_COLOR);
		break;
	case TypeShape::Ellipse:
		return std::make_shared<CEllipseShape>(position, DEFAULT_SIZE, DEFAULT_FILL_COLOR, DEFAULT_OUTLINE_COLOR);
		break;
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	}

	//return PCShape();
}
