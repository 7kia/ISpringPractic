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

void CShape::SetInnerColor(Color color)
{
	m_innerColor = color;
}

Color CShape::GetInnerColor() const
{
	return m_innerColor;
}

void CShape::SetOuterColor(Color color)
{
	m_outerColor = color;
}

Color CShape::GetOuterColor() const
{
	return m_outerColor;
}
