#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllViewShapes.h"

class CSelectedShape;
class IShapeProvider;
class CChangeShapeRectCanvasCommand : public IMyCommand
{
public:
	CChangeShapeRectCanvasCommand(
		IShapeProvider & pShapeStorage,
		const CFrame & oldData,
		size_t shapeIndex
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// IMyCommand
	void Execute() override;
	void Cancel() override;
	void Destroy() override;
	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	IShapeProvider & m_shapeCollection;
	size_t		m_shapeIndex;
	CFrame		m_oldFrame;
	CFrame		m_newData;
};