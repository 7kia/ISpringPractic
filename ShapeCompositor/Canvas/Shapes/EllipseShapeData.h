#pragma once

#include "CShapeModel.h"
#include "Observer.h"

class CEllipseDataShape
	: public CShapeModel
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