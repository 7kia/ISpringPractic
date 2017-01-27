#include "stdafx.h"
#include "CanvasCommand.h"
#include "../Canvas.h"

CCanvasCommand::CCanvasCommand(CCanvas * pCanvas)
	: IMyCommand()
	, m_pCanvas(pCanvas)
{
}
