#pragma once

#include "CShape.h"
#include "Observer.h"

class CEllipseDataShape
	: public CShapeData
{
public:
	CEllipseDataShape(
		const Vec2f position
		, const SSize size
		, const Color fillColor
		, const Color outlineColor
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IRenderShapeVisitor

	void Accept(IRenderShapeVisitor & visitor) const override;

	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
};