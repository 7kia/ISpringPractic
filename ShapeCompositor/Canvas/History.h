#pragma once

#include "CanvasCommands\AllCanvasCommand.h"

#include <vector>
#include <deque>

class CCanvas;

class CHistory
{
public:
	CHistory();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void AddAndExecuteCommand(CanvasCommandPtr && command);

	void Undo();
	void Redo();

	void Clear();
private:
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::deque<CanvasCommandPtr>						m_history;
	std::deque<CanvasCommandPtr>::reverse_iterator		m_currentCommand = m_history.rbegin();
};