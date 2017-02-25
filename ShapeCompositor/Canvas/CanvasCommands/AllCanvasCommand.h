#pragma once

#include "AddShapeCommand.h"
#include "DeleteShapeCommand.h"
#include "MoveShapeCommand.h"
#include "ScaleShapeCommand.h"

// IMyCommandPtr or IMyCommandSharedPtr
using CanvasCommandPtr = std::shared_ptr<IMyCommand>;
