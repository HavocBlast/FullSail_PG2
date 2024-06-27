#pragma once
#include "Shape.h"
class Line : public Shape{
private:
	Point2D endPt;

public:
	// Getter/Setters
	Point2D GetEndPt(){
		return endPt;
	}

	void SetEndPt(Point2D endPt){
		this->endPt = endPt;
	}

	Line(Point2D start, Point2D end, ConsoleColor color) : Shape(start, color){
		endPt = end;
	}

	void PlotLine(int x0, int y0, int x1, int y1);

	void Plot(int x, int y);

	void Draw() override;
};