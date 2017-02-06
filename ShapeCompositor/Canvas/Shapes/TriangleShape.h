#pragma once

#include "CShape.h"

class CTriangleShape
	: public CShapeData
	, public IHaveVertex
{
public:
	CTriangleShape(
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
	// IHaveVertex
	std::vector<Vec2f> GetVertices() const override;
	//--------------------------------------------
	// IIsPointIntersection

	bool IsPointIntersection(const Vec2f point) const override;

	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::vector<Vec2f> m_verteces;
};