#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\Shapes\ShapeViewFactory.h"

class IShapeCollection;
class CAddShapeCanvasCommand : public IMyCommand
{
public:
	CAddShapeCanvasCommand(
		IShapeCollection & pShapeCollection,
		CShapeModelPtr & pShapeModel,
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
	IShapeCollection & m_shapeCollection;
	CTextureStorage & m_textureStorage;
	CShapeModelPtr & m_shapeModel;
};