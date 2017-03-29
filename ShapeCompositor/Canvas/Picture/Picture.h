#pragma once

#include "Canvas\Shapes\Rectangle.h"

class CPicture : public CRectangle
{
public:
	CPicture(
		const std::string textureName
		, const Vec2f position = Vec2f()
		, const SSize size = DEFAULT_SIZE
		, const Color fillColor = DEFAULT_FILL_COLOR
		, const Color outlineColor = DEFAULT_OUTLINE_COLOR
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	//--------------------------------------------
	// IDrawable

	void Accept(IShapeVisitor & renderer) const override;
	//--------------------------------------------
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::string m_textureName;
};