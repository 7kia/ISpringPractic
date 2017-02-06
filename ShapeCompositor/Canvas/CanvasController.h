#pragma once


#include "Canvas.h"
#include "CanvasCommands\AllCanvasCommand.h"

class CCanvasController
{
public:
	CCanvasController(CCanvas * pCanvas);

	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	// Commands
	void AddTriangle();
	void AddRectangle();
	void AddEllipse();
	void Undo();
	void Redo();

private:
	void AddCommand(const CanvasCommandPtr command);
	void ExecuteCurrent();
	void UndoCommand();
	void RedoCommand();
	void UpdateShapes(Vec2f point);

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	// TODO : transfer to other place(might class)
	std::vector<CanvasCommandPtr>						m_history;
	std::vector<CanvasCommandPtr>::reverse_iterator		m_currentCommand = m_history.rbegin();


	CCanvas * m_pCanvas = nullptr;
};