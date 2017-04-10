#pragma once

#include "AddShapeCommand.h"
#include "DeleteShapeCommand.h"
#include "ChangeShapeRectCommand.h"
#include "AddPictureCommand.h"

// IMyCommandPtr or IMyCommandSharedPtr
using CanvasCommandPtr = std::shared_ptr<IMyCommand>;
