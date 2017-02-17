#pragma once


#include <memory>
#include "IShape.h"

#include "Observer.h"

// TODO  : see need it
struct SPresenterData
{
	Vec2f position;
	SSize size;

	SPresenterData();
	SPresenterData(Vec2f position, SSize size);
};

// Mixin for avoid dublicate
class CShape 
	: public IShape
	, public IIsPointIntersection
{
public:
	CShape(
		const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShape

	// Position
	void SetPosition(Vec2f position) override;
	Vec2f GetPosition() const override;
	// Inner Color
	void SetFillColor(Color color) override;
	Color GetFillColor() const override;
	// Outer Color
	void SetOutlineColor(Color color) override;
	Color GetOutlineColor() const override;
	// Size
	void SetSize(SSize size) override;
	SSize GetSize() const override;
	// Own rect
	RECT GetOwnRect() const override;

	std::vector<Vec2f> GetFrameVertices() const;

	SShapeData GetShapeData() const override;
	void SetShapeData(SShapeData const & data) override;
//////////////////////////////////////////////////////////////////////
// Data
protected:
	Vec2f m_position;
	SSize m_size;
	Color m_fillColor;
	Color m_outlineColor;
};

using CShapePtr = std::shared_ptr<CShape>;