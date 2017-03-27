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

SSize & SSize::operator=(const SSize & right)
{
	width = right.width;
	height = right.height;

	return *this;
	// TODO: �������� ����� �������� return
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

Color & Color::operator=(const Color & right)
{
	r = right.r;
	g = right.g;
	b = right.b;
	a = right.a;

	return *this;
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

bool Vec2f::operator!=(Vec2f const & vec) const
{
	return !(*this == vec);
}

Vec2f & Vec2f::operator=(const Vec2f & right)
{
	x = right.x;
	y = right.y;

	return *this;
}

SSize const operator+(SSize const & first, SSize const & second)
{
	return SSize(first.width + second.width, first.height + second.height);
}

Vec2f const operator+(Vec2f const & first, Vec2f const & second)
{
	return Vec2f(first.x + second.x, first.y + second.y);
}

Vec2f const operator-(Vec2f const & first, Vec2f const & second)
{
	return Vec2f(first.x - second.x, first.y - second.y);
}

Vec2f const operator*(Vec2f const & first, Vec2f const & second)
{
	return Vec2f(first.x * second.x, first.y * second.y);
}

Vec2f const operator-(Vec2f const & first)
{
	return Vec2f(-first.x, -first.y);
}

SFrameData::SFrameData(const Vec2f position, const SSize size)
	: position(position)
	, size(size)
{
}

std::vector<Vec2f> SFrameData::GetFrameVertices() const
{
	//////////////////////////////////////
	// TODO : rewrite, delete SFrameData, 
	SRectF frame;

	frame.left = position.x - size.width / 2.f;
	frame.right = position.x + size.width / 2.f;
	frame.bottom = position.y + size.height / 2.f;
	frame.top = position.y - size.height / 2.f;
	//////////////////////////////////////

	return{
		Vec2f(frame.left, frame.bottom)// Left bootom
		, Vec2f(frame.right, frame.bottom)// Right bootom
		, Vec2f(frame.right, frame.top)// Right top
		, Vec2f(frame.left, frame.top)// Left top
	};
}

bool SFrameData::operator==(SFrameData const & data) const
{
	return (size == data.size) && (position == data.position);
}

CFrame::CFrame(
	const Vec2f & position
	, const SSize & size
)
	: m_position(position)
	, m_size(size)
{
}


void CFrame::SetPosition(Vec2f position)
{
	m_position = position;
}

Vec2f CFrame::GetPosition() const
{
	return m_position;
}

void CFrame::Move(const Vec2f shift)
{
	SetPosition(GetPosition() + shift);
}

void CFrame::SetSize(SSize size)
{
	m_size = size;
}

SSize CFrame::GetSize() const
{
	return m_size;
}


SFrameData CFrame::GetFrameData() const
{
	SFrameData info;
	info.position = m_position;
	info.size = m_size;
	return info;
}

void CFrame::SetFrameData(SFrameData const & data)
{
	m_position = data.position;
	m_size = data.size;
}