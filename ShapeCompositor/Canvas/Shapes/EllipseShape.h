#pragma once

#include "CShape.h"

class CEllipseShape
	: public CShape
{
public:
	CEllipseShape(
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

	//////////////////////////////////////////////////////////////////////
	// Data
private:
};