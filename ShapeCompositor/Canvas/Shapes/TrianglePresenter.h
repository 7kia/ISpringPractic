#pragma once

#include "ShapePresenter.h"


class CTrianglePresenter
	: public CShapePresenter
	, public IHaveVertex
{
public:
	CTrianglePresenter(const Vec2f position, const SSize size);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
private:
	//--------------------------------------------
	// IIsPointIntersection

	bool IsPointIntersection(const Vec2f point) const override;

	//--------------------------------------------
	// IHaveVertex
	std::vector<Vec2f> GetVertices() const override;
	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:

};