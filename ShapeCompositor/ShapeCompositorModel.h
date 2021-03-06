#pragma once

#include "FileWork\MyDocument.h"
#include "Canvas\Shapes\Picture\PictureView.h"
#include "Canvas\Shapes\Picture\D2DImageFactory.h"
#include "Canvas\Shapes\Picture\TextureStorage.h"
#include "Canvas\CanvasModel.h"
#include "Canvas\History.h"
#include "Signal.h"

class IShapeManipulator
{
public:
	virtual ~IShapeManipulator() = default;

	virtual void DeleteShape(size_t shapeIndex) = 0;
	virtual void CreateShape(ShapeType type) = 0;
	virtual void ChangeRect(const CFrame oldFrame, const CFrame newFrame, size_t shapeIndex) = 0;

	virtual signal::Connection DoOnCreateView(std::function<void(const CShapeViewPtr&, size_t)> const & action) = 0;
	virtual signal::Connection DoOnDeleteView(std::function<void(size_t)> const & action) = 0;
};

class IModelReseter
{
public:
	virtual ~IModelReseter() = default;

	virtual void ResetModel() = 0;
	virtual signal::Connection DoOnResetView(std::function<void()> const & action) = 0;

	virtual IModelReseter & GetModelReseter() = 0;
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
	bool OpenDocument() override;
	bool NewDocument() override;
	//--------------------------------------------
	// IModelReseter
	void ResetModel() override;
	signal::Connection DoOnResetView(std::function<void()> const & action) override;
	IModelReseter & GetModelReseter() override;
	//--------------------------------------------
	// IShapeManipulator
	void DeleteShape(size_t shapeIndex) override;
	void CreateShape(ShapeType type) override;
	void ChangeRect(const CFrame oldFrame, const CFrame newFrame, size_t shapeIndex) override;

	signal::Connection DoOnCreateView(std::function<void(const CShapeViewPtr&, size_t)> const & action) override;
	signal::Connection DoOnDeleteView(std::function<void(size_t)> const & action) override;
	//--------------------------------------------

private:
	int SaveChangeDocument();
	void LoadPicture(const boost::filesystem::path & path);

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	signal::Signal<void()> m_resetView;

	CCanvasModel m_domainModel;
	CHistory m_history;
	CMyDocument m_document;

	CShapeViewFactory m_shapeFactory;
	CTextureStorage m_textureStorage;
	CD2DImageFactory m_imageFactory;
};
