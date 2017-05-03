#include "stdafx.h"
#include "DeleteShapeCommand.h"
#include "../Canvas.h"

CDeleteShapeCanvasCommand::CDeleteShapeCanvasCommand(
	IShapeCollection & pCanvas,
	CSelectedShape & selectedShape,
	const CShapeViewFactory & factory
)
	: m_canvas(pCanvas)
	, m_selectShape(selectedShape)
	, m_factory(factory)
	, m_data(selectedShape.GetShape()->GetShapeData())
	, m_index(pCanvas.GetShapeIndex(selectedShape.GetShape()))
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
