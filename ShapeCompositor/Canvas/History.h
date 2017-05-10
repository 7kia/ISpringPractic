#pragma once

#include "CanvasCommands\AllCanvasCommand.h"

#include <vector>
#include <deque>

class IHistory
{
public:
	virtual ~IHistory() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual void AddAndExecuteCommand(const ICommandPtr & command) = 0;

	virtual void Undo() = 0;
	virtual void Redo() = 0;

	virtual void Clear() = 0;
};

struct IHistoryManipulator
{
	virtual ~IHistoryManipulator() = default;

	virtual void UndoCommand() = 0;
	virtual void RedoCommand() = 0;
	virtual void ClearHistory() = 0;
	virtual bool IsSave() const = 0;
	virtual void DoSave() = 0;
};

class CHistory : public IHistory
{
public:
	CHistory();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void AddAndExecuteCommand(const ICommandPtr & command) override;

	void Undo() override;
	void Redo() override;

	void Clear() override;

	// For save to document
	bool IsSave() const;
	void DoSave();
private:
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::deque<ICommandPtr>						m_history;
	std::deque<ICommandPtr>::reverse_iterator	m_currentCommand = m_history.rbegin();
	ICommandPtr									m_saveLastCommand;
};
