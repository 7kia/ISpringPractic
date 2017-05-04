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

bool CShapeView::IsPointIntersection(const Vec2f point) const
{
	return false;
}

