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

	virtual void HandleLButtHandleDown(CPoint point )= 0;
	virtual void HandleLButtHandleUp(CPoint point) = 0;
	virtual void HandleRButtHandleUp(CPoint point) = 0;
	virtual void HandleMouseMove(CPoint point) = 0;
};