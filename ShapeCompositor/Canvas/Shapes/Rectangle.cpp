#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle()
	: IRectangle()
{
}

CRectangle::CRectangle(SSize size)
{
	SetWidth(size.width);
	SetHeight(size.height);

}

CRectangle::CRectangle(float width, float height)
{
	SetWidth(width);
	SetHeight(height);
}

void CRectangle::SetWidth(float width)
{
	if (width < 0)
	{
		m_width = 0;
	}
	else
	{
		m_width = width;
	}
}

float CRectangle::GetWidth() const
{
	return m_width;
}

void CRectangle::SetHeight(float height)
{
	if (height < 0)
	{
		m_height = 0;
	}
	else
	{
		m_height = height;
	}
}

float CRectangle::GetHeight() const
{
	return m_height;
}