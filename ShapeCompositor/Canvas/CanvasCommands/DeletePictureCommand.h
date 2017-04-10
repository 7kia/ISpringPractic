#pragma once

#pragma once

#include "CanvasCommand.h"
#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\Picture\Picture.h"
#include "Canvas\Picture\TextureStorage.h"

class IShapeCollection;
class CDeletePictureCommand : public IMyCommand
{
public:
	CDeletePictureCommand(
		IShapeCollection & pCanvas,
		CSelectedShape & seletedShape,
		CTextureStorage & textureStorage,
		const SPictureData & pictureData
	);
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
	const SPictureData m_pictureData;
	size_t m_index = 0;
	IShapeCollection & m_canvas;
	CSelectedShape & m_selectShape;
	CTextureStorage & m_textureStorage;
};