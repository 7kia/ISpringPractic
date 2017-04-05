// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Canvas/Shapes/CShape.h"
#include "Canvas/Shapes/ShapeFactory.h"

BOOST_AUTO_TEST_SUITE(CShape_suite)

struct Shape_
{
	class CTestShape : public CShape
	{
	public:
		CTestShape(
			const ShapeType type
			, const Vec2f position
			, const SSize size
			, const Color fillColor
			, const Color outlineColor
		) 
			: CShape(
				type
				, position
				, size
				, fillColor
				, outlineColor
			)
		{

		};

		void Accept(IShapeVisitor & renderer) const {};
	};
	CTestShape shape;

	Shape_()
		: shape(
			ShapeType::Rectangle
			, Vec2f()
			, DEFAULT_SIZE
			, DEFAULT_FILL_COLOR
			, DEFAULT_OUTLINE_COLOR
		)
	{

	}
};
BOOST_FIXTURE_TEST_SUITE(Shape, Shape_)
	BOOST_AUTO_TEST_CASE(Have_position)
	{
		Vec2f pos(5.f, 10.f);

		shape.SetPosition(pos); 

		BOOST_CHECK(shape.GetPosition() == pos);
	}
	BOOST_AUTO_TEST_CASE(Have_fill_color)
	{
		Color color(0.2f, 0.4f, 0.1f);
		shape.SetFillColor(color);

		BOOST_CHECK(shape.GetFillColor() == color);
	}
	BOOST_AUTO_TEST_CASE(Have_outline_color)
	{
		Color color(0.3f, 0.5f, 0.13f);
		shape.SetOutlineColor(color);

		BOOST_CHECK(shape.GetOutlineColor() == color);
	}
	BOOST_AUTO_TEST_CASE(Have_size)
	{
		SSize size(1.2f, 99.f);
		shape.SetSize(size);

		BOOST_CHECK(shape.GetSize() == size);
	}
	BOOST_AUTO_TEST_CASE(Have_outline_thikness)
	{
		const float thikness = 2.f;

		BOOST_CHECK_EQUAL(shape.GetOutlineThickness(), 1.f);

		shape.SetOutlineThickness(thikness);

		BOOST_CHECK_EQUAL(shape.GetOutlineThickness(), 2.f);
	}
	BOOST_AUTO_TEST_CASE(Can_change_frame)
	{
		SSize size(1.2f, 99.f);
		Vec2f pos(4.5f, -9.4f);

		CFrame setData(pos, size);

		shape.SetFrame(setData);

		BOOST_CHECK(shape.GetFrame() == setData);
	}
	BOOST_AUTO_TEST_CASE(Can_change_shape)
	{
		SShapeData setData(ShapeType::Ellipse
			, Vec2f(4.6f, -19.4f)
			, SSize(4.2f, 9.6f)
			, Color(1.f, 0.5f, 0.25f)
			, Color(0.6f, 0.35f, 0.325f)
		);

		shape.SetShapeData(setData);

		BOOST_CHECK(shape.GetShapeData() == setData);
	}
BOOST_AUTO_TEST_SUITE_END()// Shape_

BOOST_AUTO_TEST_SUITE_END()// CShape


BOOST_AUTO_TEST_SUITE(CRectangle_suite)

struct Rectangle_
{
	CRectangle rectangle;
	Rectangle_()
	{

	}

};
BOOST_FIXTURE_TEST_SUITE(Rectangle, Rectangle_)
	BOOST_AUTO_TEST_CASE(Have_verteces)
	{
		float width = 1.2f;
		float height = 4.1f;
		rectangle.SetSize(SSize(width, height));

		auto verteces = rectangle.GetVertices();

		BOOST_CHECK(verteces[0] == Vec2f(- width / 2.f, height / 2.f));
		BOOST_CHECK(verteces[1] == Vec2f(width / 2.f, height / 2.f));
		BOOST_CHECK(verteces[2] == Vec2f(width / 2.f, -height / 2.f));
		BOOST_CHECK(verteces[3] == Vec2f(-width / 2.f, -height / 2.f));
	}
	BOOST_AUTO_TEST_CASE(Check_point_intersection)
	{
		float width = 2.1f;
		float height = 4.9f;
		rectangle.SetSize(SSize(width, height));

		BOOST_CHECK(rectangle.IsPointIntersection(Vec2f()));
		BOOST_CHECK(!rectangle.IsPointIntersection(Vec2f(-width / 2.f -1.f, 0.f)));
		BOOST_CHECK(!rectangle.IsPointIntersection(Vec2f(width / 2.f + 1.f, 0.f)));
		BOOST_CHECK(!rectangle.IsPointIntersection(Vec2f(0.f, -height / 2.f - 1.f)));
		BOOST_CHECK(!rectangle.IsPointIntersection(Vec2f(0.f, height / 2.f + 1.f)));

		BOOST_CHECK(rectangle.IsPointIntersection(Vec2f(-width / 2.f, height / 2.f)));
		BOOST_CHECK(rectangle.IsPointIntersection(Vec2f(width / 2.f, height / 2.f)));
		BOOST_CHECK(rectangle.IsPointIntersection(Vec2f(width / 2.f, -height / 2.f)));
		BOOST_CHECK(rectangle.IsPointIntersection(Vec2f(-width / 2.f, -height / 2.f)));
	}
BOOST_AUTO_TEST_SUITE_END()// Rectangle_

struct Triangle_
{
	Vec2f first;
	Vec2f second;
	Vec2f third;

	Vec2f pos;

	CTriangle triangle;
	CTriangle secondTriangle;

	Triangle_()
		: first(-11.f, 29.f)
		, second(14.f, 29.f)
		, third(1.5f, -25.f)
		, triangle(Vec2f(1.5f, 2.f), SSize(25.f, 54.f))
		, secondTriangle(Vec2f(), SSize(1.f, 1.f))
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
	BOOST_AUTO_TEST_CASE(Check_point_intersection)
	{
		BOOST_CHECK(secondTriangle.IsPointIntersection(Vec2f(0.f, 0.f)));
		BOOST_CHECK(secondTriangle.IsPointIntersection(Vec2f(-0.5f, 0.5f)));
		BOOST_CHECK(secondTriangle.IsPointIntersection(Vec2f(0.5f, 0.5f)));

		BOOST_CHECK(!secondTriangle.IsPointIntersection(Vec2f(-0.5f, -0.5f)));
		BOOST_CHECK(!secondTriangle.IsPointIntersection(Vec2f(0.5f, -0.5f)));

		BOOST_CHECK(!secondTriangle.IsPointIntersection(Vec2f(-0.25f, -0.25f)));
		BOOST_CHECK(!secondTriangle.IsPointIntersection(Vec2f(0.25f, -0.25f)));

	}
BOOST_AUTO_TEST_SUITE_END()// Triangle_


struct Ellipse_
{
	CEllipse circle;
	CEllipse ellipse;

	Ellipse_()
		: circle(Vec2f(), SSize(1.f, 1.f), DEFAULT_FILL_COLOR, DEFAULT_OUTLINE_COLOR)
		, ellipse(Vec2f(), SSize(1.f, 2.f), DEFAULT_FILL_COLOR, DEFAULT_OUTLINE_COLOR)
	{

	}
};
BOOST_FIXTURE_TEST_SUITE(Ellipse, Ellipse_)
	BOOST_AUTO_TEST_CASE(Check_point_intersection_for_circle)
	{
		BOOST_CHECK(circle.IsPointIntersection(Vec2f(0.f, 0.f)));
		BOOST_CHECK(circle.IsPointIntersection(Vec2f(0.5f, 0.f)));
		BOOST_CHECK(circle.IsPointIntersection(Vec2f(0.f, 0.5f)));

		BOOST_CHECK(!circle.IsPointIntersection(Vec2f(0.5f, 0.5f)));
		BOOST_CHECK(!circle.IsPointIntersection(Vec2f(-0.5f, 0.5f)));
		BOOST_CHECK(!circle.IsPointIntersection(Vec2f(-0.5f, -0.5f)));
		BOOST_CHECK(!circle.IsPointIntersection(Vec2f(0.5f, -0.5f)));
	}
	BOOST_AUTO_TEST_CASE(Check_point_intersection_for_ellipse)
	{
		BOOST_CHECK(ellipse.IsPointIntersection(Vec2f(0.f, 0.f)));
		BOOST_CHECK(ellipse.IsPointIntersection(Vec2f(0.5f, 0.f)));
		BOOST_CHECK(ellipse.IsPointIntersection(Vec2f(0.f, 1.0f)));

		BOOST_CHECK(!ellipse.IsPointIntersection(Vec2f(0.5f, 1.0f)));
		BOOST_CHECK(!ellipse.IsPointIntersection(Vec2f(-0.5f, 1.0f)));
		BOOST_CHECK(!ellipse.IsPointIntersection(Vec2f(-0.5f, -1.0f)));
		BOOST_CHECK(!ellipse.IsPointIntersection(Vec2f(0.5f, -1.0f)));
	}
BOOST_AUTO_TEST_SUITE_END()// Ellipse_

BOOST_AUTO_TEST_SUITE_END()// CShape_suite
