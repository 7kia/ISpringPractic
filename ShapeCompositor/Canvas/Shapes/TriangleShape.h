#pragma once

#include "CShape.h"

class CTriangleShape
	: public CShape
	, public IHaveVertex
{
public:
	CTriangleShape(Vec2f const & position
					, float width
					, float height
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
	// IHaveVertex
	std::vector<Vec2f> GetVertices() const override;
	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::vector<Vec2f> m_verteces;
};