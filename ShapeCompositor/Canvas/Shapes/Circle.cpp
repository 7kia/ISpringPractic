#include "stdafx.h"
#include "Circle.h"

CCircle::CCircle()
{
}

CCircle::CCircle(float radius)
{
	SetRadius(radius);
}

void CCircle::SetRadius(float value)
{
	if (m_radius < 0)
	{
		throw std::runtime_error("Ellipse radius must be more zero");
	}
	else
	{
		m_radius = value;
	}
}

float CCircle::GetRadius() const
{
	return m_radius;
}
