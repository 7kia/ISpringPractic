#pragma once

#include "ShapeView.h"

class CEllipseView 
	: public CShapeView
{
public:
	CEllipseView(
		const Vec2f position = Vec2f(),
		const SSize size = DEFAULT_SIZE,
		const Color & fillColor = DEFAULT_FILL_COLOR,
		const Color & outlineColor = DEFAULT_OUTLINE_COLOR,
		float outlineThikness = 1.f
	);

	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShape

	void Accept(IShapeVisitor & visitor) const override;

	//--------------------------------------------
	// IIsPointIntersection
	bool IsPointIntersection(const Vec2f point) const override;
	//--------------------------------------------

private:

	//////////////////////////////////////////////////////////////////////
	// Data
private:

};