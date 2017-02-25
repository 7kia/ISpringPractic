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
SSize const operator +(SSize const &first, SSize const &second);

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
	bool operator!=(Vec2f const& vec) const;
	Vec2f& operator=(const Vec2f& right);

	float x = 0.f;
	float y = 0.f;
};
Vec2f const operator +(Vec2f const &first, Vec2f const &second);
Vec2f const operator -(Vec2f const &first, Vec2f const &second);
Vec2f const operator -(Vec2f const &first);

static const SSize DEFAULT_SIZE = SSize(50.f, 50.f);
static const Color DEFAULT_OUTLINE_COLOR = Color(0.f, 0.f, 0.f);
static const Color DEFAULT_FILL_COLOR = Color(0.45f, 0.75f, 0.55f);

/////////////////////////////////////////////////////////////
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


struct SFrameData
{
	SFrameData(const Vec2f position = Vec2f(), const SSize size = DEFAULT_SIZE);

	RECT GetOwnRect() const;
	std::vector<Vec2f> GetFrameVertices() const;

	Vec2f position;
	SSize size;
};


class IFrame
{
public:
	virtual ~IFrame() = default;

	// Position
	virtual void SetPosition(Vec2f position) = 0;
	virtual Vec2f GetPosition() const = 0;

	virtual void Move(const Vec2f shift) = 0;
	// Size
	virtual void SetSize(SSize size) = 0;
	virtual SSize GetSize() const = 0;

	virtual void UpdateScale(const Vec2f shift) = 0;
	// Own rect
	virtual RECT GetOwnRect() const = 0;

	// Get shape data
	virtual SFrameData GetFrameData() const = 0;
	virtual void SetFrameData(SFrameData const & data) = 0;

};
