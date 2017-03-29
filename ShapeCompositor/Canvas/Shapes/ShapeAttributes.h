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
Vec2f const operator *(Vec2f const &first, Vec2f const &second);
Vec2f const operator -(Vec2f const &first);

using ListVertices = std::vector<Vec2f>;

static const SSize DEFAULT_SIZE = SSize(50.f, 50.f);
static const Color DEFAULT_OUTLINE_COLOR = Color(0.f, 0.f, 0.f);
static const Color DEFAULT_FILL_COLOR = Color(0.45f, 0.75f, 0.55f);

/////////////////////////////////////////////////////////////
// Mixin

class IIsPointIntersection
{
public:
	virtual ~IIsPointIntersection() = default;

	virtual bool IsPointIntersection(const Vec2f point) const {
		return false;
	};
};

struct SRectF
{
	float left;
	float top;
	float right;
	float bottom;
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
};

class CFrame
	: public IFrame
{
public:
	CFrame(
		const Vec2f & position = Vec2f()
		, const SSize & size = DEFAULT_SIZE
	);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	// Position
	void SetPosition(Vec2f position) override;
	Vec2f GetPosition() const override;
	void Move(const Vec2f shift) override;
	// Size
	void SetSize(SSize size) override;
	SSize GetSize() const override;

	// Get shape data
	CFrame GetFrameData() const;
	void SetFrameData(CFrame const & data);

	std::vector<Vec2f> GetFrameVertices() const;

	bool operator==(const CFrame & frame) const;
	//////////////////////////////////////////////////////////////////////
	// Data
protected:
	Vec2f m_position;
	SSize m_size;
};

// Own rect
SRectF GetFrameRect(const IFrame & frame);
