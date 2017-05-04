#pragma once

#include <memory>

#include <vector>

#include "Shapes\ShapeViewFactory.h"
#include "Picture\PictureView.h"
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

CShapeViewPtr GetShape(const Vec2f mousePosition, const std::vector<CShapeViewPtr> & vector);

class IShapeProvider
{
public:
	virtual ~IShapeProvider() = default;

	virtual CShapeViewPtr GetShape(const size_t index) = 0;
	virtual CShapeViewPtr GetShape(const ID2D1Bitmap * pTexture) = 0;
	virtual std::vector<CShapeViewPtr>&	GetShapes() = 0;
	virtual size_t GetShapeCount() const = 0;
	virtual size_t GetShapeIndex(const CShapeViewPtr & pShape) const = 0;
};

class IShapeCollection : public IShapeProvider
{
public:
	virtual ~IShapeCollection() = default;

	virtual void DeleteShape(const size_t index) = 0;
	virtual void DeleteShape(const CShapeViewPtr &  pShape) = 0;
	virtual void Clear() = 0;

	virtual void PushBackShape(const CShapeViewPtr & shape) = 0;
	virtual void InsertShape(const size_t insertIndex, const CShapeViewPtr & shape) = 0;
	virtual void SetShapes(const std::vector<CShapeViewPtr> & shapes) = 0;


	virtual bool IsSelectShape(const size_t index, const CShapeViewPtr & selectedShape) const = 0;

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


bool HavePictureWithTexture(ID2D1Bitmap * pTexture, const std::vector<CShapeViewPtr> & shapes);

class CCanvas
	: private IShapeCollection
	, public ICanvas
{
public:
	CCanvas(const SSize size);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	//--------------------------------------------
	// IShapeCollection
	void					DeleteShape(const size_t index) override;
	void					DeleteShape(const CShapeViewPtr & pShape) override;
	void					Clear() override;

	void					PushBackShape(const CShapeViewPtr & shape) override;
	void					InsertShape(const size_t insertIndex, const CShapeViewPtr & shape) override;
	void					SetShapes(const std::vector<CShapeViewPtr> & shapes) override;

	size_t					GetShapeCount() const override;

	// For drag and drop
	bool					IsSelectShape(const size_t index, const CShapeViewPtr & selectedShape) const override;
	//--------------------------------------------

	//--------------------------------------------
	// IShapeProvider
	CShapeViewPtr				GetShape(const size_t index) override;
	CShapeViewPtr				GetShape(const ID2D1Bitmap * pTexture) override;
	size_t					GetShapeIndex(const CShapeViewPtr & pShape) const override;

	std::vector<CShapeViewPtr>&	GetShapes() override;
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
	std::vector<CShapeViewPtr>	m_shapes;
	SSize					m_size;
};

