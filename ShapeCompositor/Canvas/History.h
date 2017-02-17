#pragma once

#include "CanvasCommands\AllCanvasCommand.h"

#include <vector>

class CCanvas;

class CHistory
{
public:
	CHistory(CCanvas * pCanvas);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// 
	void AddTriangle();
	void AddRectangle();
	void AddEllipse();
	void DeleteSelectShape();
	void Undo();
	void Redo();

private:

	void AddCommand(const CanvasCommandPtr command);
	void ExecuteCurrent();
	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::vector<CanvasCommandPtr>						m_history;
	std::vector<CanvasCommandPtr>::reverse_iterator		m_currentCommand = m_history.rbegin();

	CCanvas * m_pCanvas = nullptr;
};