#include "stdafx.h"
#include "ShapeViewFactory.h"

CShapeViewPtr CShapeViewFactory::CreateShape(const CShapeModel & data)
{
	CShapePresenter presenter(data);
	CShapeViewPtr view;
	switch (data.type)
	{
	case ShapeType::Triangle:
		view = std::make_shared<CTriangleView>(
			data.GetPosition(),
			data.GetSize(),
			data.GetFillColor(),
			data.GetOutlineColor(),
			data.GetOutlineThickness()
			);
		view->SetPresenter(presenter);
		return view;
	case ShapeType::Rectangle:
		view = std::make_shared<CRectangleView>(
			data.GetPosition(),
			data.GetSize(),
			data.GetFillColor(),
			data.GetOutlineColor(),
			data.GetOutlineThickness()
			);
		view->SetPresenter(presenter);
		return view;
	case ShapeType::Ellipse:
		view = std::make_shared<CEllipseView>(
			data.GetPosition(),
			data.GetSize(),
			data.GetFillColor(),
			data.GetOutlineColor(),
			data.GetOutlineThickness()
			);
		view->SetPresenter(presenter);
		return view;
	case ShapeType::Picture:
		auto pictureModel = dynamic_cast<CPictureModel*>(&data);
		view = std::make_shared<CPictureView>(
			pictureModel->GetTexture(),
			pictureModel->GetPosition(),
			pictureModel->GetSize()// Need presenter
			);
		view->SetPresenter(presenter);
		return view;
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	};
}