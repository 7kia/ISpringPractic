#include "stdafx.h"
#include "ShapeAttributes.h"


SSize::SSize(float width, float height)
	: width(width)
	, height(height)
{
}

bool SSize::operator==(SSize const & size) const
{
	return (size.width == width) && (size.height == height);
}

Color::Color(float r
			, float g
			, float b
			, float a)
	: r(r)
	, g(g)
	, b(b)
	, a(a)
{
}

bool Color::operator==(Color const & other) const
{
	return (r == other.r)
		&& (g == other.g)
		&& (b == other.b)
		&& (a == other.a);
}

Vec2f::Vec2f(float x, float y)
	: x(x)
	, y(y)
{
}

bool Vec2f::operator==(Vec2f const & vec) const
{
	return (fabs(x - vec.x) < std::numeric_limits<float>::epsilon())
		&& (fabs(y - vec.y) < std::numeric_limits<float>::epsilon());
}

Vec2f const operator+(Vec2f const & first, Vec2f const & second)
{
	return Vec2f(first.x + second.x, first.y + second.y);
}

Vec2f const operator-(Vec2f const & first, Vec2f const & second)
{
	return Vec2f(first.x - second.x, first.y - second.y);
}