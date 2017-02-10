#pragma once

#include "CShapeModel.h"

class CTriangleShapeData
	: public CShapeModel
{
public:
	CTriangleShapeData(
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

	void Accept(IRenderShapeVisitor & visitor) const override;

	//--------------------------------------------
	// IHaveVertex
	std::vector<Vec2f> GetVertices() const override;
	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::vector<Vec2f> m_verteces;
};