#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\Picture\PictureView.h"
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
	const SPictureData m_pictureData;
	CTextureStorage & m_textureStorage;
	CSelectedShape & m_selectShape;
};