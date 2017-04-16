#include "stdafx.h"
#include "DragPoint.h"

namespace
{
	static const SSize SELECTED_ELLIPSE_SIZE = SSize(10.f, 10.f);
}

CDragPoint::CDragPoint(const Vec2f position)
	: CEllipse(
		position,
		SELECTED_ELLIPSE_SIZE,
		BLACK_COLOR,
		BLACK_COLOR
	)
{
}
