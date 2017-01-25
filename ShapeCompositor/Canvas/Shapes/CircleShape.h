#pragma once

#include "CShape.h"
#include "Circle.h"

class CCircleShape
	: public CShape
	, public CCircle
{
public:
	CCircleShape();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IShape

	//--------------------------------------------
	// IRenderShapeVisitor

	void Accept(IRenderShapeVisitor & visitor) override;

	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
};