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
	SShapeData(
		const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);

	Vec2f position;
	SSize size;
	Color fillColor;
	Color outlineColor;
};

// Mixin for avoid dublicate
class CShapeData
{
public:
	CShapeData(
		const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	std::vector<Vec2f> GetFrameVertices() const;

//////////////////////////////////////////////////////////////////////
// Data
protected:
	Vec2f m_position;
	SSize m_size;
	Color m_fillColor;
	Color m_outlineColor;
};

// TODO std::shared_ptr<CShapeModel> replace to CShapeDataPtr
class CShapeModel 
	: public IShape
	, public CShapeData
	, public IObserver<SShapeData>
	, public CObservable<const CShapeModel *>// For connect with ShapeRenderer
	, public IHaveVertex
{
public:
	CShapeModel(
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
	void Update(SShapeData const& data) override;
	//--------------------------------------------
	// IRenderShapeVisitor
	const CShapeModel * GetChangedData() const override;
	//--------------------------------------------
	// IHaveVertex
	std::vector<Vec2f> GetVertices() const override;
	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
public:
	// TODO : see need it(might need for render
	//bool m_isUpdate = false;
};


using CShapeDataPtr = std::shared_ptr<CShapeModel>;

struct SRenderShapeInfo
{
	CShapeDataPtr ptr;
};