#include "stdafx.h"
#include "ShapeCompositorModel.h"

namespace
{
	static const SSize CANVAS_SIZE = SSize(640.f, 480.f);
	static const SSize MAX_SIZE = SSize(CANVAS_SIZE.width * SCALE_FACTOR, CANVAS_SIZE.height * SCALE_FACTOR);
	static const float SCALE_FACTOR = 0.8f;

}

CShapeCompositorModel::CShapeCompositorModel()
	: m_textureStorage(MAX_SIZE)
	, m_canvas(CANVAS_SIZE)
{
	m_canvasBorder = m_shapeFactory.CreateShape(
		SShapeData(
			ShapeType::Rectangle,
			Vec2f(CANVAS_SIZE.width / 2.f, CANVAS_SIZE.height / 2.f),
			CANVAS_SIZE,
			NOT_COLOR,
			BLACK_COLOR,
			3.f
		)
	);
}

D2D1_RECT_F CShapeCompositorModel::GetCanvasRect() const
{
	return m_canvas.GetRect();
}

CShapePtr CShapeCompositorModel::GetCanvasBorder() const
{
	return m_canvasBorder;
}

std::vector<CShapePtr> CShapeCompositorModel::GetCanvasShapes()
{
	return m_canvas.GetShapes();
}

CTextureStorage & CShapeCompositorModel::GetTextureStorage()
{
	return m_textureStorage;
}

void CShapeCompositorModel::LoadPicture(const boost::filesystem::path & path, CSelectedShape & selectedShape)
{
	const auto pictureName = path.filename().generic_wstring();

	m_textureStorage.AddTexture(
		pictureName,
		m_imageFactory.CreateTexture(path.generic_wstring())
	);

	const auto canvasSize = m_canvas.GetSize();
	m_history.AddAndExecuteCommand(std::make_shared<CAddPictureCommand>(
		m_canvas.GetShapeCollection(),
		SPictureData(
			m_textureStorage.GetTexture(pictureName),
			Vec2f(float(canvasSize.width) / 2.f, float(canvasSize.height) / 2.f),
			m_textureStorage.GetCorrectSize(pictureName)
		),
		m_textureStorage,
		selectedShape
		)
	);
}

void CShapeCompositorModel::SetRenderTargetForImageFactory(ID2D1HwndRenderTarget * pRenderTarget)
{
	m_imageFactory.SetRenderTarget(pRenderTarget);
}

void CShapeCompositorModel::UndoCommand()
{
	m_history.Undo();
}

void CShapeCompositorModel::RedoCommand()
{
	m_history.Redo();
}

void CShapeCompositorModel::ClearHistory()
{
	m_history.Clear();
}

bool CShapeCompositorModel::IsSave() const
{
	return m_history.IsSave();
}

void CShapeCompositorModel::DoSave()
{
	m_history.DoSave();
}

void CShapeCompositorModel::CreateShape(ShapeType type, CSelectedShape & selectedShape)
{
	m_history.AddAndExecuteCommand(
		std::make_shared<CAddShapeCanvasCommand>(
			m_canvas.GetShapeCollection()
			, type
			, m_shapeFactory
			, selectedShape
			)
	);
}
