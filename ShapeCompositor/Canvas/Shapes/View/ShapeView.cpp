#include "stdafx.h"
#include "ShapeView.h"
#include "../Presenter/ShapePresenter.h"
#include "../Picture/PictureView.h"

bool HavePictureWithTexture(ID2D1Bitmap * pTexture, const std::vector<CShapeModelPtr> & shapes)
{
	for (const auto & shape : shapes)
	{
		if (shape->GetType() == ShapeType::Picture)
		{
			auto pPicture = dynamic_cast<CPictureModel*>(shape.get());
			if (pPicture->GetTexture() == pTexture)
			{
				return true;
			}
		}
	}
	return false;
}


CShapeView::CShapeView(
	const Vec2f position
	, const SSize size
	, const Color & fillColor
	, const Color & outlineColor
	, float outlineThikness
)
	: CFrame(position, size)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
	, m_outlineThikness(outlineThikness)
{
}

void CShapeView::SetFillColor(const Color & color)
{
	m_fillColor = color;
}

Color CShapeView::GetFillColor() const
{
	return m_fillColor;
}

void CShapeView::SetOutlineColor(const Color &  color)
{
	m_outlineColor = color;
}

Color CShapeView::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShapeView::SetOutlineThickness(const float thickness)
{
	m_outlineThikness = thickness;
}

float CShapeView::GetOutlineThickness() const
{
	return m_outlineThikness;
}


void CShapeView::SetFrame(const CFrame & data)
{
	CFrame::SetFrame(data);
	m_onChangeRect(data);
}

bool CShapeView::IsPointIntersection(const Vec2f point) const
{
	return false;
}

void CShapeView::SetPresenter(std::shared_ptr<CShapePresenter> & pPresenter)
{
	m_pPresenter = pPresenter;
}

signal::Connection CShapeView::DoOnRectChanged(std::function<void(const CFrame&)> const & action)
{
	return m_onChangeRect.connect(action);
}

