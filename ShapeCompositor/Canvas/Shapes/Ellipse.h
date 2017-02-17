#pragma once

#include "CShape.h"

class CEllipse 
	: public CShape
{
public:
	CEllipse(
		const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IDrawable

	void Draw(IRenderShape & renderer) const override;

	//--------------------------------------------
	// IIsPointIntersection
	bool IsPointIntersection(const Vec2f point) const override;
	//--------------------------------------------

private:

	//////////////////////////////////////////////////////////////////////
	// Data
private:

};