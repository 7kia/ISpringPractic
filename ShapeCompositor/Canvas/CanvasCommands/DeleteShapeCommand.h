#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"

class IShapeCollection;
class CDeleteShapeCanvasCommand : public IMyCommand
{
public:
	CDeleteShapeCanvasCommand(
		IShapeCollection & shapeCollection,
		CSelectedShape & selectedShape,
		CTextureStorage & textureStorage,
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
	CShapeModelPtr m_shapeModel;
	size_t m_index = 0;

	IShapeCollection & m_shapeCollection;
	CSelectedShape & m_selectShape;
	CTextureStorage & m_textureStorage;
};