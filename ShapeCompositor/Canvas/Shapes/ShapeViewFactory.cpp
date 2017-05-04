#include "stdafx.h"
#include "ShapeViewFactory.h"

CShapeViewPtr CShapeViewFactory::CreateShape(const CShapeModel & data)
{
	switch (data.type)
	{
	case ShapeType::Triangle:
		return std::make_shared<CTriangleView>(
			data.GetPosition(),
			data.GetSize(),
			data.GetFillColor(),
			data.GetOutlineColor(),
			data.GetOutlineThickness()
			);
	case ShapeType::Rectangle:
		return std::make_shared<CRectangleView>(
			data.GetPosition(),
			data.GetSize(),
			data.GetFillColor(),
			data.GetOutlineColor(),
			data.GetOutlineThickness()
			);
	case ShapeType::Ellipse:
		return std::make_shared<CEllipseView>(
			data.GetPosition(),
			data.GetSize(),
			data.GetFillColor(),
			data.GetOutlineColor(),
			data.GetOutlineThickness()
			);
	case ShapeType::Picture:
		auto pictureModel = dynamic_cast<CPictureModel*>(&data);
		return std::make_shared<CPictureView>(
			pictureModel->GetTexture(),
			pictureModel->GetPosition(),
			pictureModel->GetSize()
			);
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	};
}