// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Canvas/Shapes/CShape.h"
#include "Canvas/Shapes/AllShapes.h"

BOOST_AUTO_TEST_SUITE(CShape_suite)

struct Shape_
{
	CRectangleShape shape;
};
BOOST_FIXTURE_TEST_SUITE(Shape, Shape_)
	BOOST_AUTO_TEST_CASE(Have_position)
	{
		Vec2f pos(5.f, 10.f);

		shape.SetPosition(pos); 

		BOOST_CHECK(shape.GetPosition() == pos);
	}
	BOOST_AUTO_TEST_CASE(Have_inner_color)
	{
		Color color(0.2f, 0.4f, 0.1f);
		shape.SetFillColor(color);

		BOOST_CHECK(shape.GetFillColor() == color);
	}
	BOOST_AUTO_TEST_CASE(Have_outer_color)
	{
		Color color(0.3f, 0.5f, 0.13f);
		shape.SetOutlineColor(color);

		BOOST_CHECK(shape.GetOutlineColor() == color);
	}
BOOST_AUTO_TEST_SUITE_END()// Shape_

BOOST_AUTO_TEST_SUITE_END()// CShape


BOOST_AUTO_TEST_SUITE(CRectangle_suite)

struct Rectangle_
{
	CRectangleShape rectangle;
};
BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)
	BOOST_AUTO_TEST_CASE(Have_width)
	{
		float width = 3.2f;
		rectangle.SetWidth(width);

		BOOST_CHECK(rectangle.GetWidth() == width);
	}
	BOOST_AUTO_TEST_CASE(Have_height)
	{
		float height = 4.1f;
		rectangle.SetHeight(height);

		BOOST_CHECK(rectangle.GetHeight() == height);
	}
	BOOST_AUTO_TEST_CASE(Have_verteces)
	{
		float width = 1.2f;
		float height = 4.1f;
		rectangle.SetWidth(width);
		rectangle.SetHeight(height);

		auto verteces = rectangle.GetVertices();

		BOOST_CHECK(verteces[0] == Vec2f(- width / 2.f, height / 2.f));
		BOOST_CHECK(verteces[1] == Vec2f(width / 2.f, height / 2.f));
		BOOST_CHECK(verteces[2] == Vec2f(width / 2.f, -height / 2.f));
		BOOST_CHECK(verteces[3] == Vec2f(-width / 2.f, -height / 2.f));

	}
BOOST_AUTO_TEST_SUITE_END()// Rectangle_


struct Circle_
{
	CCircleShape circle;
};
BOOST_FIXTURE_TEST_SUITE(Circle, Circle_)
BOOST_AUTO_TEST_CASE(Have_radius)
{
	float radius = 6.8f;
	circle.SetRadius(radius);

	BOOST_CHECK(circle.GetRadius() == radius);
}
BOOST_AUTO_TEST_SUITE_END()// Circle_

struct Triangle_
{
	Vec2f first;
	Vec2f second;
	Vec2f third;

	Vec2f pos;

	CTriangleShape triangle;

	Triangle_()
		: first(-11.f, 29.f)
		, second(14.f, 29.f)
		, third(1.5f, -25.f)
		, triangle(Vec2f(1.5f, 2.f), 25.f, 54.f)
	{

	}
};
BOOST_FIXTURE_TEST_SUITE(Triangle, Triangle_)
BOOST_AUTO_TEST_CASE(Have_points)
{
	auto verteces = triangle.GetVertices();

	BOOST_CHECK(verteces[0] == first);
	BOOST_CHECK(verteces[1] == second);
	BOOST_CHECK(verteces[2] == third);
}
BOOST_AUTO_TEST_SUITE_END()// Triangle_

BOOST_AUTO_TEST_SUITE_END()// CShape_suite
