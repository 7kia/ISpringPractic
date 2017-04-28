#pragma once

#include <memory>
#include <array>

#include "Shapes\AllShapes.h"
#include "ObjectRenderer.h"
#include "Shapes\ShapeFactory.h"
#include <boost\optional.hpp>

static const SSize SELECTED_ELLIPSE_SIZE = SSize(10.f, 10.f);
static const SSize MIN_SHAPE_SIZE = SSize(50.f, 50.f);

class CSelectedShape
	: public IFrame
{
public:
	CSelectedShape();

	enum class ShapeIndex
	{
		MarkerLeftBottom = 0
		, MarkerRightBottom
		, MarkerRightTop
		, MarkerLeftTop
		, Amount
	};

	using DragPointsArray = std::array<CShapePtr, size_t(ShapeIndex::Amount)>;
	enum class UpdateType
	{
		None = -1,
		MarkerLeftBottom ,
		MarkerRightBottom ,
		MarkerRightTop ,
		MarkerLeftTop ,
		Move,
	};
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void					SetShape(const CShapePtr & shape);
	CShapePtr				GetShape() const;
	void					ResetSelectShapePtr();
	void					ResetUpdateParameters();

	void					SetUpdateState(const bool state);
	bool					IsUpdate() const;
	bool					HaveSelectedShape() const;

	void					SetUpdateType(UpdateType type);
	UpdateType				GetUpdateType() const;

	bool					IsResize(const Vec2f point);
	bool					InMarker(const Vec2f point, const ShapeIndex markerIndex);

	bool					DoneUpdate() const;

	bool					IsMove(const Vec2f point);
	void					HandleMoveMouse(const Vec2f point);
	//--------------------------------------------

	// For draw
	DragPointsArray			GetDragPoints() const;
	CShapePtr				GetFrameShape() const;
	void					SetBoundingRect(const D2D1_RECT_F & rect);
	//--------------------------------------------
	// IFrame

	// Position
	void SetPosition(const Vec2f position) override;
	Vec2f GetPosition() const override;
	void Move(const Vec2f shift) override;
	// Size
	void SetSize(const SSize size) override;
	SSize GetSize() const override;

	// Get shape data
	CFrame GetFrame() const;// TODO : see need it
	void SetFrame(CFrame const & data);
	//--------------------------------------------



private:
	// For drag and drop
	Vec2f	GetFinalShift() const;
	SSize	GetDirectionResize() const;
	bool	CheckBoundingRect(const D2D1_RECT_F & rect) const;

	//

	void					SetDragPointPositions();

	bool					CheckSize(const SSize size) const;
	CFrame					GetNewFrame(const Vec2f shift, const CFrame & oldFrame) const;
	static SSize			GetCorrectSize(const SSize size);
	Vec2f					GetCorrectPosition(
												const SSize newSize
												, const Vec2f shift
												, const Vec2f startPosition
												) const;


	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CShapePtr						m_selectedShape;

	DragPointsArray					m_dragPoints;
	CShapePtr						m_frame;
	D2D1_RECT_F						m_boundingRect;
	// For drag and drop
	boost::optional<Vec2f>			m_startMove;
	Vec2f							m_start;
	Vec2f							m_current;
	bool							m_isUpdate = false;
	UpdateType						m_updateType = UpdateType::None;
};