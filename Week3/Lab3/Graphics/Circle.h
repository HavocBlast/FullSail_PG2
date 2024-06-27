#pragma once
#include "Shape.h"

class Circle : public Shape
{
private:
	int radius;

public:
	int GetRadius(){
		return radius;
	}

	void SetRadius(int radius){
		this->radius = radius;
	}

	Circle(int radius, Point2D startPt, ConsoleColor color) : Shape(startPt, color){
		this->radius = radius;
	}

	void DrawCirclePoints(int xc, int yc, int x,int y);
	void DrawCircle(int xc, int yc, int r);
	void Plot(int x, int y);
	void Draw() override;
};