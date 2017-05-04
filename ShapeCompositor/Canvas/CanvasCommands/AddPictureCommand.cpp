#include "stdafx.h"
#include "AddPictureCommand.h"
#include "../Canvas.h"
#include "GlobalFunctions.h"


CAddPictureCommand::CAddPictureCommand(
	IShapeCollection & pCanvas,
	const SPictureData & pictureData,
	CTextureStorage & textureStorage,
	CSelectedShape & seletedShape
)
	: m_canvas(pCanvas)
	, m_pictureData(pictureData)
	, m_textureStorage(textureStorage)
	, m_selectShape(seletedShape)
{
}


void CAddPictureCommand::Execute()
{
	m_canvas.PushBackShape(
		std::make_shared<CPictureView>(
			m_pictureData.pTexture,
			m_pictureData.position,
			m_pictureData.size
		)
	);

	m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(m_pictureData.pTexture), false);
}

void CAddPictureCommand::Cancel()
{
	if (m_canvas.IsSelectShape(m_canvas.GetShapeCount() - 1, m_selectShape.GetShape()))
	{
		m_selectShape.ResetSelectShapePtr();
	}
	DeleteLastElement(m_canvas.GetShapes());

	const auto shapeHavePicture = m_canvas.GetShape(m_pictureData.pTexture);
	if (!shapeHavePicture)
	{
		m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(m_pictureData.pTexture), true);
	}

}

void CAddPictureCommand::Destroy()
{
	auto listShapesAfterDestroy = m_canvas.GetShapes();
	listShapesAfterDestroy.pop_back();

	m_textureStorage.SetDelete(
		m_textureStorage.GetNameTexture(m_pictureData.pTexture),
		!HavePictureWithTexture(m_pictureData.pTexture, listShapesAfterDestroy)
	);
}
