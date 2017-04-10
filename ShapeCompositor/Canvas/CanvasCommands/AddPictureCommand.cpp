#include "stdafx.h"
#include "AddPictureCommand.h"
#include "../Canvas.h"

CAddPictureCommand::CAddPictureCommand(
	IShapeCollection & pCanvas,
	ID2D1Bitmap * pTexture,
	const Vec2f position,
	const SSize size,
	CTextureStorage & textureStorage,
	CSelectedShape & seletedShape
)
	: m_canvas(pCanvas)
	, m_pTexture(pTexture)
	, m_position(position)
	, m_size(size)
	, m_textureStorage(textureStorage)
	, m_selectShape(seletedShape)
{
}


void CAddPictureCommand::Execute()
{
	m_canvas.PushBackShape(
		std::make_shared<CPicture>(
			m_pTexture,
			m_position,
			m_size
		)
	);

	m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(m_pTexture), false);
}

void CAddPictureCommand::Cancel()
{
	if (m_canvas.IsSelectShape(m_canvas.GetAmountShapes() - 1, m_selectShape.GetShape()))
	{
		m_selectShape.ResetSelectShapePtr();
	}
	DeleteLastElement(m_canvas.GetShapes());

	m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(m_pTexture), !m_canvas.HavePictureWithTexture(m_pTexture));
}