// Lab2-1Test.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Canvas/Shapes/CShape.h"

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