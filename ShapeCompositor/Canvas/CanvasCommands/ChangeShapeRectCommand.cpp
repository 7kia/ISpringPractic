#include "stdafx.h"
#include "ChangeShapeRectCommand.h"
#include "../SelectedShape.h"

CChangeShapeRectCanvasCommand::CChangeShapeRectCanvasCommand(
	CShapePtr pShape
	, const CFrame & oldData
	, const CFrame & newData
	, CSelectedShape & selectedShape
)
	: m_pShape(pShape)
	, m_oldFrame(oldData)
	, m_newData(newData)
	, m_pSelectedShape(&selectedShape)
{
}

void CChangeShapeRectCanvasCommand::Execute()
{
	m_pShape->SetFrameData(m_newData);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->SetFrameData(m_newData);
		m_pSelectedShape->SetOldFrameData(m_newData);
	}
}

void CChangeShapeRectCanvasCommand::Cancel()
{
	m_pShape->SetFrameData(m_oldFrame);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->SetFrameData(m_oldFrame);
		m_pSelectedShape->SetOldFrameData(m_oldFrame);
	}
}

