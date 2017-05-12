#include "stdafx.h"

#include "Canvas\CanvasCommands\AddShapeCommand.h"
#include "Canvas\CanvasCommands\DeleteShapeCommand.h"
#include "Canvas\CanvasCommands\ChangeShapeRectCommand.h"

#include "Canvas\Shapes\Picture\PictureView.h"
#include "Canvas\Shapes\Picture\TextureStorage.h"
#include "Canvas\Shapes\Picture\D2DImageFactory.h"

#include "Canvas\Shapes\AllViewShapes.h"
#include "Canvas\Shapes\ShapeViewFactory.h"

#include "Canvas\D2DObjectRenderer.h"
#include "Canvas\History.h"
#include "Canvas\SelectedShape.h"
#include "Canvas\CanvasModel.h"

#include "FileWork\FileManager.h"
#include "FileWork\MyDocument.h"
#include "FileWork\XMLReader.h"

#include "ShapeCompositorView.h"
#include "ShapeCompositorModel.h"
#include "ShapeCompositorDoc.h"