#pragma once

#include "CShape.h"

class CTriangle
	: public CShape
	, public IHaveVertex
{
public:
	CTriangle(
		const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShape(for draw

	void Accept(IObjectVisitor & renderer) const override;

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