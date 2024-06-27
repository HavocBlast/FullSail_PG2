#include <iostream>
#include "Console.h"
#include "Input.h"
#include <algorithm>
#include <memory>
#include "Tester.h"
#include "Shape.h"
#include "Line.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"
#include "ShapeFactory.h"


int main()
{
	Tester graphicsTest;
	srand((unsigned int)time(NULL)); //seed the random # generator

	Console::ResizeWindow(150, 30);

	int menuSelection = 0;
	std::vector<std::string> menuOptions{ "1. Draw Shape", "2. Draw Line", "3. Draw Rectangle", "4. Draw Triangle",  "5. Draw Circle", "6. Draw Random Shapes", "7. Exit" };

	do
	{
		Console::Clear();
		menuSelection = Input::GetMenuSelection(menuOptions);
		Console::Clear();


		//----------------------------------------------------------------
		//                                                              //
		//    Call your methods in the appropriate case statement       //
		//                                                              //
		switch (menuSelection)
		{
		case 1:
		{
			Shape shape = Shape(
				rand() % (Console::GetWindowWidth() + 1), 
				rand() % (Console::GetWindowHeight() + 1), 
				Yellow);
			shape.Draw();
			break;
		}
		case 2:
		{
			// Generate two random points w/ x & y in console
			Point2D startPt = Point2D(rand() % (Console::GetWindowWidth()), rand() % (Console::GetWindowHeight()));
			Point2D endPt = Point2D(rand() % (Console::GetWindowWidth()), rand() % (Console::GetWindowHeight()));
			// Create a line instance with those point and a color
			Line line = Line(startPt, endPt, Red);
			line.Draw();
			break;
		}
		case 3:
		{
			Point2D startPt = Point2D(rand() % (Console::GetWindowWidth()), rand() % (Console::GetWindowHeight()));
			int width = rand() % (Console::GetWindowWidth() - startPt.x);
			int height = rand() % (Console::GetWindowHeight() - startPt.y);

			Rectangle rectangle = Rectangle(width, height, startPt, Cyan);
			rectangle.Draw();
			break;
		}
		case 4:
		{
			Point2D p1 = Point2D(rand() % (Console::GetWindowWidth()), rand() % (Console::GetWindowHeight()));
			Point2D p2 = Point2D(rand() % (Console::GetWindowWidth()), rand() % (Console::GetWindowHeight()));
			Point2D p3 = Point2D(rand() % (Console::GetWindowWidth()), rand() % (Console::GetWindowHeight()));
			
			Triangle triangle = Triangle(p1, p2, p3, Yellow);
			triangle.Draw();
			break;
		}
		case 5:
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

			Circle circle = Circle(radius, centerPt, Red);
			circle.Draw();
			break;
		}
		case 6:
		{	
			// Create a vector that holds unique_ptr of Shapes
			std::vector<std::unique_ptr<Shape>> shapes;
			// Create 100 random Shapes and add them to the vector
				// Randomly pick which type of Shapes (Shape, Line, Rectangle, Triangle, Circle)
				// Create the instance according to its Shape. Call the appropriate method of the ShapeFactory
			for(int i = 0; i < 101; i++){
				int choice = rand() % 5;
				std::unique_ptr<Shape> pShape = ShapeFactory::RandomShape();
				std::unique_ptr<Line> pLine = ShapeFactory::RandomLine();
				std::unique_ptr<Triangle> pTriangle = ShapeFactory::RandomTriangle();
				std::unique_ptr<Rectangle> pRectangle = ShapeFactory::RandomRectangle();
				std::unique_ptr<Circle> pCircle = ShapeFactory::RandomCircle();

				switch (choice)
				{
				case 0:
					shapes.push_back(std::make_unique<Shape>(pShape->GetStartPt(), pShape->GetColor()));
					break;
				case 1:
					shapes.push_back(std::make_unique<Line>(pLine->GetStartPt(), pLine->GetStartPt(), pLine->GetColor()));
					break;
				case 2:
					shapes.push_back(std::make_unique<Triangle>(pTriangle->GetStartPt(), pTriangle->GetP2(), pTriangle->GetP3(), pTriangle->GetColor()));
					break;
				case 3:
					shapes.push_back(std::make_unique<Rectangle>(pRectangle->GetWidth(), pRectangle->GetHeight(), pRectangle->GetStartPt(), pRectangle->GetColor()));
					break;
				case 4:
					shapes.push_back(std::make_unique<Circle>(pCircle->GetRadius(), pCircle->GetStartPt(), pCircle->GetColor()));
					break;
				default:
					break;
				}
			}
			// After this loop, loop over the Shapes vector and call Draw on each Shape
			for(std::unique_ptr<Shape> &shape : shapes){
				shape->Draw();
			}
			break;
		}
		default:
			break;
		}

		Input::PressEnter(true);

	} while (menuSelection != menuOptions.size());
}