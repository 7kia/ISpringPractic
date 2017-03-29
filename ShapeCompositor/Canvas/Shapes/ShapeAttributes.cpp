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
	// TODO: вставьте здесь оператор return
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

SRectF GetFrameRect(const IFrame & frame)
{
	SRectF rect;
	const Vec2f position = frame.GetPosition();
	const SSize size = frame.GetSize();

	rect.left = position.x - size.width / 2.f;
	rect.right = position.x + size.width / 2.f;
	rect.bottom = position.y + size.height / 2.f;
	rect.top = position.y - size.height / 2.f;

	return rect;
}


std::vector<Vec2f> CFrame::GetFrameVertices() const
{
	const SRectF ownRect = ::GetFrameRect(*this);

	return{
		Vec2f(ownRect.left, ownRect.bottom)// Left bootom
		, Vec2f(ownRect.right, ownRect.bottom)// Right bootom
		, Vec2f(ownRect.right, ownRect.top)// Right top
		, Vec2f(ownRect.left, ownRect.top)// Left top
	};
}

bool CFrame::operator==(const CFrame & frame) const
{
	return (frame.GetSize() == GetSize()) && (frame.GetPosition() == GetPosition());
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

CFrame CFrame::GetFrameData() const
{
	return CFrame(m_position, m_size);
}

void CFrame::SetFrameData(CFrame const & data)
{
	m_position = data.GetPosition();
	m_size = data.GetSize();
}