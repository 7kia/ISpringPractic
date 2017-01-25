// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Canvas/Shapes/CShape.h"
#include "Canvas/Shapes/RectangleShape.h"

BOOST_AUTO_TEST_SUITE(CShape_suite)

struct Shape_
{
	CShape shape;
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
		shape.SetInnerColor(color);

		BOOST_CHECK(shape.GetInnerColor() == color);
	}
	BOOST_AUTO_TEST_CASE(Have_outer_color)
	{
		Color color(0.3f, 0.5f, 0.13f);
		shape.SetOuterColor(color);

		BOOST_CHECK(shape.GetOuterColor() == color);
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
BOOST_AUTO_TEST_SUITE_END()// Rectangle_

BOOST_AUTO_TEST_SUITE_END()// CRectangle_suite
