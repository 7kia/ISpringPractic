#pragma once

#include "CShape.h"

class CRectangleShapeData 
	: public CShapeData
	, public IHaveVertex
{
public:
	CRectangleShapeData(
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

	//////////////////////////////////////////////////////////////////////
	// Data
private:
};