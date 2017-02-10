#pragma once

#include "AddShapeCommand.h"
#include "DeleteShapeCommand.h"

// IMyCommandPtr or IMyCommandSharedPtr
using CanvasCommandPtr = std::shared_ptr<IMyCommand>;
