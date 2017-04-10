#include "stdafx.h"
#include "ChangeShapeRectCommand.h"
#include "../SelectedShape.h"
#include "../Canvas.h"

CChangeShapeRectCanvasCommand::CChangeShapeRectCanvasCommand(
	IShapeProvider & pShapeStorage
	, const CFrame & oldData
	, const CFrame & newData
	, CSelectedShape & selectedShape
)
	: m_canvas(pShapeStorage)
	, m_index(pShapeStorage.GetShapeIndex(selectedShape.GetShape()))
	, m_oldFrame(oldData)
	, m_newData(newData)
	, m_pSelectedShape(&selectedShape)
{
}

void CChangeShapeRectCanvasCommand::Execute()
{
	CShapePtr shape = m_canvas.GetShape(m_index);
	shape->SetFrame(m_newData);

	if (m_pSelectedShape->GetShape() == shape)
	{
		m_pSelectedShape->SetFrame(m_newData);
		m_pSelectedShape->SetOldFrame(m_newData);
	}
}

void CChangeShapeRectCanvasCommand::Cancel()
{
	CShapePtr shape = m_canvas.GetShape(m_index);
	shape->SetFrame(m_oldFrame);

	if (m_pSelectedShape->GetShape() == shape)
	{
		m_pSelectedShape->SetFrame(m_oldFrame);
		m_pSelectedShape->SetOldFrame(m_oldFrame);
	}
}

