#include "stdafx.h"
#include "CanvasController.h"
#include "Canvas.h"

CCanvasController::CCanvasController(CCanvas * pCanvas)
	: m_pCanvas(pCanvas)
{

}


void CCanvasController::AddTriangle()
{
	CanvasCommandPtr createCommand = std::make_shared<CAddShapeCanvasCommand>(m_pCanvas, TypeShape::Triangle);
	AddCommand(createCommand);
	ExecuteCurrent();
}

void CCanvasController::AddRectangle()
{
	CanvasCommandPtr createCommand = std::make_shared<CAddShapeCanvasCommand>(m_pCanvas, TypeShape::Rectangle);
	AddCommand(createCommand);
	ExecuteCurrent();
}

void CCanvasController::AddEllipse()
{
	CanvasCommandPtr createCommand = std::make_shared<CAddShapeCanvasCommand>(m_pCanvas, TypeShape::Ellipse);
	AddCommand(createCommand);
	ExecuteCurrent();
}

void CCanvasController::Undo()
{
	UndoCommand();
}

void CCanvasController::Redo()
{
	RedoCommand();
}

void CCanvasController::HandleLButtHandleDown(CPoint point)
{
	auto selectShape = m_pCanvas->GetShapePresenter(Vec2f(float(point.x), float(point.y)));

	if (!selectShape._Expired())
	{
		1;

	}
}

void CCanvasController::HandleLButtHandleUp(CPoint point)
{
	// TODO
}

void CCanvasController::HandleRButtHandleUp(CPoint point)
{
	// TODO
}

void CCanvasController::HandleMouseMove(CPoint point)
{
	// TODO
}


void CCanvasController::AddCommand(const CanvasCommandPtr command)
{
	// TODO : insert to middle queue
	if (!m_history.empty() && (m_currentCommand != m_history.rbegin()))
	{
		m_history.erase(m_currentCommand.base(), m_history.end());
	}
	m_history.push_back(command);
	m_currentCommand = m_history.rbegin();
}

void CCanvasController::ExecuteCurrent()
{
	m_currentCommand->get()->Execute();
}

void CCanvasController::UndoCommand()
{
	if (m_currentCommand != m_history.rend())
	{
		m_currentCommand->get()->Cancel();
		++m_currentCommand;
	}
}

void CCanvasController::RedoCommand()
{
	if (m_currentCommand != m_history.rbegin())
	{
		--m_currentCommand;
		m_currentCommand->get()->Execute();
	}
}

void CCanvasController::UpdateShapes(Vec2f point)
{
	for (auto & shape : m_pCanvas->m_shapePresenters)
	{
		if(shape->IsPointIntersection(Vec2f(float(point.x), float(point.y))))
		{
			// TODO
		}
	}
}

CShapePresenterPtr CCanvasController::GetShape(const CPoint position)
{
	return m_pCanvas->GetShapePresenter(Vec2f(float(position.x), float(position.y)));
}
