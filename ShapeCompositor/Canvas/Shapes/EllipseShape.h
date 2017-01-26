#pragma once

#include "CShape.h"
#include "Circle.h"

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

	//////////////////////////////////////////////////////////////////////
	// Data
private:
};