#include "stdafx.h"
#include "ChangeShapeRectCommand.h"
#include "../SelectedShape.h"
#include "../Canvas.h"

CChangeShapeRectCanvasCommand::CChangeShapeRectCanvasCommand(
	IGetShape * pShapeStorage
	, const CFrame & oldData
	, const CFrame & newData
	, CSelectedShape & selectedShape
)
	: m_pCanvas(pShapeStorage)
	, m_index(pShapeStorage->GetShapeIndex(selectedShape.GetShape()))
	, m_oldFrame(oldData)
	, m_newData(newData)
	, m_pSelectedShape(&selectedShape)
{
}

void CChangeShapeRectCanvasCommand::Execute()
{
	CShapePtr shape = m_pCanvas->GetShape(m_index);
	shape->SetFrameData(m_newData);

	if (m_pSelectedShape->GetShape() == shape)
	{
		m_pSelectedShape->SetFrameData(m_newData);
		m_pSelectedShape->SetOldFrameData(m_newData);
	}
}

void CChangeShapeRectCanvasCommand::Cancel()
{
	CShapePtr shape = m_pCanvas->GetShape(m_index);
	shape->SetFrameData(m_oldFrame);

	if (m_pSelectedShape->GetShape() == shape)
	{
		m_pSelectedShape->SetFrameData(m_oldFrame);
		m_pSelectedShape->SetOldFrameData(m_oldFrame);
	}
}
