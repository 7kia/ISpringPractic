#include "stdafx.h"
#include "ScaleShapeCommand.h"
#include "../SelectShape.h"

CScaleShapeCanvasCommand::CScaleShapeCanvasCommand(
	CShapePtr pShape
	, SFrameData oldData
	, SFrameData newData
	, CSelectShape * pSelectedShape
)
	: m_pShape(pShape)
	, m_oldData(oldData)
	, m_newData(newData)
	, m_pSelectedShape(pSelectedShape)
{
}

void CScaleShapeCanvasCommand::Execute()
{
	m_pShape->SetFrameData(m_newData);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->SetFrameData(m_newData);
	}
}

void CScaleShapeCanvasCommand::Cancel()
{
	m_pShape->SetFrameData(m_oldData);

	if (m_pSelectedShape->GetShape() == m_pShape)
	{
		m_pSelectedShape->SetFrameData(m_oldData);
	}
}

