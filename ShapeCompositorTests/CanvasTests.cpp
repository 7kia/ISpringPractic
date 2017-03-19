#include "stdafx.h"
#include "Canvas/Canvas.h"

BOOST_AUTO_TEST_SUITE(CCanvas_suite)


struct CanvasFixture
{
	CCanvas emptyCanvas;
	CCanvas fullCanvas;
	CShapeFactory factory;

	CShapePtr ellipse;
	CShapePtr rectangle;
	CShapePtr triangle;

	CanvasFixture()
		: ellipse(factory.CreateShape(SShapeData(ShapeType::Ellipse)))
		, rectangle(factory.CreateShape(SShapeData(ShapeType::Rectangle)))
		, triangle(factory.CreateShape(SShapeData(ShapeType::Triangle)))
	{
		fullCanvas.PushBackShape(ellipse);
		fullCanvas.PushBackShape(triangle);
		fullCanvas.PushBackShape(rectangle);
	}
};
BOOST_FIXTURE_TEST_SUITE(Canvas, CanvasFixture)

	BOOST_AUTO_TEST_CASE(Can_check_size)
	{
		BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 0);
		emptyCanvas.PushBackShape(rectangle);

		BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 1);
		emptyCanvas.PushBackShape(ellipse);

		BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 2);
		emptyCanvas.PushBackShape(triangle);
	}

	BOOST_AUTO_TEST_SUITE(Add)
		BOOST_AUTO_TEST_CASE(Can_push_back_shape)
		{
			BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 0);
			emptyCanvas.PushBackShape(rectangle);

			BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 1);
			emptyCanvas.PushBackShape(ellipse);

			BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 2);
			emptyCanvas.PushBackShape(triangle);

			BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 3);
			BOOST_CHECK_EQUAL(emptyCanvas.GetShape(0), rectangle);
			BOOST_CHECK_EQUAL(emptyCanvas.GetShape(1), ellipse);
			BOOST_CHECK_EQUAL(emptyCanvas.GetShape(2), triangle);
		}
		BOOST_AUTO_TEST_CASE(Can_insert_shape)
		{
			BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 3);

			fullCanvas.InsertShape(1, rectangle);

			BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 4);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(0), ellipse);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(1), rectangle);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(2), triangle);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(3), rectangle);
		}
		BOOST_AUTO_TEST_CASE(Check_index_for_InsertShape)
		{
			BOOST_CHECK_THROW(emptyCanvas.InsertShape(1, rectangle), std::runtime_error);

			emptyCanvas.PushBackShape(triangle);
			emptyCanvas.PushBackShape(triangle);

			BOOST_CHECK_THROW(emptyCanvas.InsertShape(5, rectangle), std::runtime_error);
		}
	BOOST_AUTO_TEST_SUITE_END()// Add

	BOOST_AUTO_TEST_SUITE(Delete)
		BOOST_AUTO_TEST_CASE(Can_delete_shape_by_pointer)
		{
			fullCanvas.DeleteShape(triangle);
			BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 2);

			BOOST_CHECK_EQUAL(fullCanvas.GetShape(0), ellipse);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(1), rectangle);
		}
		BOOST_AUTO_TEST_CASE(Can_delete_shape_by_index)
		{
			fullCanvas.DeleteShape(0);
			BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 2);

			BOOST_CHECK_EQUAL(fullCanvas.GetShape(0), triangle);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(1), rectangle);

			fullCanvas.DeleteShape(1);
			BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 1);

			BOOST_CHECK_EQUAL(fullCanvas.GetShape(0), triangle);
		}
		BOOST_AUTO_TEST_CASE(Check_index_for_DeleteShape_with_index_argument)
		{
			BOOST_CHECK_THROW(fullCanvas.DeleteShape(3), std::runtime_error);

			BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 3);

			BOOST_CHECK_EQUAL(fullCanvas.GetShape(0), ellipse);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(1), triangle);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(2), rectangle);
		}
		BOOST_AUTO_TEST_CASE(Can_delete_last_shape)
		{
			emptyCanvas.PushBackShape(ellipse);
			emptyCanvas.PushBackShape(triangle);

			emptyCanvas.DeleteLastShape();
			BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 1);

			BOOST_CHECK_EQUAL(emptyCanvas.GetShape(0), ellipse);

			emptyCanvas.DeleteLastShape();
			BOOST_CHECK_EQUAL(emptyCanvas.GetAmountShapes(), 0);
		}
		BOOST_AUTO_TEST_CASE(if_canvas_is_empty_DeleteLastShape_throw_exception)
		{
			BOOST_CHECK_THROW(emptyCanvas.DeleteLastShape(), std::runtime_error);
		}
		BOOST_AUTO_TEST_CASE(Can_clear_canvas)
		{
			BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 3);

			fullCanvas.Clear();

			BOOST_CHECK_EQUAL(fullCanvas.GetAmountShapes(), 0);
		}

	BOOST_AUTO_TEST_SUITE_END()// Delete


	BOOST_AUTO_TEST_SUITE(GetShape)
		BOOST_AUTO_TEST_CASE(GetShape_by_index)
		{
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(0), ellipse);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(1), triangle);
			BOOST_CHECK_EQUAL(fullCanvas.GetShape(2), rectangle);
		}
		
		struct GetShapeByMousePositionFixture
		{
			const Vec2f firstPos = Vec2f(0.5f, 0.5f);
			const Vec2f secondPos = Vec2f(1.5f, 0.5f);
			const Vec2f thirdPos = Vec2f(0.5f, 1.25f);
			const SSize size = SSize(1.f, 1.f);

			CShapeFactory factory;
			CCanvas canvas;

			CShapePtr ellipse;
			CShapePtr rectangle;
			CShapePtr triangle;


			GetShapeByMousePositionFixture()
				: ellipse(factory.CreateShape(SShapeData(ShapeType::Ellipse, firstPos, size)))
				, triangle(factory.CreateShape(SShapeData(ShapeType::Triangle, secondPos, size)))
				, rectangle(factory.CreateShape(SShapeData(ShapeType::Rectangle, thirdPos, size)))
			{
				canvas.PushBackShape(ellipse);
				canvas.PushBackShape(triangle);
				canvas.PushBackShape(rectangle);
			}
		};
		BOOST_FIXTURE_TEST_SUITE(GetShapeByMousePosition, GetShapeByMousePositionFixture)
			BOOST_AUTO_TEST_CASE(Check_centers)
			{
				BOOST_CHECK_EQUAL(canvas.GetShape(firstPos), ellipse);
				BOOST_CHECK_EQUAL(canvas.GetShape(secondPos), triangle);
				BOOST_CHECK_EQUAL(canvas.GetShape(thirdPos), rectangle);
			}
			BOOST_AUTO_TEST_CASE(Check_other_point)
			{
				BOOST_CHECK_EQUAL(canvas.GetShape(firstPos + Vec2f(-0.25f, 0.f)), ellipse);
				BOOST_CHECK_EQUAL(canvas.GetShape(secondPos + Vec2f(-0.25f, 0.f)), triangle);
				BOOST_CHECK_EQUAL(canvas.GetShape(thirdPos + Vec2f(0.25f, 0.f)), rectangle);
			}
			BOOST_AUTO_TEST_CASE(Check_overlap)
			{
				BOOST_CHECK_EQUAL(canvas.GetShape(firstPos + Vec2f(0.f, 0.22f)), ellipse);
				BOOST_CHECK_EQUAL(canvas.GetShape(firstPos + Vec2f(0.f, 0.25f)), rectangle);
				BOOST_CHECK_EQUAL(canvas.GetShape(firstPos + Vec2f(0.f, 0.28f)), rectangle);
				BOOST_CHECK_EQUAL(canvas.GetShape(thirdPos + Vec2f(0.0f, 0.35f)), rectangle);
			}
		BOOST_AUTO_TEST_SUITE_END()// GetShapeByMousePositionFixture

	BOOST_AUTO_TEST_SUITE_END()// GetShape

	BOOST_AUTO_TEST_CASE(GetShapeIndex)
	{
		BOOST_CHECK_EQUAL(fullCanvas.GetShapeIndex(ellipse), 0);
		BOOST_CHECK_EQUAL(fullCanvas.GetShapeIndex(triangle), 1);
		BOOST_CHECK_EQUAL(fullCanvas.GetShapeIndex(rectangle), 2);
	}
	BOOST_AUTO_TEST_CASE(GetShapes)
	{
		auto shapes = fullCanvas.GetShapes();
		
		BOOST_CHECK_EQUAL(shapes[0], ellipse);
		BOOST_CHECK_EQUAL(shapes[1], triangle);
		BOOST_CHECK_EQUAL(shapes[2], rectangle);
	}

BOOST_AUTO_TEST_SUITE_END()// CanvasFixture


BOOST_AUTO_TEST_SUITE_END()// Canvas_suite