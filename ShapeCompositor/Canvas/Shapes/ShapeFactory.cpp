#include "stdafx.h"
#include "../Canvas.h"
#include "ShapeFactory.h"

CShapeFactory::CShapeFactory(CCanvas * pCanvas)
	: IShapeFactory()
	, m_pCanvas(pCanvas)
{
}

void CShapeFactory::CreateShape(TypeShape type, const Vec2f position)
{
	CShapeDataPtr lastData;
	CShapePresenterPtr lastPresenter;
	switch (type)
	{
	case TypeShape::Triangle:
		m_pCanvas->m_shapesData.push_back(std::make_shared<CTriangleShapeData>(
			position
			, DEFAULT_SIZE
			, DEFAULT_FILL_COLOR
			, DEFAULT_OUTLINE_COLOR
			));
		m_pCanvas->m_shapePresenters.push_back(std::make_shared<CTrianglePresenter>(
			position
			, DEFAULT_SIZE
			));

		BindPresenterWithModel();
		break;
	case TypeShape::Rectangle:
		m_pCanvas->m_shapesData.push_back(std::make_shared<CRectangleShapeData>(
			position
			, DEFAULT_SIZE
			, DEFAULT_FILL_COLOR
			, DEFAULT_OUTLINE_COLOR
			));
		m_pCanvas->m_shapePresenters.push_back(std::make_shared<CRectanglePresenter>(
			position
			, DEFAULT_SIZE
			));

		BindPresenterWithModel();
		break;
	case TypeShape::Ellipse:
		m_pCanvas->m_shapesData.push_back(std::make_shared<CEllipseDataShape>(
			position
			, DEFAULT_SIZE
			, DEFAULT_FILL_COLOR
			, DEFAULT_OUTLINE_COLOR
			));
		m_pCanvas->m_shapePresenters.push_back(std::make_shared<CEllipsePresenter>(
			position
			, DEFAULT_SIZE
			));

		BindPresenterWithModel();
		break;
	default:
		throw std::runtime_error("The shape type not exist");
		break;
	}

	//return CShapeDataPtr();
}

void CShapeFactory::BindPresenterWithModel()
{
	CShapeDataPtr lastData =m_pCanvas->m_shapesData.back();
	CShapePresenterPtr lastPresenter =  m_pCanvas->m_shapePresenters.back();

	lastPresenter->RegisterObserver(*lastData.get());
}
