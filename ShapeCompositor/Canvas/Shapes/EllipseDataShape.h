#pragma once

#include "CShape.h"
#include "Observer.h"

class CEllipseDataShape
	: public CShapeData
	, public IObserver<SPresenterData>
	, public CObservable<SShapeData>
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

	void Accept(IRenderShapeVisitor & visitor) override;

	//--------------------------------------------
	// IObserver<SPresenterData>
	void Update(SPresenterData const& data) override;
	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	bool m_isUpdate = false;
};