#pragma once

#include "FileWork\MyDocument.h"
#include "Canvas\Picture\Picture.h"
#include "Canvas\Picture\D2DImageFactory.h"
#include "Canvas\Picture\TextureStorage.h"
#include "Signal.h"

class IShapeManipulator
{
public:
	virtual ~IShapeManipulator() = default;

	virtual void DeleteShape(CSelectedShape & selectedShape) = 0;
	virtual void CreateShape(ShapeType type, CSelectedShape & selectedShape) = 0;
	virtual void ChangeRect(const CFrame oldFrame, CSelectedShape & selectedShape) = 0;
};

class IModelReseter
{
public:
	virtual ~IModelReseter() = default;

	virtual void ResetModel() = 0;
	virtual signal::Connection DoOnResetSelectedShape(std::function<void()> const & action) = 0;
};

class IDataForDraw
{
public:
	virtual ~IDataForDraw() = default;

	virtual CShapePtr GetCanvasBorder() const = 0;
	virtual std::vector<CShapePtr> & GetCanvasShapes() = 0;
};

class IHaveRenderTarget
{
public:
	virtual ~IHaveRenderTarget() = default;

	virtual void SetRenderTargetForModelComponents(ID2D1HwndRenderTarget * pRenderTarget) = 0;
};

class CShapeCompositorModel
	: public IHistoryManipulator
	, public IDocumentManipulator
	, public IShapeManipulator
	, public IModelReseter
	, public IDataForDraw
	, public IHaveRenderTarget
{
public:
	CShapeCompositorModel();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	D2D1_RECT_F GetCanvasRect() const;

	//--------------------------------------------
	// IHaveRenderTarget
	void SetRenderTargetForModelComponents(ID2D1HwndRenderTarget * pRenderTarget) override;
	//--------------------------------------------
	// IDataForDraw
	CShapePtr GetCanvasBorder() const override;
	std::vector<CShapePtr> & GetCanvasShapes() override;
	//--------------------------------------------
	// IHistoryManipulator
	void UndoCommand() override;
	void RedoCommand() override;
	void ClearHistory() override;
	bool IsSave() const override;
	void DoSave() override;
	//--------------------------------------------
	// IDocumentManipulator
	bool SaveAsDocument() override;
	bool SaveDocument() override;
	bool OpenDocument(CSelectedShape & selectedShape) override;
	bool NewDocument() override;
	//--------------------------------------------
	// IModelReseter
	void ResetModel() override;
	signal::Connection DoOnResetSelectedShape(std::function<void()> const & action) override;
	//--------------------------------------------
	// IShapeManipulator
	void DeleteShape(CSelectedShape & selectedShape) override;
	void CreateShape(ShapeType type, CSelectedShape & selectedShape) override;
	void ChangeRect(const CFrame oldFrame, CSelectedShape & selectedShape) override;
	//--------------------------------------------
	IShapeCollection & GetShapeCollection();

private:
	int SaveChangeDocument();
	void LoadPicture(const boost::filesystem::path & path, CSelectedShape & selectedShape);

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	signal::Signal<void()> m_resetSelectedShape;

	CCanvas m_canvas;
	CShapePtr m_canvasBorder;

	CHistory m_history;
	CMyDocument m_document;

	CShapeFactory m_shapeFactory;
	CTextureStorage m_textureStorage;
	CD2DImageFactory m_imageFactory;
};
