#include "stdafx.h"
#include "../Canvas.h"
#include "ShapeFactory.h"

CShapeFactory::CShapeFactory(CCanvas * pCanvas)
	: IShapeFactory()
	, m_pCanvas(pCanvas)
{
}

PCShape CShapeFactory::CreateShape(TypeShape type, const Vec2f position)
{
	PCShape createShape;

	switch (type)
	{
	case TypeShape::Triangle:
		createShape = std::make_shared<CTriangleShape>(position, DEFAULT_SIZE, DEFAULT_FILL_COLOR, DEFAULT_OUTLINE_COLOR);
		//createShape->OnUpdate.connect(boost::bind(createShape->IsPointIntersection),)
		return createShape;
		break;
	case TypeShape::Rectangle:
		return std::make_shared<CRectangleShape>(position, DEFAULT_SIZE, DEFAULT_FILL_COLOR, DEFAULT_OUTLINE_COLOR);
		break;
	case TypeShape::Ellipse:
		return std::make_shared<CEllipseDataShape>(position, DEFAULT_SIZE, DEFAULT_FILL_COLOR, DEFAULT_OUTLINE_COLOR);
		break;
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	}

	//return PCShape();
}
