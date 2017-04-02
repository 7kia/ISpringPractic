#pragma once

#include "AddShapeCommand.h"
#include "DeleteShapeCommand.h"
#include "ChangeShapeRectCommand.h"

// IMyCommandPtr or IMyCommandSharedPtr
using CanvasCommandPtr = std::shared_ptr<IMyCommand>;
