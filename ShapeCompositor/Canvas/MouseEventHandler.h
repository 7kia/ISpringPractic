#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <afxwin.h>


class IMouseEventHandler
{
public:
	virtual ~IMouseEventHandler() = default;

	virtual bool HandleLButtHandleDown(CPoint point )= 0;
	virtual bool HandleLButtHandleUp(CPoint point) = 0;
	virtual bool HandleRButtHandleUp(CPoint point) = 0;
	virtual bool HandleMouseMove(CPoint point) = 0;
};