#include "stdafx.h"

#include "Canvas\CanvasCommands\AddShapeCommand.h"
#include "Canvas\CanvasCommands\DeleteShapeCommand.h"
#include "Canvas\CanvasCommands\ChangeShapeRectCommand.h"
#include "Canvas\CanvasCommands\AddPictureCommand.h"
#include "Canvas\CanvasCommands\DeletePictureCommand.h"

#include "Canvas\Picture\Picture.h"
#include "Canvas\Picture\TextureStorage.h"
#include "Canvas\Picture\D2DImageFactory.h"

#include "Canvas\Shapes\AllShapes.h"
#include "Canvas\Shapes\ShapeFactory.h"

#include "Canvas\D2DObjectRenderer.h"
#include "Canvas\History.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\Canvas.h"

#include "FileWork\FileManager.h"
#include "FileWork\MyDocument.h"
#include "FileWork\XMLReader.h"

#include "ShapeCompositorView.h"
#include "ShapeCompositorModel.h"
#include "ShapeCompositorDoc.h"