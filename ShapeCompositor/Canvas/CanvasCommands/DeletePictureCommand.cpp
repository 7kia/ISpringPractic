#include "stdafx.h"
#include "DeletePictureCommand.h"
#include "../CanvasModel.h"

CDeletePictureCommand::CDeletePictureCommand(
	IShapeCollection & pCanvas,
	CSelectedShape & seletedShape,
	CTextureStorage & textureStorage
)
	: m_shapeCollection(pCanvas)
	, m_selectShape(seletedShape)
	, m_index(pCanvas.GetShapeIndex(seletedShape.GetShape()))
	, m_textureStorage(textureStorage)
	, m_pictureData(dynamic_cast<CPictureView*>(seletedShape.GetShape().get())->GetPictureData())
{
}

void CDeletePictureCommand::Execute()
{
	if (m_shapeCollection.IsSelectShape(m_index, m_selectShape.GetShape()))
	{
		m_selectShape.ResetSelectShapePtr();
	}
	m_shapeCollection.DeleteShape(m_index);

	const auto shapeHavePicture = m_shapeCollection.GetShape(m_pictureData.pTexture);
	if (!shapeHavePicture)
	{
		m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(m_pictureData.pTexture), true);
	}

}

void CDeletePictureCommand::Cancel()
{
	m_shapeCollection.InsertShape(
		m_index, 
		std::make_shared<CPictureView>(
			m_pictureData.pTexture,
			m_pictureData.position,
			m_pictureData.size
		)
	);

	m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(m_pictureData.pTexture), false);
}

void CDeletePictureCommand::Destroy()
{
	m_textureStorage.SetDelete(
		m_textureStorage.GetNameTexture(m_pictureData.pTexture),
		false
	);
}
