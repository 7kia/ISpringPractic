#pragma once

#include "../ShapeAttributes.h"
#include "../IShape.h"
#include "Signal.h"

class CShapeModel
	: public CFrame
{
public:
	CShapeModel(
		ShapeType type,
		const Vec2f position = Vec2f(),
		const SSize size = DEFAULT_SIZE,
		const Color & fillColor = DEFAULT_FILL_COLOR,
		const Color & outlineColor = DEFAULT_OUTLINE_COLOR,
		const float outlineThikness = 1.f
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	// Inner Color
	void SetFillColor(const Color &  color);
	Color GetFillColor() const;
	// Outer Color
	void SetOutlineColor(const Color &  color);
	Color GetOutlineColor() const;
	// Thickness outline
	void SetOutlineThickness(const float thickness);
	float GetOutlineThickness() const;
	//--------------------------------------------
	// For update view and model for update history(for selected shape)
	void Update(const CFrame & data);
	
	ShapeType GetType() const;
	signal::Connection DoOnRectChanged(std::function<void(const CFrame&)> const& action);
	bool operator==(const CShapeModel & otherModel) const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	ShapeType m_type = ShapeType::Triangle;
	Color m_fillColor;
	Color m_outlineColor;
	float m_outlineThikness = 1.f;

	signal::Signal<void(const CFrame&)> m_onChangeRect;
};

using CShapeModelPtr = std::shared_ptr<CShapeModel>;