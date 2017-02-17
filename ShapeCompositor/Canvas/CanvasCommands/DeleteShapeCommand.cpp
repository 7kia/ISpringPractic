#include "stdafx.h"
#include "DeleteShapeCommand.h"

CDeleteShapeCanvasCommand::CDeleteShapeCanvasCommand(CCanvas *const pCanvas
	, const CShapePtr shape
	, size_t index
)
	: m_typeDefinder()
	, m_pCanvas(pCanvas)
	, m_data(shape->GetShapeData())
	, m_index(index)
{
	//auto p = *shape.get();
	//m_type = m_typeDefinder.GetType(*shape.get());
	// TODO : include observer

}

void CDeleteShapeCanvasCommand::Execute()
{
	m_pCanvas->DeleteShape(m_index);
}

void CDeleteShapeCanvasCommand::Cancel()
{
	m_pCanvas->AddShape(m_type);
}
