#pragma once


#include <memory>
#include "IShape.h"

#include "Observer.h"


struct SPresenterData
{
	Vec2f position;
	SSize size;
};

struct SShapeData
{
	Vec2f position;
	SSize size;
	Color fillColor;
	Color outlineColor;
};

class CShapeData 
	: public IShape
	, public IObserver<SPresenterData>
{
public:
	CShapeData(
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

	// Position
	void SetPosition(Vec2f position) override;
	Vec2f GetPosition() const override;
	// Inner Color
	void SetFillColor(Color color) override;
	Color GetFillColor() const override;
	// Outer Color
	void SetOutlineColor(Color color) override;
	Color GetOutlineColor() const override;
	// Size
	void SetSize(SSize size) override;
	SSize GetSize() const override;
	// Own rect
	RECT GetOwnRect() const override;

	//--------------------------------------------
	// IObserver<SPresenterData>
	void Update(SPresenterData const& data) override;
	//--------------------------------------------

	// TODO :
	// Visual part

	//--------------------------------------------

	//void			Set();
	//void			Get();
	//////////////////////////////////////////////////////////////////////
	// Data
public:

protected:
	Vec2f m_position;

	SSize m_size;
	Color m_fillColor;
	Color m_outlineColor;

	// TODO : see need it(might need for render
	bool m_isUpdate = false;

};


using CShapeDataPtr = std::shared_ptr<CShapeData>;

struct SRenderShapeInfo
{
	CShapeDataPtr ptr;
};