#pragma once

#include <d2d1.h>
#include <functional>
#include <vector>

struct SSize
{
	SSize();
	SSize(float width, float height);
	float width = 0.f;
	float height = 0.f;
};

struct Vec2f
{
	Vec2f() = default;
	Vec2f(float x, float y);

	bool operator==(Vec2f const& vec) const;

	float x = 0.f;
	float y = 0.f;
};

struct Color
{
	Color() = default;
	Color(float r
		, float g
		, float b
		, float a = 1.f);

	bool operator==(Color const& other) const;

	float r = 0.f;
	float g = 0.f;
	float b = 0.f;
	float a = 1.f;
};

// Mixin
class IHaveVertex
{
public:
	virtual ~IHaveVertex() = default;

	virtual std::vector<Vec2f> GetVertices() const = 0;
};