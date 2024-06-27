#include "ShapeFactory.h"

Point2D ShapeFactory::RandomPoint()
{
	return Point2D(rand() % (Console::GetWindowWidth()), rand() % (Console::GetWindowHeight()));
}

ConsoleColor ShapeFactory::RandomColor()
{
	return ConsoleColor(rand() % 9);
}

std::unique_ptr<Shape> ShapeFactory::RandomShape()
{
	std::unique_ptr<Shape> pShape = std::make_unique<Shape>(
		RandomPoint(),
		RandomColor()
	);
	return pShape;
}

std::unique_ptr<Line> ShapeFactory::RandomLine()
{
	std::unique_ptr<Line> pLine = std::make_unique<Line>(
		RandomPoint(),
		RandomPoint(),
		RandomColor()
	);
	return pLine;
}

std::unique_ptr<Rectangle> ShapeFactory::RandomRectangle()
{
	int width = rand() % (Console::GetWindowWidth());
	int height = rand() % (Console::GetWindowHeight());

	std::unique_ptr<Rectangle> pRectangle = std::make_unique<Rectangle>(
		width,
		height,
		RandomPoint(),
		RandomColor()
	);
	return pRectangle;
}

std::unique_ptr<Triangle> ShapeFactory::RandomTriangle()
{
	std::unique_ptr<Triangle> pTriangle = std::make_unique<Triangle>(
		RandomPoint(),
		RandomPoint(),
		RandomPoint(),
		RandomColor()
	);
	return pTriangle;
}

std::unique_ptr<Circle> ShapeFactory::RandomCircle()
{
	int radius;
			// Check to make sure that centerPt +- radius </> windowSize
			
			radius = rand() % ((Console::GetWindowHeight()) / 2);
			Point2D centerPt = Point2D(rand() % (Console::GetWindowWidth() - radius), rand() % (Console::GetWindowHeight()) - radius);

			if(centerPt.y < radius){
				centerPt.y = radius + 1;
			}
			if(centerPt.x < radius){
				centerPt.x = radius + 1;
			}
			if(centerPt.y > Console::GetWindowHeight() - radius){
				centerPt.y = Console::GetWindowHeight() - radius - 1;
			}
			if(centerPt.x > Console::GetWindowWidth() - radius){
				centerPt.x = Console::GetWindowWidth() - radius - 1;
			}
	std::unique_ptr<Circle> pCircle = std::make_unique<Circle>(

		radius,
		RandomPoint(),
		RandomColor()
	);
	return pCircle;

}

