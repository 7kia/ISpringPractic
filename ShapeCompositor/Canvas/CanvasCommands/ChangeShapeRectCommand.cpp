#include "stdafx.h"
#include "ChangeShapeRectCommand.h"
#include "../SelectedShape.h"
#include "../CanvasModel.h"

CChangeShapeRectCanvasCommand::CChangeShapeRectCanvasCommand(
	IShapeProvider & pShapeStorage,
	const CFrame & oldFrame,
	const CFrame & newFrame,
	size_t shapeIndex
)
	: m_shapeCollection(pShapeStorage)
	, m_shapeIndex(shapeIndex)
	, m_oldFrame(oldFrame)
	, m_newFrame(newFrame)
{
}

void CChangeShapeRectCanvasCommand::Execute()
{
	auto shape = m_shapeCollection.GetShape(m_shapeIndex);
	shape->Update(m_newFrame);
}

void CChangeShapeRectCanvasCommand::Cancel()
{
	auto shape = m_shapeCollection.GetShape(m_shapeIndex);
	shape->Update(m_oldFrame);
}

void CChangeShapeRectCanvasCommand::Destroy()
{
}

