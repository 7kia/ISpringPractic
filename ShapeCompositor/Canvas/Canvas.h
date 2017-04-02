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


class IGetShape
{
public:
	virtual ~IGetShape() = default;

	virtual CShapePtr GetShape(size_t index) = 0;
	virtual CShapePtr GetShape(const Vec2f mousePosition) = 0;
	virtual size_t GetShapeIndex(const CShapePtr & pShape) const = 0;

};

class IAddAndDeleteShape
	: public IGetShape
{
public:
	virtual ~IAddAndDeleteShape() = default;

	virtual void DeleteShape(size_t index) = 0;
	virtual void DeleteShape(const CShapePtr &  pShape) = 0;
	virtual void DeleteLastShape() = 0;

	virtual void PushBackShape(const CShapePtr & shape) = 0;
	virtual void InsertShape(size_t insertIndex, const CShapePtr & shape) = 0;

	virtual size_t GetAmountShapes() const = 0;
	virtual bool IsSelectShape(size_t index, const CShapePtr & selectedShape) const = 0;

};


class CCanvas
	: public IAddAndDeleteShape
{
public:
	CCanvas(const SSize & size = SSize());
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	//--------------------------------------------
	void AddAndExecuteCommand(const CanvasCommandPtr & command);

	void UndoCommand();
	void RedoCommand();

	void ClearHistory();
	//--------------------------------------------
	// IAddAndDeleteShape
	void					DeleteShape(size_t index) override;
	void					DeleteShape(const CShapePtr & pShape) override;
	void					DeleteLastShape() override;

	void					PushBackShape(const CShapePtr & shape) override;
	void					InsertShape(size_t insertIndex, const CShapePtr & shape) override;

	size_t					GetAmountShapes() const override;

	// For drag and drop
	bool					IsSelectShape(size_t index, const CShapePtr & selectedShape) const override;
	//--------------------------------------------
	void					Clear();

	//--------------------------------------------
	// IGetShape
	CShapePtr				GetShape(size_t index) override;
	CShapePtr				GetShape(const Vec2f mousePosition) override;
	size_t					GetShapeIndex(const CShapePtr & pShape) const override;
	//--------------------------------------------
	std::vector<CShapePtr>	GetShapes() const;
	void					SetShapes(const std::vector<CShapePtr> & shapes);
	//--------------------------------------------

	// Size
	void					SetSize(const SSize & size);
	SSize					GetSize() const;

	// For save to document
	bool					IsSave() const;
	void					SetSaveState(bool value);

private:
	void					CheckShapeIndex(size_t index, size_t max) const;
	//////////////////////////////////////////////////////////////////////
	// Data
public:
private:
	CHistory m_history;
	// TODO : see might require do private
	std::vector<CShapePtr>	m_shapes;

	SSize m_size;

	bool m_isSave = false;
};
