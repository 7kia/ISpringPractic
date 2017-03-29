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
	CSelectedShape(const CShapeFactory & shapeFactory);

	enum class ShapeIndex
	{
		MarkerLeftBottom = 0
		, MarkerRightBottom
		, MarkerRightTop
		, MarkerLeftTop
		, Frame
		, Amount
	};

	using ArrayShapes = std::array<CShapePtr, size_t(ShapeIndex::Amount)>;
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

	bool					DoneUpdate() const;

	bool					IsMove(const Vec2f point);
	void					HandleMoveMouse(const Vec2f point);
	//--------------------------------------------

	// For draw
	ArrayShapes				GetShapes() const;


	//--------------------------------------------
	// IFrame

	// Position
	void SetPosition(Vec2f position) override;
	Vec2f GetPosition() const override;
	void Move(const Vec2f shift) override;
	// Size
	void SetSize(SSize size) override;
	SSize GetSize() const override;

	SRectF GetOwnRect() const;

	// Get shape data
	CFrame GetFrameData() const;// TODO : see need it
	void SetFrameData(CFrame const & data);
	//--------------------------------------------


	// For drag and drop
	Vec2f	GetFinalShift() const;
	void	MoveFrame(const Vec2f shift);
	CFrame GetFinalFrameData() const;
	CFrame	GetOldFrameData();
	CFrame	GetCurrentFrameData();
	SSize GetDirectionResize() const;
	void ReturnToOldState();

private:
	void					SetViewPosition();
	void					SetMoveView();
	void					SetResizeView();

	bool					CheckSize(const SSize size) const;
	CFrame				GetNewFrameData(const Vec2f shift) const;
	SSize					GetCorrectSize(const SSize size) const;
	Vec2f					GetCorrectPosition(
												const SSize newSize
												, const Vec2f shift
												, const Vec2f startPosition
												) const;

	Vec2f					GetCorrectPositionShift(
								const Vec2f shift
								, bool conditionForX
								, bool conditionForY
							) const;

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CFrame						m_frameData;
	CFrame						m_oldData;
	CShapePtr						m_selectedShape;

	ArrayShapes						m_resizeShapes;

	// For drag and drop
	boost::optional<Vec2f>				m_startMove;
	Vec2f								m_start;
	Vec2f								m_current;
	bool								m_isUpdate = false;
	UpdateType							m_updateType = UpdateType::None;
};