#include "stdafx.h"
#include "DeleteShapeCommand.h"
#include "../CanvasModel.h"

CDeleteShapeCanvasCommand::CDeleteShapeCanvasCommand(
	IShapeCollection & shapeCollection,
	CSelectedShape & selectedShape,
	CTextureStorage & textureStorage,
)
	: m_shapeCollection(shapeCollection)
	, m_selectShape(selectedShape)
	, m_textureStorage(textureStorage)
	, m_shapeModel(selectedShape.GetShape()->)
	, m_index(shapeCollection.GetShapeIndex(selectedShape.GetShape()))
{
}

void CDeleteShapeCanvasCommand::Execute()
{
	if (m_shapeCollection.IsSelectShape(m_index, m_selectShape.GetShape()))
	{
		m_selectShape.ResetSelectShapePtr();
	}
	m_shapeCollection.DeleteShape(m_index);

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
	m_shapeCollection.InsertShape(m_index, m_shapeModel);

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
