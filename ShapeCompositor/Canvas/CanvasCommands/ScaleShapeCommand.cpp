#include "stdafx.h"
#include "ScaleShapeCommand.h"
#include "../SelectedShape.h"

CScaleShapeCanvasCommand::CScaleShapeCanvasCommand(
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

void CScaleShapeCanvasCommand::Execute()
{
	m_pShape->SetFrameData(m_newData);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->SetFrameData(m_newData);
		m_pSelectedShape->SetOldFrameData(m_newData);
	}
}

void CScaleShapeCanvasCommand::Cancel()
{
	m_pShape->SetFrameData(m_oldFrame);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->SetFrameData(m_oldFrame);
		m_pSelectedShape->SetOldFrameData(m_oldFrame);
	}
}

