#pragma once

#include <d2d1.h>
#include <functional>
#include <vector>

struct SSize
{
	SSize() = default;
	SSize(float width, float height);

	bool operator==(SSize const& size) const;
	SSize& operator=(const SSize& right);

	float width = 0.f;
	float height = 0.f;
};

struct Color
{
	Color() = default;
	Color(float r
		, float g
		, float b
		, float a = 1.f);

	bool operator==(Color const& other) const;
	Color& operator=(const Color& right);

	float r = 0.f;
	float g = 0.f;
	float b = 0.f;
	float a = 1.f;
};

static const Color NOT_COLOR = Color(0.f, 0.f, 0.f, 0.f);
static const Color BLACK_COLOR = Color(0.f, 0.f, 0.f, 1.f);
struct Vec2f
{
	Vec2f() = default;
	Vec2f(float x, float y);

	bool operator==(Vec2f const& vec) const;
	Vec2f& operator=(const Vec2f& right);

	float x = 0.f;
	float y = 0.f;
};
Vec2f const operator +(Vec2f const &first, Vec2f const &second);
Vec2f const operator -(Vec2f const &first, Vec2f const &second);

// Mixin
class IHaveVertex
{
public:
	virtual ~IHaveVertex() = default;

	virtual std::vector<Vec2f> GetVertices() const = 0;
};

class IIsPointIntersection
{
public:
	virtual ~IIsPointIntersection() = default;

	virtual bool IsPointIntersection(const Vec2f point) const {
		return false;
	};
};

class IShapeVisitor;
class IDrawable
{
public:
	virtual ~IDrawable() = default;

	// For render
	virtual void Accept(IShapeVisitor & renderer) const {};// TODO : must be = 0
};