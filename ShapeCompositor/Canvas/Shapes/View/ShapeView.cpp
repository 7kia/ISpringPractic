#include "stdafx.h"
#include "ShapeView.h"

CShapeView::CShapeView(const ShapeType type)
	: m_type(type)
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


ShapeType CShapeView::GetType() const
{
	return m_type;
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

void CShapeView::SetPresenter(CShapePresenter & presenter)
{
	m_presenter = presenter;
}

signal::Connection CShapeView::DoOnRectChanged(std::function<void(const CFrame&)> const & action)
{
	return m_onChangeRect.connect(action);
}

