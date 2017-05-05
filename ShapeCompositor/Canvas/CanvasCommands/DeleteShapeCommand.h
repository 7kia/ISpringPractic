#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllViewShapes.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\Shapes\Picture\TextureStorage.h"

class IShapeCollection;
class CDeleteShapeCanvasCommand : public IMyCommand
{
public:
	CDeleteShapeCanvasCommand(
		IShapeCollection & shapeCollection,
		size_t insertIndex,
		CTextureStorage & textureStorage
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
	IShapeCollection & m_shapeCollection;
	size_t m_insertIndex = 0;
	CTextureStorage & m_textureStorage;
};