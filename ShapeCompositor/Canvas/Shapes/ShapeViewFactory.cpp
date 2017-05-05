#include "stdafx.h"
#include "ShapeViewFactory.h"
#include "Presenter/ShapePresenter.h"

CShapeViewPtr CShapeViewFactory::CreateShape(CShapeModelPtr & data)
{
	auto presenter = std::make_shared<CShapePresenter>(data);
	CShapeViewPtr view;
	switch (data->GetType())
	{
	case ShapeType::Triangle:
		view = std::make_shared<CTriangleView>(
			data->GetPosition(),
			data->GetSize(),
			data->GetFillColor(),
			data->GetOutlineColor(),
			data->GetOutlineThickness()
		);
		presenter->SetShapeView(view.get());
		view->SetPresenter(presenter);
		return view;
	case ShapeType::Rectangle:
		view = std::make_shared<CRectangleView>(
			data->GetPosition(),
			data->GetSize(),
			data->GetFillColor(),
			data->GetOutlineColor(),
			data->GetOutlineThickness()
		);
		presenter->SetShapeView(view.get());
		view->SetPresenter(presenter);
		return view;
	case ShapeType::Ellipse:
		view = std::make_shared<CEllipseView>(
			data->GetPosition(),
			data->GetSize(),
			data->GetFillColor(),
			data->GetOutlineColor(),
			data->GetOutlineThickness()
		);
		presenter->SetShapeView(view.get());
		view->SetPresenter(presenter);
		return view;
	case ShapeType::Picture:
		view = GetPictureView(data);
		presenter->SetShapeView(view.get());
		view->SetPresenter(presenter);
		return view;
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
