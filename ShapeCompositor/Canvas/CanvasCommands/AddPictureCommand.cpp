#include "stdafx.h"
#include "AddPictureCommand.h"
#include "../Canvas.h"

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
		std::make_shared<CPicture>(
			m_pictureData.pTexture,
			m_pictureData.position,
			m_pictureData.size
		)
	);

	m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(m_pictureData.pTexture), false);
}

void CAddPictureCommand::Cancel()
{
	if (m_canvas.IsSelectShape(m_canvas.GetAmountShapes() - 1, m_selectShape.GetShape()))
	{
		m_selectShape.ResetSelectShapePtr();
	}
	DeleteLastElement(m_canvas.GetShapes());

	m_textureStorage.SetDelete(
		m_textureStorage.GetNameTexture(m_pictureData.pTexture),
		!m_canvas.HavePictureWithTexture(m_pictureData.pTexture)
	);
}