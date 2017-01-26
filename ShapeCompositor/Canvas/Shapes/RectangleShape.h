#pragma once

#include "CShape.h"
#include "Rectangle.h"

class CRectangleShape 
	: public CShape
	, public CRectangle
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
	std::vector<Vec2f> GetVertices() const override;

	//////////////////////////////////////////////////////////////////////
	// Data
private:
};