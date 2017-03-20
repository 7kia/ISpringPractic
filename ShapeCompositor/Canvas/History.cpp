#include "stdafx.h"
#include "History.h"
#include "Canvas.h"

CHistory::CHistory()
	: IHistory()
{
}

void CHistory::AddAndExecuteCommand(const CanvasCommandPtr & command)
{
	// TODO : insert to middle queue
	if (!m_history.empty() && (m_currentCommand != m_history.rbegin()))
	{
		m_history.erase(m_currentCommand.base(), m_history.end());
	}
	m_history.push_back(command);
	m_currentCommand = m_history.rbegin();

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

void CHistory::Clear()
{
	m_history.clear();
	m_currentCommand = m_history.rbegin();
}
