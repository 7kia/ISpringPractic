#pragma once

#include <memory>

class IMyCommand
{
public:
	virtual ~IMyCommand() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	virtual void Execute() = 0;
	virtual void Cancel() = 0;
	virtual void Destroy() = 0;
};

