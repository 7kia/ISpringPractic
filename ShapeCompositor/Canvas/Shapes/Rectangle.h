#pragma once

#include "CShape.h"

class CRectangle
	: public CShape
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

	void Accept(IShapeVisitor & visitor) const override;
	//--------------------------------------------
	// IIsPointIntersection
	bool IsPointIntersection(const Vec2f point) const override;
	//--------------------------------------------

	ListVertices GetVertices() const;

private:

	//////////////////////////////////////////////////////////////////////
	// Data
private:

};