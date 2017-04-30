#include "stdafx.h"
#include "DeletePictureCommand.h"
#include "../Canvas.h"

CDeletePictureCommand::CDeletePictureCommand(
	IShapeCollection & pCanvas,
	CSelectedShape & seletedShape,
	CTextureStorage & textureStorage
)
	: m_canvas(pCanvas)
	, m_selectShape(seletedShape)
	, m_index(pCanvas.GetShapeIndex(seletedShape.GetShape()))
	, m_textureStorage(textureStorage)
	, m_pictureData(dynamic_cast<CPicture*>(seletedShape.GetShape().get())->GetPictureData())
{
}

void CDeletePictureCommand::Execute()
{
	if (m_canvas.IsSelectShape(m_index, m_selectShape.GetShape()))
	{
		m_selectShape.ResetSelectShapePtr();
	}
	m_canvas.DeleteShape(m_index);
}

void CDeletePictureCommand::Cancel()
{
	m_canvas.InsertShape(
		m_index, 
		std::make_shared<CPicture>(
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
