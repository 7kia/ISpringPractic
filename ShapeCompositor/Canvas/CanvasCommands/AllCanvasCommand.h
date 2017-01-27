#pragma once

#include "AddShapeCommand.h"

// IMyCommandPtr or IMyCommandSharedPtr
using PCanvasCommand = std::shared_ptr<IMyCommand>;
