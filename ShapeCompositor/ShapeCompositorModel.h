#pragma once

#include "FileWork\MyDocument.h"
#include "Canvas\Picture\Picture.h"
#include "Canvas\Picture\D2DImageFactory.h"
#include "Canvas\Picture\TextureStorage.h"
#include "Signal.h"

class IDataForSave
{
public:
	virtual ~IDataForSave() = default;

	virtual std::vector<CShapePtr> GetCanvasShapes() = 0;
	virtual CTextureStorage & GetTextureStorage() = 0;
}

class CShapeCompositorModel
	: public IHistoryManipulator
	, public IDataForSave
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
	//--------------------------------------------
	// IHistoryManipulator
	void UndoCommand() override;
	void RedoCommand() override;
	void ClearHistory() override;
	bool IsSave() const override;
	void DoSave() override;
	//--------------------------------------------
	// IDataForSave
	std::vector<CShapePtr> GetCanvasShapes() override;
	CTextureStorage & GetTextureStorage() override;
	//--------------------------------------------

	void CreateShape(ShapeType type, CSelectedShape & selectedShape);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CCanvas m_canvas;
	CShapePtr m_canvasBorder;

	CHistory m_history;

	CShapeFactory m_shapeFactory;
	CTextureStorage m_textureStorage;
	CD2DImageFactory m_imageFactory;
};
