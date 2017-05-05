#include "stdafx.h"
#include "AddShapeCommand.h"
#include "../CanvasModel.h"
#include "GlobalFunctions.h"

CAddShapeCanvasCommand::CAddShapeCanvasCommand(
	IShapeCollection & pShapeCollection,
	CShapeModelPtr & pShapeModel,
	CTextureStorage & textureStorage
)
	: m_shapeCollection(pShapeCollection)
	, m_shapeModel(pShapeModel)
	, m_textureStorage(textureStorage)
{
}

void CAddShapeCanvasCommand::Execute()
{
	m_shapeCollection.PushBackShape(m_shapeModel);

	if (m_shapeModel->GetType() == ShapeType::Picture)
	{
		auto pPictureModel = dynamic_cast<CPictureModel*>(m_shapeModel.get());

		m_textureStorage.SetDelete(m_textureStorage.GetNameTexture(pPictureModel->GetTexture()), false);
	}
}

void CAddShapeCanvasCommand::Cancel()
{
	DeleteLastElement(m_shapeCollection.GetShapes());

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

void CAddShapeCanvasCommand::Destroy()
{
	if (m_shapeModel->GetType() == ShapeType::Picture)
	{
		auto listShapesAfterDestroy = m_shapeCollection.GetShapes();
		listShapesAfterDestroy.pop_back();// TODO: check correctness

		auto pPictureModel = dynamic_cast<CPictureModel*>(m_shapeModel.get());

		m_textureStorage.SetDelete(
			m_textureStorage.GetNameTexture(pPictureModel->GetTexture()),
			!HavePictureWithTexture(pPictureModel->GetTexture(), listShapesAfterDestroy)
		);
	}
}
