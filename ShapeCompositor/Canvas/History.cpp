#include "stdafx.h"
#include "History.h"

CHistory::CHistory(CCanvas * pCanvas)
	: m_pCanvas(pCanvas)
{
}

void CHistory::AddTriangle()
{
	CanvasCommandPtr createCommand = std::make_shared<CAddShapeCanvasCommand>(m_pCanvas, TypeShape::Triangle);
	AddCommand(createCommand);
	ExecuteCurrent();
}

void CHistory::AddRectangle()
{
	CanvasCommandPtr createCommand = std::make_shared<CAddShapeCanvasCommand>(m_pCanvas, TypeShape::Rectangle);
	AddCommand(createCommand);
	ExecuteCurrent();
}

void CHistory::AddEllipse()
{
	CanvasCommandPtr createCommand = std::make_shared<CAddShapeCanvasCommand>(m_pCanvas, TypeShape::Ellipse);
	AddCommand(createCommand);
	ExecuteCurrent();
}

void CHistory::AddCommand(const CanvasCommandPtr command)
{
	// TODO : insert to middle queue
	if (!m_history.empty() && (m_currentCommand != m_history.rbegin()))
	{
		m_history.erase(m_currentCommand.base(), m_history.end());
	}
	m_history.push_back(command);
	m_currentCommand = m_history.rbegin();
}

void CHistory::ExecuteCurrent()
{
	m_currentCommand->get()->Execute();
}

void CHistory::Undo()
{
	if (m_currentCommand != m_history.rend())
	{
		m_currentCommand->get()->Cancel();
		++m_currentCommand;
	}
}

void CHistory::Redo()
{
	if (m_currentCommand != m_history.rbegin())
	{
		--m_currentCommand;
		m_currentCommand->get()->Execute();
	}
}