#pragma once
#include <memory>
#include <Point2D.h>
#include <Console.h>
#include <Shape.h>
#include <Line.h>
#include <Rectangle.h>
#include <Triangle.h>
#include <Circle.h>

class ShapeFactory
{
public:
	static Point2D RandomPoint();

	static ConsoleColor RandomColor();

	static std::unique_ptr<Shape> RandomShape();

	static std::unique_ptr<Line> RandomLine();

	static std::unique_ptr<Rectangle> RandomRectangle();

	static std::unique_ptr<Triangle> RandomTriangle();

	static std::unique_ptr<Circle> RandomCircle();
};