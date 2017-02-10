#pragma once

#include "Observer.h"
#include "CShape.h"

class CShapePresenter 
	: public CObservable<SPresenterData>// For update view and model
	, public IObserver<SPresenterData>
	, public IIsPointIntersection
{
public:
	CShapePresenter(const Vec2f position, const SSize size);

	~CShapePresenter();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	bool CheckPointIntersection(const Vec2f point);

	//--------------------------------------------
	// CObservable<SPresenterData>
	SPresenterData GetChangedData() const override;
	//--------------------------------------------

	void Update(const SPresenterData & data) override;
	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	Vec2f m_position;
	SSize m_size;
};

using CShapePresenterPtr = std::shared_ptr<CShapePresenter>;
using CShapePresenterWeakPtr = std::weak_ptr<CShapePresenter>;