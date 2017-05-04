#include "stdafx.h"
#include "ChangeShapeRectCommand.h"
#include "../SelectedShape.h"
#include "../CanvasModel.h"

CChangeShapeRectCanvasCommand::CChangeShapeRectCanvasCommand(
	IShapeProvider & pShapeStorage,
	const CFrame & oldData,
	const CFrame & newData,
	CSelectedShape & selectedShape
)
	: m_shapeCollection(pShapeStorage)
	, m_index(pShapeStorage.GetShapeIndex(selectedShape.GetShape()))
	, m_oldFrame(oldData)
	, m_newData(newData)
	, m_pSelectedShape(&selectedShape)
{
}

void CChangeShapeRectCanvasCommand::Execute()
{
	CShapeViewPtr shape = m_shapeCollection.GetShape(m_index);
	shape->SetFrame(m_newData);

	if (m_pSelectedShape->GetShape() == shape)
	{
		m_pSelectedShape->SetFrame(m_newData);
	}
}

void CChangeShapeRectCanvasCommand::Cancel()
{
	CShapeViewPtr shape = m_shapeCollection.GetShape(m_index);
	shape->SetFrame(m_oldFrame);

	if (m_pSelectedShape->GetShape() == shape)
	{
		m_pSelectedShape->SetFrame(m_oldFrame);
	}
}

void CChangeShapeRectCanvasCommand::Destroy()
{
}

