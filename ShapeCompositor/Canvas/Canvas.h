#pragma once

#include <memory>

#include <vector>

#include "Shapes\ShapeFactory.h"
#include "ObjectRenderer.h"
#include "CanvasCommands\AllCanvasCommand.h"
#include "MouseEventHandler.h"


static const size_t MAX_COMMANDS = 5;

static const LONG VIEW_WIDTH = 640;
static const LONG VIEW_HEIGHT = 480;

class CShapeCompositorView;
class CShapeCompositorDoc;
class CCanvasController;


class CCanvas
	: public IDrawable
	, public CFrame
{
public:
	CCanvas();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	// For drag and drop
	bool					IsSelectShape(size_t index, const CShapePtr selectedShape) const;
	//

	//--------------------------------------------
	// 	IDrawable
	void					Accept(IObjectVisitor & renderer) const override;
	//--------------------------------------------
	void					DeleteShape(size_t index);
	void					DeleteShape(CShapePtr pShape);// TODO : see need it variant
	void					DeleteLastShape();
	void					Clear();

	CShapePtr				GetShape(size_t index);
	CShapePtr				GetShape(const Vec2f mousePosition);
	size_t					GetShapeIndex(const CShapePtr pShape) const;
	std::vector<CShapePtr>	GetShapes() const;

	void					PushBackShape(CShapePtr & shape);
	void					InsertShape(size_t insertIndex, CShapePtr & shape);

	size_t					GetAmountShapes() const;

private:
	void					CheckIndex(size_t index) const;
	size_t					GetIndexShape(CShapePtr pShape) const;
	//////////////////////////////////////////////////////////////////////
	// Data
public:

	// TODO : see might require do private
	std::vector<CShapePtr>	m_shapes;
private:
};
