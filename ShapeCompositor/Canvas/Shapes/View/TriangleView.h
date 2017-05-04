#pragma once

#include "ShapeView.h"

class CTriangleView
	: public CShapeView
{
public:
	CTriangleView() = default;
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