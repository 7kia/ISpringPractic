#pragma once

#include "CShapeModel.h"

class CRectangleShapeData 
	: public CShapeModel
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

	void Accept(IRenderShapeVisitor & visitor) const override;

	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
};