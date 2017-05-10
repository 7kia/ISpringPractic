#pragma once

#include <memory>

#include <vector>

#include "Shapes\ShapeViewFactory.h"
#include "Shapes\Picture\PictureView.h"
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


namespace CanvasNamespace
{
	static const SSize CANVAS_SIZE = SSize(640.f, 480.f);
	static const float SCALE_FACTOR = 0.8f;
	static const SSize MAX_PICTURE_SIZE = SSize(CANVAS_SIZE.width * SCALE_FACTOR, CANVAS_SIZE.height * SCALE_FACTOR);
}

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

	virtual void DeleteShape(size_t index) = 0;
	virtual void DeleteShape(const CShapeModelPtr &  pShape) = 0;
	virtual void Clear() = 0;

	virtual void PushBackShape(CShapeModelPtr & shape) = 0;
	virtual void InsertShape(size_t insertIndex, CShapeModelPtr & shape) = 0;
	virtual void SetShapes(std::vector<CShapeModelPtr> & shapes) = 0;
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
	//--------------------------------------------
	// IShapeCollection
	void					DeleteShape(size_t index) override;
	void					DeleteShape(const CShapeModelPtr & pShape) override;
	void					Clear() override;

	void					PushBackShape(CShapeModelPtr & shape) override;
	void					InsertShape(size_t insertIndex, CShapeModelPtr & shape) override;
	void					SetShapes(std::vector<CShapeModelPtr> & shapes) override;

	size_t					GetShapeCount() const override;
	//--------------------------------------------
	// Signals
	signal::Connection DoOnCreateView(std::function<void(const CShapeViewPtr &, size_t)> const & action);
	signal::Connection DoOnDeleteView(std::function<void(size_t)> const & action);
	//--------------------------------------------
	// IShapeProvider
	CShapeModelPtr					GetShape(const size_t index) override;
	CShapeModelPtr					GetShape(const ID2D1Bitmap * pTexture) override;
	size_t							GetShapeIndex(const CShapeModelPtr & pShape) const override;

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
	void CreateShapePresenter(CShapeModelPtr & pModel, CShapeViewPtr & pView);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::vector<CShapeModelPtr>	m_shapes;
	SSize m_size;

	CShapeViewFactory m_shapeViewFactory;
	// Signals
	signal::Signal<void(CShapeViewPtr &, size_t)> m_onCreateView;
	signal::Signal<void(size_t)> m_onDeleteView;

};

