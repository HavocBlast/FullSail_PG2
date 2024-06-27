#pragma once

struct Point2D{

public:
	int x;
	int y;

	Point2D(){
		x = 0;
		y = 0;
	}

	Point2D(int x, int y){
		this->x = x;
		this->y = y;
	}
};