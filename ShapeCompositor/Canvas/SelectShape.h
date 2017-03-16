#pragma once

#include <memory>
#include <array>

#include "Shapes\AllShapes.h"
#include "ObjectRenderer.h"
#include "Shapes\ShapeFactory.h"

static const SSize SELECTED_ELLIPSE_SIZE = SSize(10.f, 10.f);

class CSelectShape
	: public IDrawable
	, public IFrame
{
public:
	CSelectShape(const CShapeFactory & shapeFactory);

	enum class Marker
	{
		MarkerLeftBottom = 0,
		MarkerRightBottom,
		MarkerRightTop,
		MarkerLeftTop,
	};
	enum class UpdateType
	{
		None = -1,
		Move ,
		MarkerLeftBottom ,
		MarkerRightBottom ,
		MarkerRightTop ,
		MarkerLeftTop ,
	};
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void					SetShape(CShapePtr shape);
	CShapePtr				GetShape() const;
	void					ResetSelectShapePtr();
	void					ResetUpdateParameters();

	void					SetUpdateState(bool state);
	bool					IsUpdate() const;
	bool					HaveSelectedShape() const;

	void					SetUpdateType(UpdateType type);
	UpdateType				GetUpdateType() const;

	//
	bool					IsResize(const Vec2f point);
	bool					InLeftTopMarker(const Vec2f point);
	bool					InLeftBottomMarker(const Vec2f point);
	bool					InRightTopMarker(const Vec2f point);
	bool					InRightBottomMarker(const Vec2f point);


	bool					IsMove(const Vec2f point);
	void					HandleMoveMouse(const Vec2f point);
	//--------------------------------------------
	// IDrawable
	void					Accept(IObjectVisitor & renderer) const override;// TODO : must be = 0
	//--------------------------------------------
	// IFrame

	// Position
	void SetPosition(Vec2f position) override;
	Vec2f GetPosition() const override;
	void Move(const Vec2f shift) override;
	// Size
	void SetSize(SSize size) override;
	SSize GetSize() const override;
	void UpdateScale(const Vec2f shift)override;
	// Own rect
	SRectF GetOwnRect() const override;

	// Get shape data
	SFrameData GetFrameData() const override;// TODO : see need it
	void SetFrameData(SFrameData const & data) override;
	//--------------------------------------------


	// For drag and drop
	Vec2f	GetShift() const;
	void	MoveFrame(const Vec2f shift);
	SFrameData GetNewFrameData() const;
	SFrameData	GetOldFrameData();
	SFrameData	GetCurrentFrameData();
	SSize GetChangeResize() const;
	void ReturnToOldState();

private:
	void					SetViewPosition();
	void					SetMoveView();
	void					SetResizeView();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	SFrameData						m_frameData;
	SFrameData						m_oldData;
	CShapePtr						m_selectShape;

	std::vector<CShapePtr>				m_moveShape;
	std::array<CShapePtr, 4>			m_resizeShapes;

	// For drag and drop
	Vec2f								m_startMove;
	Vec2f								m_start;
	Vec2f								m_current;
	bool								m_isUpdate = false;
	UpdateType							m_updateType = UpdateType::None;
};