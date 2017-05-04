#pragma once

#include "ShapeView.h"

class CRectangleView
	: public CShapeView
{
public:
	CRectangleView() = default;
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

	VertexList GetVertices() const;

private:

	//////////////////////////////////////////////////////////////////////
	// Data
private:

};