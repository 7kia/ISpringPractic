#include "stdafx.h"
#include "DeleteShapeCommand.h"
#include "../Canvas.h"

CDeleteShapeCanvasCommand::CDeleteShapeCanvasCommand(
	IShapeCollection & pCanvas,
	CSelectedShape & seletedShape,
	const CShapeFactory & factory
)
	: m_canvas(canvas)
	, m_selectShape(selectedShape)
	, m_factory(factory)
	, m_data(selectedShape.GetShape()->GetShapeData())
	, m_index(canvas.GetShapeIndex(selectedShape.GetShape()))
{
}

void CDeleteShapeCanvasCommand::Execute()
{
	if (m_canvas.IsSelectShape(m_index, m_selectShape.GetShape()))
	{
		m_selectShape.ResetSelectShapePtr();
	}
	m_canvas.DeleteShape(m_index);
}

void CDeleteShapeCanvasCommand::Cancel()
{
	m_canvas.InsertShape(m_index, m_factory.CreateShape(m_data));
}

void CDeleteShapeCanvasCommand::Destroy()
{
}
