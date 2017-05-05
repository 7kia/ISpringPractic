#include "stdafx.h"
#include "DeleteShapeCommand.h"
#include "../CanvasModel.h"

CDeleteShapeCanvasCommand::CDeleteShapeCanvasCommand(
	IShapeCollection & shapeCollection,
	size_t insertIndex,
	CTextureStorage & textureStorage
)
	: m_shapeCollection(shapeCollection)
	, m_textureStorage(textureStorage)
	, m_shapeModel(shapeCollection.GetShape(insertIndex))
	, m_insertIndex(insertIndex)
{
}

void CDeleteShapeCanvasCommand::Execute()
{
	m_shapeCollection.DeleteShape(m_insertIndex);

	if (m_shapeModel->GetType() == ShapeType::Picture)
	{
		auto pPictureModel = dynamic_cast<CPictureModel*>(m_shapeModel.get());
		const auto shapeHavePicture = m_shapeCollection.GetShape(pPictureModel->GetTexture());
		if (!shapeHavePicture)
		{
			m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(pPictureModel->GetTexture()), true);
		}
	}
}

void CDeleteShapeCanvasCommand::Cancel()
{
	m_shapeCollection.InsertShape(m_insertIndex, m_shapeModel);

	if (m_shapeModel->GetType() == ShapeType::Picture)
	{
		auto pPictureModel = dynamic_cast<CPictureModel*>(m_shapeModel.get());

		m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(pPictureModel->GetTexture()), false);
	}
}

void CDeleteShapeCanvasCommand::Destroy()
{
	if (m_shapeModel->GetType() == ShapeType::Picture)
	{
		auto pPictureModel = dynamic_cast<CPictureModel*>(m_shapeModel.get());

		m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(pPictureModel->GetTexture()), false);
	}
}
