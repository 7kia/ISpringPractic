#include "stdafx.h"
#include "ShapeViewFactory.h"
#include "Presenter/ShapePresenter.h"

CShapeViewPtr CShapeViewFactory::CreateShape(CShapeModelPtr & data)
{
	switch (data->GetType())
	{
	case ShapeType::Triangle:
		return std::make_shared<CTriangleView>(
			data->GetPosition(),
			data->GetSize(),
			data->GetFillColor(),
			data->GetOutlineColor(),
			data->GetOutlineThickness()
		);
	case ShapeType::Rectangle:
		return std::make_shared<CRectangleView>(
			data->GetPosition(),
			data->GetSize(),
			data->GetFillColor(),
			data->GetOutlineColor(),
			data->GetOutlineThickness()
		);
	case ShapeType::Ellipse:
		return std::make_shared<CEllipseView>(
			data->GetPosition(),
			data->GetSize(),
			data->GetFillColor(),
			data->GetOutlineColor(),
			data->GetOutlineThickness()
		);;
	case ShapeType::Picture:
		return GetPictureView(data);
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	};
}

std::shared_ptr<CPictureView> CShapeViewFactory::GetPictureView(CShapeModelPtr & data)
{
	auto pictureModel = dynamic_cast<CPictureModel*>(data.get());
	return std::make_shared<CPictureView>(
		pictureModel->GetTexture(),
		pictureModel->GetPosition(),
		pictureModel->GetSize()
	);
}
