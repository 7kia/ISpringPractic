#pragma once


#include "Canvas.h"
#include "CanvasCommands\AllCanvasCommand.h"
#include "MouseEventHandler.h"
#include "SelectShape.h"

class CCanvasController : public IMouseEventHandler
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

	void DeleteSelectShape();
	//--------------------------------------------
	// IMouseEventHandler

	 void HandleLButtHandleDown(CPoint point) override;
	 void HandleLButtHandleUp(CPoint point) override;
	 void HandleRButtHandleUp(CPoint point) override;
	 void HandleMouseMove(CPoint point) override;

	//--------------------------------------------

private:
	void AddCommand(const CanvasCommandPtr command);
	void ExecuteCurrent();
	void UndoCommand();
	void RedoCommand();
	void UpdateShapes(Vec2f point);

	CShapePresenterPtr GetShape(const CPoint position);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	// TODO : transfer to other place(might class)
	std::vector<CanvasCommandPtr>						m_history;
	std::vector<CanvasCommandPtr>::reverse_iterator		m_currentCommand = m_history.rbegin();

	CCanvas * m_pCanvas = nullptr;
};