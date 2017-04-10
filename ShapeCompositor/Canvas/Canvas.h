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


class IShapeProvider
{
public:
	virtual ~IShapeProvider() = default;

	virtual CShapePtr GetShape(size_t index) = 0;
	virtual CShapePtr GetShape(const Vec2f mousePosition) = 0;
	virtual std::vector<CShapePtr>&	GetShapes() = 0;
	virtual size_t GetAmountShapes() const = 0;
	virtual size_t GetShapeIndex(const CShapePtr & pShape) const = 0;
	virtual bool HavePictureWithTexture(ID2D1Bitmap * pTexture) const = 0;
};

class IShapeCollection : public IShapeProvider
{
public:
	virtual ~IShapeCollection() = default;

	virtual void DeleteShape(size_t index) = 0;
	virtual void DeleteShape(const CShapePtr &  pShape) = 0;

	virtual void PushBackShape(const CShapePtr & shape) = 0;
	virtual void InsertShape(size_t insertIndex, const CShapePtr & shape) = 0;


	virtual bool IsSelectShape(size_t index, const CShapePtr & selectedShape) const = 0;

};

class ICanvas
{
public:
	virtual ~ICanvas() = default;
	virtual IShapeCollection& GetShapeCollection() = 0;
	virtual IShapeProvider& GetShapeProvider() = 0;
	virtual void	SetSize(const SSize & size) = 0;
	virtual SSize	GetSize() const = 0;
};

template<typename T>
void DeleteLastElement(std::vector<T> & vector);

class CCanvas
	: public IShapeCollection
	, public ICanvas
{
public:
	CCanvas(const SSize & size, const CShapePtr & view);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	//--------------------------------------------
	// IShapeCollection
	void					DeleteShape(size_t index) override;
	void					DeleteShape(const CShapePtr & pShape) override;

	void					PushBackShape(const CShapePtr & shape) override;
	void					InsertShape(size_t insertIndex, const CShapePtr & shape) override;

	size_t					GetAmountShapes() const override;

	// For drag and drop
	bool					IsSelectShape(size_t index, const CShapePtr & selectedShape) const override;
	//--------------------------------------------
	void					Clear();

	//--------------------------------------------
	// IShapeProvider
	CShapePtr				GetShape(size_t index) override;
	CShapePtr				GetShape(const Vec2f mousePosition) override;
	size_t					GetShapeIndex(const CShapePtr & pShape) const override;

	std::vector<CShapePtr>&	GetShapes() override;
	bool					HavePictureWithTexture(ID2D1Bitmap * pTexture) const override;
	//--------------------------------------------
	void					SetShapes(const std::vector<CShapePtr> & shapes);
	//--------------------------------------------
	// ICanvas
	IShapeCollection&		GetShapeCollection() override;
	IShapeProvider&			GetShapeProvider() override;
	// Size
	void					SetSize(const SSize & size) override;
	SSize					GetSize() const override;

	//--------------------------------------------
	// For draw borders
	CShapePtr				GetView() const;

private:
	//////////////////////////////////////////////////////////////////////
	// Data
public:
private:
	// TODO : see might require do private
	std::vector<CShapePtr>	m_shapes;

	CShapePtr				m_view;
	SSize					m_size;
};

