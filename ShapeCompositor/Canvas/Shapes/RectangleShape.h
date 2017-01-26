#pragma once

#include "CShape.h"
#include "Rectangle.h"

class CRectangleShape 
	: public CShape
	, public IHaveVertex
{
public:
	CRectangleShape(
		const Vec2f position
		, const SSize size
		, const Color fillColor
		, const Color outlineColor
	);

	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShape

	//--------------------------------------------
	// IRenderShapeVisitor

	void Accept(IRenderShapeVisitor & visitor) override;

	//--------------------------------------------
	// IIsPointIntersection

	bool IsPointIntersection(const Vec2f point) const override;

	//--------------------------------------------
	std::vector<Vec2f> GetVertices() const override;

	//////////////////////////////////////////////////////////////////////
	// Data
private:
};