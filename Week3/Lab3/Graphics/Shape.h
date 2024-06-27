#pragma once
#include "Point2D.h"
#include <Console.h>

class Shape
{
private:
	// Fields
	Point2D startPt;
	ConsoleColor color;
public:
	// Getters
	Point2D GetStartPt() const{
		return startPt;
	}

	ConsoleColor GetColor() const{
		return color;
	}

	// Setters
	void SetStartPt(Point2D startPt){
		this->startPt = startPt;
	}

	void SetColor(ConsoleColor color){
		this->color = color;
	}

	// Constructors
	Shape(Point2D startingPoint, ConsoleColor color) : startPt(startingPoint), color(color){

	}

	Shape(int x, int y, ConsoleColor color) : startPt(x, y), color(color){
	
	}

	virtual void Draw();
};