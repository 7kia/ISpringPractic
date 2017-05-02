#pragma once


#include <memory>
#include "IShape.h"

// Mixin for avoid dublicate
class CShape 
	: public IShape
	, public CFrame
{
public:
	CShape(
		const ShapeType type,
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
	// Type
	ShapeType GetType() const override;

	SShapeData GetShapeData() const override;
	void SetShapeData(const SShapeData & data) override;
	//--------------------------------------------
	virtual bool IsPointIntersection(const Vec2f point) const;
	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	Color m_fillColor;
	Color m_outlineColor;
	ShapeType m_type;
	float m_outlineThikness = 1.f;
};

using CShapePtr = std::shared_ptr<CShape>;