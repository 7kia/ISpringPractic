#pragma once

#include "ShapeAttributes.h"

class CShapeModel
	: public IShape
	, public CFrame
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
	//--------------------------------------------
	// IShape

	// Inner Color
	void SetFillColor(const Color &  color) override;
	Color GetFillColor() const override;
	// Outer Color
	void SetOutlineColor(const Color &  color) override;
	Color GetOutlineColor() const override;
	// Thikness outline
	void SetOutlineThickness(const float thickness) override;
	float GetOutlineThickness() const override;
	//--------------------------------------------
	// IFrame
	void SetFrame(const CFrame & data) override;
	//--------------------------------------------
	//void SetType();
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