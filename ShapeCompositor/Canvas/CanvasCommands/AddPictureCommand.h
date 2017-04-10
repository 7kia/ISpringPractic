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
		ID2D1Bitmap * pTexture,
		const Vec2f position,
		const SSize size,
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
	ID2D1Bitmap * m_pTexture = nullptr;
	const Vec2f m_position;
	const SSize m_size;
	CTextureStorage & m_textureStorage;
	CSelectedShape & m_selectShape;
};