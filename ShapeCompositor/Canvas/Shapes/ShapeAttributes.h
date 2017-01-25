#pragma once

#include <d2d1.h>
#include <functional>

struct Vec2f
{
	Vec2f() = default;
	Vec2f(float x, float y);

	bool operator==(Vec2f const& vec) const;

	float x;
	float y;
};

struct Color
{
	Color() = default;
	Color(float r
		, float g
		, float b
		, float a = 1.f);

	bool operator==(Color const& other) const;

	float r;
	float g;
	float b;
	float a;
};