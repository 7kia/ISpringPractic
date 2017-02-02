#pragma once

#include "AddShapeCommand.h"

// IMyCommandPtr or IMyCommandSharedPtr
using CanvasCommandPtr = std::shared_ptr<IMyCommand>;
