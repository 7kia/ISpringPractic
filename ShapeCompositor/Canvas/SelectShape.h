#pragma once

#include <memory>

#include "Shapes\AllShapes.h"
#include "ShapeRenderer.h"
#include "Shapes\ShapeFactory.h"

static const SSize SELECTED_ELLIPSE_SIZE = SSize(10.f, 10.f);

class CSelectShape
	: public IDrawable
{
public:
	CSelectShape(CD2DObjectRenderer & shapeRenderer, const CShapeFactory & shapeFactory);

	enum class UpdateType
	{
		None = -1,
		Move,
		Resize,
	};
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void					SetShape(CShapePtr shape);
	CShapePtr				GetShape() const;
	void					ResetSelectShapePtr();

	void					SetStateUpdate(bool state);
	bool					IsUpdate() const;
	bool					HaveSelectedShape() const;

	void					SetUpdateType(UpdateType type);
	UpdateType				GetUpdateType() const;

	//
	bool					IsResize(const Vec2f point);
	bool					IsMove(const Vec2f point);

	//--------------------------------------------
	// IDrawable
	void					Accept(IShapeVisitor & renderer) const override;// TODO : must be = 0
	//--------------------------------------------
	// IIsPointIntersection
	bool					DefineUpdateType(const Vec2f point);
	//--------------------------------------------

private:
	void					SetViewPosition();
	void					SetMoveView();
	void					SetResizeView();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	SShapeData						m_frameData;
	CShapePtr						m_selectShape;

	std::vector<CShapePtr>				m_moveShape;
	std::vector<CShapePtr>				m_resizeShapes;

	// For drag and drop
	Vec2f								m_startMove;
	Vec2f								m_start;
	Vec2f								m_current;
	Vec2f								m_end;
	bool								m_isUpdate = false;
	UpdateType							m_updateType = UpdateType::None;
};