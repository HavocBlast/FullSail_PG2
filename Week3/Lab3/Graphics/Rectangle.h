#pragma once
#include "Shape.h"
#include "Line.h"
#include <vector>

class Rectangle : public Shape{
private:
	int width;
	int height;
	std::vector<Line> lines;

public:
	int GetWidth(){
		return width;
	}
	void SetWidth(int width){
		this->width = width;
	}

	int GetHeight(){
		return height;
	}

	void SetHeight(int height){
		this->height = height;
	}

	Rectangle(int width, int height, Point2D startPt, ConsoleColor color) : Shape(startPt, color){
		this->width = width;
		this->height = height;

		lines.push_back(Line(startPt, Point2D(startPt.x + width, startPt.y), color)); // P1 Top left to top right
		lines.push_back(Line(Point2D(startPt.x + width, startPt.y), Point2D(startPt.x + width, startPt.y + height), color)); //P2 Top right to bottom right
		lines.push_back(Line(Point2D(startPt.x, startPt.y + height), Point2D(startPt.x + width, startPt.y + height), color));// P3 Bottom left to bottom right
		lines.push_back(Line(startPt, Point2D(startPt.x, startPt.y + height), color));// P4 Top left to bottom left

	}
	void Draw() override;
};