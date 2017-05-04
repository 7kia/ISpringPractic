#pragma once

#include "ShapeView.h"

class CEllipseView 
	: public CShapeView
{
public:
	CEllipseView() = default;
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