#pragma once

#include <memory>

#include <vector>

#include "Shapes\ShapeViewFactory.h"
#include "Picture\PictureView.h"
#include "ShapeRenderer.h"
#include "CanvasCommands\AllCanvasCommand.h"
#include "MouseEventHandler.h"
#include "History.h"

static const size_t MAX_COMMANDS = 5;

static const LONG VIEW_WIDTH = 640;
static const LONG VIEW_HEIGHT = 480;

class CShapeCompositorView;
class CShapeCompositorDoc;
class CCanvasController;

CShapeViewPtr GetShape(const Vec2f mousePosition, const std::vector<CShapeViewPtr> & vector);

class IShapeProvider
{
public:
	virtual ~IShapeProvider() = default;

	virtual CShapeModelPtr GetShape(const size_t index) = 0;
	virtual CShapeModelPtr GetShape(const ID2D1Bitmap * pTexture) = 0;
	virtual std::vector<CShapeModelPtr>&	GetShapes() = 0;
	virtual size_t GetShapeCount() const = 0;
	virtual size_t GetShapeIndex(const CShapeModelPtr & pShape) const = 0;
};

class IShapeCollection : public IShapeProvider
{
public:
	virtual ~IShapeCollection() = default;

	virtual void DeleteShape(const size_t index) = 0;
	virtual void DeleteShape(const CShapeModelPtr &  pShape) = 0;
	virtual void Clear() = 0;

	virtual void PushBackShape(const CShapeModelPtr & shape) = 0;
	virtual void InsertShape(const size_t insertIndex, const CShapeModelPtr & shape) = 0;
	virtual void SetShapes(const std::vector<CShapeModelPtr> & shapes) = 0;


	virtual bool IsSelectShape(const size_t index, const CShapeModelPtr & selectedShape) const = 0;

};

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual IShapeCollection& GetShapeCollection() = 0;
	virtual IShapeProvider& GetShapeProvider() = 0;
	virtual void	SetSize(const SSize size) = 0;
	virtual SSize	GetSize() const = 0;
	virtual D2D1_RECT_F GetRect() const = 0;
};


class CCanvasModel
	: private IShapeCollection
	, public ICanvas
{
public:
	CCanvasModel(const SSize size);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	//signal::Connection DoOnDeleteShapeCommand(std::function<void(CSelectedShape &)> const & action);

	//--------------------------------------------
	// IShapeCollection
	void					DeleteShape(const size_t index) override;
	void					DeleteShape(const CShapeModelPtr & pShape) override;
	void					Clear() override;

	void					PushBackShape(const CShapeModelPtr & shape) override;
	void					InsertShape(const size_t insertIndex, const CShapeModelPtr & shape) override;
	void					SetShapes(const std::vector<CShapeModelPtr> & shapes) override;

	size_t					GetShapeCount() const override;

	// For drag and drop
	bool					IsSelectShape(const size_t index, const CShapeModelPtr & selectedShape) const override;
	//--------------------------------------------

	//--------------------------------------------
	// IShapeProvider
	CShapeModelPtr				GetShape(const size_t index) override;
	CShapeModelPtr				GetShape(const ID2D1Bitmap * pTexture) override;
	size_t						GetShapeIndex(const CShapeModelPtr & pShape) const override;

	std::vector<CShapeModelPtr>&	GetShapes() override;
	//--------------------------------------------
	// ICanvas
	IShapeCollection&		GetShapeCollection() override;
	IShapeProvider&			GetShapeProvider() override;
	// Size
	void					SetSize(const SSize size) override;
	SSize					GetSize() const override;

	D2D1_RECT_F				GetRect() const;
	//--------------------------------------------

private:
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::vector<CShapeModelPtr>	m_shapes;

	SSize m_size;
};

