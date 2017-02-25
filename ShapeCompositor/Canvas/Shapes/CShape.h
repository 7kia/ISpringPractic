#pragma once


#include <memory>
#include "IShape.h"

#include "Observer.h"

// Mixin for avoid dublicate
class CShape 
	: public IShape
	, public IIsPointIntersection
{
public:
	CShape(
		const TypeShape type
		, const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShape

	// Inner Color
	void SetFillColor(Color color) override;
	Color GetFillColor() const override;
	// Outer Color
	void SetOutlineColor(Color color) override;
	Color GetOutlineColor() const override;
	// Type
	TypeShape GetShape() const override;

	SShapeData GetShapeData() const override;
	void SetShapeData(SShapeData const & data) override;
	//--------------------------------------------
	// IFrame

	// Position
	void SetPosition(Vec2f position) override;
	Vec2f GetPosition() const override;
	void Move(const Vec2f shift) override;
	// Size
	void SetSize(SSize size) override;
	SSize GetSize() const override;

	void UpdateScale(const Vec2f shift) override;
	// Own rect
	RECT GetOwnRect() const override;

	// Get shape data
	SFrameData GetFrameData() const override;
	void SetFrameData(SFrameData const & data) override;
	//--------------------------------------------
	


	std::vector<Vec2f> GetFrameVertices() const;

//////////////////////////////////////////////////////////////////////
// Data
protected:
	Vec2f m_position;
	SSize m_size;
	Color m_fillColor;
	Color m_outlineColor;
	TypeShape m_type;
};

using CShapePtr = std::shared_ptr<CShape>;