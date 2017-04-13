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
		std::for_each(m_currentCommand.base(), m_history.end(),
			[&](auto & iter)
		{
			iter->Destroy();
		}
		);
		if (std::find(m_currentCommand.base(), m_history.end(), m_saveLastCommand) != m_history.end())
		{
			m_saveLastCommand.reset();
		}
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
	m_saveLastCommand.reset();
}


bool CHistory::IsSave() const
{
	// foc new document
	
	// for erase part history, never will be empty history 
	// as erase was for add command instead other
	const bool noSaveLastCommand = !m_saveLastCommand;
	if (noSaveLastCommand && (m_history.empty() || (m_currentCommand == m_history.rend())) )
	{
		return true;
	}
	// not save return to start
	/*if (noSaveLastCommand && (m_currentCommand == m_history.rend()))
	{
		return true;
	}*/

	return 	m_saveLastCommand == *m_currentCommand;
}

void CHistory::DoSave()
{
	if (m_currentCommand != m_history.rend())
	{
		m_saveLastCommand = *m_currentCommand;
	}
}