#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\Picture\Picture.h"
#include "Canvas\Picture\TextureStorage.h"


class IShapeCollection;
class CAddPictureCommand : public IMyCommand
{
public:
	CAddPictureCommand(
		IShapeCollection & pCanvas,
		const SPictureData & pictureData,
		CTextureStorage & textureStorage,
		CSelectedShape & seletedShape
	);//ShapeType
	  //////////////////////////////////////////////////////////////////////
	  // Methods
public:
	//--------------------------------------------
	// IMyCommand
	void Execute() override;
	void Cancel() override;

	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	IShapeCollection & m_canvas;
	const SPictureData m_pictureData;
	CTextureStorage & m_textureStorage;
	CSelectedShape & m_selectShape;
};