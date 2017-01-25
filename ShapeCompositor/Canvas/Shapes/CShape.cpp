#include "stdafx.h"
#include "CShape.h"

CShape::CShape()
	: IShape()
{
}

void CShape::SetPosition(Vec2f position)
{
	m_position = position;
}

Vec2f CShape::GetPosition() const
{
	return m_position;
}

void CShape::SetFillColor(Color color)
{
	m_fillColor = color;
}

Color CShape::GetFillColor() const
{
	return m_fillColor;
}

void CShape::SetOutlineColor(Color color)
{
	m_outlineColor = color;
}

Color CShape::GetOutlineColor() const
{
	return m_outlineColor;
}
