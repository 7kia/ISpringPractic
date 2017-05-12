#include "stdafx.h"
#include "ShapeModel.h"

CShapeModel::CShapeModel(
	ShapeType type,
	const Vec2f position,
	const SSize size,
	const Color & fillColor,
	const Color & outlineColor,
	const float outlineThikness
)
	: m_type(type)
	, CFrame(position, size)
	, m_fillColor(fillColor)
	, m_outlineColor(outlineColor)
	, m_outlineThikness(outlineThikness)
{
}

ShapeType CShapeModel::GetType() const
{
	return m_type;
}


void CShapeModel::SetFillColor(const Color & color)
{
	m_fillColor = color;
}

Color CShapeModel::GetFillColor() const
{
	return m_fillColor;
}

void CShapeModel::SetOutlineColor(const Color &  color)
{
	m_outlineColor = color;
}

Color CShapeModel::GetOutlineColor() const
{
	return m_outlineColor;
}

void CShapeModel::SetOutlineThickness(const float thickness)
{
	m_outlineThikness = thickness;
}

float CShapeModel::GetOutlineThickness() const
{
	return m_outlineThikness;
}

void CShapeModel::Update(const CFrame & data)
{
	CFrame::SetFrame(data);
	m_onChangeRect(data);
}

signal::Connection CShapeModel::DoOnRectChanged(std::function<void(const CFrame&)> const & action)
{
	return m_onChangeRect.connect(action);
}

bool CShapeModel::operator==(const CShapeModel & otherModel) const
{
	return (m_position == otherModel.GetPosition())
		&& (m_size == otherModel.GetSize())
		&& (m_type == otherModel.GetType())
		&& (m_fillColor == otherModel.GetFillColor())
		&& (m_outlineColor == otherModel.GetOutlineColor());

}
