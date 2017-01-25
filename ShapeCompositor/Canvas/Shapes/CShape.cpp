#include "stdafx.h"
#include "CShape.h"

CShape::CShape()
	: IShape()
{
}

void CShape::SetPosition(D2D1_POINT_2F position)
{
	m_position = position;
}

D2D1_POINT_2F CShape::GetPosition() const
{
	return m_position;
}

void CShape::SetInnerColor(D2D1_COLOR_F color)
{
	m_innerColor = color;
}

D2D1_COLOR_F CShape::GetInnerColor() const
{
	return m_innerColor;
}

void CShape::SetOuterColor(D2D1_COLOR_F color)
{
	m_outerColor = color;
}

D2D1_COLOR_F CShape::GetOuterColor() const
{
	return m_outerColor;
}
