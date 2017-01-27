#include "stdafx.h"
#include "Canvas.h"



CCanvas::CController::CController(CCanvas * pCanvas)
	: m_pCanvas(pCanvas)
{

}


void CCanvas::CController::ExecuteCommand(Command command)
{
	PCanvasCommand createCommand;
	switch (command)
	{
	case Command::AddTriangle:
		createCommand = std::make_shared<CAddShapeCanvasCommand>(m_pCanvas, TypeShape::Triangle);
		AddCommand(createCommand);
		ExecuteCurrent();
		break;
	case Command::AddRectangle:
		createCommand = std::make_shared<CAddShapeCanvasCommand>(m_pCanvas, TypeShape::Rectangle);
		AddCommand(createCommand);
		ExecuteCurrent();
		break;
	case Command::AddEllipse:
		createCommand = std::make_shared<CAddShapeCanvasCommand>(m_pCanvas, TypeShape::Ellipse);
		AddCommand(createCommand);
		ExecuteCurrent();
		break;
	case Command::Undo:
		UndoCommand();
		break;
	case Command::Redo:
		RedoCommand();
		break;
	default:
		break;
	}
}

void CCanvas::CController::AddCommand(const PCanvasCommand command)
{
	// TODO : insert to middle queue
	if (!m_history.empty() && (m_currentCommand != m_history.rbegin()))
	{
		m_history.erase(m_currentCommand.base(), m_history.end());
	}
	m_history.push_back(command);
	m_currentCommand = m_history.rbegin();
}

void CCanvas::CController::ExecuteCurrent()
{
	m_currentCommand->get()->Execute();
}

void CCanvas::CController::UndoCommand()
{
	if (m_currentCommand != m_history.rend())
	{
		m_currentCommand->get()->Cancel();
		++m_currentCommand;
	}
}

void CCanvas::CController::RedoCommand()
{
	if (m_currentCommand != m_history.rbegin())
	{
		--m_currentCommand;
		m_currentCommand->get()->Execute();
	}
}