#pragma once

#include "Observer.h"
#include "CShape.h"

class CShapePresenter 
	: public CObservable<SPresenterData>
	, public IIsPointIntersection
{
public:
	CShapePresenter(const Vec2f position, const SSize size);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void CheckPointIntersection(const Vec2f point);
	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	Vec2f m_position;

	SSize m_size;
};