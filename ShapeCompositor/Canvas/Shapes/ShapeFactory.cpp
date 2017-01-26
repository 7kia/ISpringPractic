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
		return std::make_shared<CTriangleShape>(position, DEFAULT_SIZE, DEFAULT_COLOR, DEFAULT_COLOR);
		break;
	case TypeShape::Rectangle:
		return std::make_shared<CRectangleShape>(position, DEFAULT_SIZE, DEFAULT_COLOR, DEFAULT_COLOR);
		break;
	case TypeShape::Circle:
		return std::make_shared<CCircleShape>(position, DEFAULT_SIZE, DEFAULT_COLOR, DEFAULT_COLOR);
		break;
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	}

	//return PCShape();
}
