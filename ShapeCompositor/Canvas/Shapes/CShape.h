#pragma once


#include <memory>
#include "IShape.h"

#include "Observer.h"


struct SPresenterData
{
	Vec2f position;
	SSize size;

	SPresenterData();
	SPresenterData(Vec2f position, SSize size);
};

static const SSize DEFAULT_SIZE = SSize(50.f, 50.f);
static const Color DEFAULT_OUTLINE_COLOR = Color(0.f, 0.f, 0.f);
static const Color DEFAULT_FILL_COLOR = Color(0.45f, 0.75f, 0.55f);


struct SShapeData
{
	SShapeData();

	Vec2f position;
	SSize size;
	Color fillColor;
	Color outlineColor;
};

// TODO std::shared_ptr<CShapeData> replace to CShapeDataPtr
class CShapeData 
	: public IShape
	, public IObserver<SPresenterData>
	, public CObservable<const CShapeData *>// For connect with ShapeRenderer
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
	// IRenderShapeVisitor
	const CShapeData * GetChangedData() const override;
	//--------------------------------------------

	// TODO :
	// Visual part

	//--------------------------------------------

	//void			Set();
	//void			Get();
	//////////////////////////////////////////////////////////////////////
	// Data
public:
	// TODO : see need it(might need for render
	bool m_isUpdate = false;

protected:
	Vec2f m_position;

	SSize m_size;
	Color m_fillColor;
	Color m_outlineColor;


};


using CShapeDataPtr = std::shared_ptr<CShapeData>;

struct SRenderShapeInfo
{
	CShapeDataPtr ptr;
};