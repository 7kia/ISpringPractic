#include "stdafx.h"
#include "AddPictureCommand.h"
#include "../CanvasModel.h"
#include "GlobalFunctions.h"


CAddPictureCommand::CAddPictureCommand(
	IShapeCollection & pCanvas,
	const SPictureData & pictureData,
	CTextureStorage & textureStorage,
	CSelectedShape & seletedShape
)
	: m_shapeCollection(pCanvas)
	, m_pictureData(pictureData)
	, m_textureStorage(textureStorage)
	, m_selectShape(seletedShape)
{
}


void CAddPictureCommand::Execute()
{
	m_shapeCollection.PushBackShape(
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
	if (m_shapeCollection.IsSelectShape(m_shapeCollection.GetShapeCount() - 1, m_selectShape.GetShape()))
	{
		m_selectShape.ResetSelectShapePtr();
	}
	DeleteLastElement(m_shapeCollection.GetShapes());

	const auto shapeHavePicture = m_shapeCollection.GetShape(m_pictureData.pTexture);
	if (!shapeHavePicture)
	{
		m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(m_pictureData.pTexture), true);
	}

}

void CAddPictureCommand::Destroy()
{
	auto listShapesAfterDestroy = m_shapeCollection.GetShapes();
	listShapesAfterDestroy.pop_back();

	m_textureStorage.SetDelete(
		m_textureStorage.GetNameTexture(m_pictureData.pTexture),
		!HavePictureWithTexture(m_pictureData.pTexture, listShapesAfterDestroy)
	);
}
