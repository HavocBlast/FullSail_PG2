#pragma once
#include "Shape.h"
#include "Line.h"
#include <vector>

class Triangle : public Shape
{
private:
	Point2D p2;
	Point2D p3;
	std::vector<Line> lines;

public:
	Point2D GetP2(){
		return p2;
	}

	void SetP2(Point2D p2){
		this->p2 = p2;
	}

	Point2D GetP3(){
		return p3;
	}

	void SetP3(Point2D p3){
		this->p3 = p3;
	}

	Triangle(Point2D p1, Point2D p2, Point2D p3, ConsoleColor color) : Shape(p1, color){
		this->p2 = p2;
		this->p3 = p3;

		lines.push_back(Line(p1, p2, color)); // P1 to P2
		lines.push_back(Line(p2, p3, color)); // P2 to P3
		lines.push_back(Line(p3, p1 , color)); // P3 to P1
	}

	void Draw() override;
};