#pragma once

#include "ShapePresenter.h"

class CEllipsePresenter 
	: public CShapePresenter
{
public:
	CEllipsePresenter(const Vec2f position, const SSize size);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
private:
	//--------------------------------------------
	// IIsPointIntersection

	bool IsPointIntersection(const Vec2f point) const override;

	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:

};