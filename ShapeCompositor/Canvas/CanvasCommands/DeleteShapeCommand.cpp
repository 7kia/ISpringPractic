#include "stdafx.h"
#include "DeleteShapeCommand.h"
#include "../Canvas.h"

CDeleteShapeCanvasCommand::CDeleteShapeCanvasCommand(
	CCanvas & canvas
	, CSelectedShape & selectedShape
	, const CShapeFactory & factory
)
	: m_pCanvas(&canvas)
	, m_pSelectShape(&selectedShape)
	, m_pFactory(&factory)
	, m_data(selectedShape.GetShape()->GetShapeData())
	, m_index(canvas.GetShapeIndex(selectedShape.GetShape()))
{
}

void CDeleteShapeCanvasCommand::Execute()
{
	if (m_pCanvas->IsSelectShape(m_index, m_pSelectShape->GetShape()))
	{
		m_pSelectShape->ResetSelectShapePtr();
	}
	m_pCanvas->DeleteShape(m_index);
}

void CDeleteShapeCanvasCommand::Cancel()
{
	m_pCanvas->InsertShape(m_index, m_pFactory->CreateShape(m_data));
}
