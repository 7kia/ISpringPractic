#pragma once

#include "CShape.h"

class CRectangle
	: public CShape
	, public IHaveVertex
{
public:
	CRectangle(
		const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IDrawable

	void Accept(IShapeVisitor & renderer) const override;

	//--------------------------------------------
	// IHaveVertex
	std::vector<Vec2f> GetVertices() const;
	//--------------------------------------------
	// IIsPointIntersection
	bool IsPointIntersection(const Vec2f point) const override;
	//--------------------------------------------

private:

	//////////////////////////////////////////////////////////////////////
	// Data
private:

};