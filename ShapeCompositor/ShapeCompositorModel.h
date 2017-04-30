#pragma once

#include "FileWork\MyDocument.h"
#include "Canvas\Picture\Picture.h"
#include "Canvas\Picture\D2DImageFactory.h"
#include "Canvas\Picture\TextureStorage.h"
#include "Signal.h"


class CShapeCompositorModel
	: public IHistoryManipulator
	, public IDocumentManipulator
{
public:
	CShapeCompositorModel();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	D2D1_RECT_F GetCanvasRect() const;
	CShapePtr GetCanvasBorder() const;
	void LoadPicture(const boost::filesystem::path & path, CSelectedShape & selectedShape);
	void SetRenderTargetForImageFactory(ID2D1HwndRenderTarget * pRenderTarget);

	signal::Connection DoOnResetSelectedShape(std::function<void()> const & action);

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


	IShapeCollection & GetShapeCollection();

	void DeleteShape(CSelectedShape & selectedShape);
	void CreateShape(ShapeType type, CSelectedShape & selectedShape);
	void CreatePicture(CSelectedShape & selectedShape);
	void ChangeRect(const CFrame oldFrame, CSelectedShape & selectedShape);


private:
	void ResetShapeCompositor();

	int SaveChangeDocument();

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
