#include "stdafx.h"
#include "ChangeShapeRectCommand.h"
#include "../SelectedShape.h"
#include "../CanvasModel.h"

CChangeShapeRectCanvasCommand::CChangeShapeRectCanvasCommand(
	IShapeProvider & pShapeStorage,
	const CFrame & oldData,
	size_t shapeIndex
)
	: m_shapeCollection(pShapeStorage)
	, m_shapeIndex(shapeIndex)
	, m_oldFrame(oldData)
	, m_newData(pShapeStorage.GetShape(shapeIndex)->GetFrame())
{
}

void CChangeShapeRectCanvasCommand::Execute()
{
	auto shape = m_shapeCollection.GetShape(m_shapeIndex);
	shape->SetFrame(m_newData);

	// SelectedShape necessary reset, send message - set m_newFrame

}

void CChangeShapeRectCanvasCommand::Cancel()
{
	auto shape = m_shapeCollection.GetShape(m_shapeIndex);
	shape->SetFrame(m_oldFrame);

	// SelectedShape necessary reset, send message - set m_oldFrame
}

void CChangeShapeRectCanvasCommand::Destroy()
{
}

