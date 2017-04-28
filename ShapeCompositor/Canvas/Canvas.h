#pragma once

#include <memory>

#include <vector>

#include "Shapes\ShapeFactory.h"
#include "Picture\Picture.h"
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

CShapePtr GetShape(const Vec2f mousePosition, const std::vector<CShapePtr> & vector);

class IShapeProvider
{
public:
	virtual ~IShapeProvider() = default;

	virtual CShapePtr GetShape(const size_t index) = 0;
	virtual std::vector<CShapePtr>&	GetShapes() = 0;
	virtual size_t GetShapeCount() const = 0;
	virtual size_t GetShapeIndex(const CShapePtr & pShape) const = 0;
};

class IShapeCollection : public IShapeProvider
{
public:
	virtual ~IShapeCollection() = default;

	virtual void DeleteShape(const size_t index) = 0;
	virtual void DeleteShape(const CShapePtr &  pShape) = 0;

	virtual void PushBackShape(const CShapePtr & shape) = 0;
	virtual void InsertShape(const size_t insertIndex, const CShapePtr & shape) = 0;


	virtual bool IsSelectShape(const size_t index, const CShapePtr & selectedShape) const = 0;

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


bool HavePictureWithTexture(ID2D1Bitmap * pTexture, const std::vector<CShapePtr> & shapes);

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
	void					DeleteShape(const CShapePtr & pShape) override;

	void					PushBackShape(const CShapePtr & shape) override;
	void					InsertShape(const size_t insertIndex, const CShapePtr & shape) override;

	size_t					GetShapeCount() const override;

	// For drag and drop
	bool					IsSelectShape(const size_t index, const CShapePtr & selectedShape) const override;
	//--------------------------------------------
	void					Clear();

	//--------------------------------------------
	// IShapeProvider
	CShapePtr				GetShape(const size_t index) override;
	size_t					GetShapeIndex(const CShapePtr & pShape) const override;

	std::vector<CShapePtr>&	GetShapes() override;
	//--------------------------------------------
	void					SetShapes(const std::vector<CShapePtr> & shapes);
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
	std::vector<CShapePtr>	m_shapes;
	SSize					m_size;
};

