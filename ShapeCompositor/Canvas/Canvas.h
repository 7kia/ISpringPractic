#pragma once

#include <memory>

#include <vector>

#include "Shapes\ShapeFactory.h"
#include "ObjectRenderer.h"
#include "CanvasCommands\AllCanvasCommand.h"
#include "MouseEventHandler.h"
#include "History.h"

static const size_t MAX_COMMANDS = 5;

static const LONG VIEW_WIDTH = 640;
static const LONG VIEW_HEIGHT = 480;

class CShapeCompositorView;
class CShapeCompositorDoc;
class CCanvasController;


class CCanvas
	: public CFrame
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
	void AddAndExecuteCommand(const CanvasCommandPtr & command);

	void UndoCommand();
	void RedoCommand();

	void ClearHistory();
	//--------------------------------------------
	void					DeleteShape(size_t index);
	void					DeleteShape(CShapePtr pShape);// TODO : see need it variant
	void					DeleteLastShape();
	void					Clear();

	CShapePtr				GetShape(size_t index);
	CShapePtr				GetShape(const Vec2f mousePosition);
	size_t					GetShapeIndex(const CShapePtr pShape) const;
	std::vector<CShapePtr>	GetShapes() const;
	void					SetShapes(const std::vector<CShapePtr> & shapes);

	void					PushBackShape(CShapePtr & shape);
	void					InsertShape(size_t insertIndex, CShapePtr & shape);

	size_t					GetAmountShapes() const;

private:
	void					CheckShapeIndex(size_t index, bool isInsert = false) const;
	size_t					GetIShapeIndex(CShapePtr pShape) const;
	//////////////////////////////////////////////////////////////////////
	// Data
public:
	CHistory m_history;
	// TODO : see might require do private
	std::vector<CShapePtr>	m_shapes;
private:
};
