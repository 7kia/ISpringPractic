#include "stdafx.h"
#include "DeleteShapeCommand.h"

CDeleteShapeCanvasCommand::CDeleteShapeCanvasCommand(CCanvas * pCanvas
	, CShapePresenterPtr shape
	, size_t index
)
	: m_pCanvas(pCanvas)
	, m_data(shape->GetChangedData())
{
}

void CDeleteShapeCanvasCommand::Execute()
{
}

void CDeleteShapeCanvasCommand::Cancel()
{
}
