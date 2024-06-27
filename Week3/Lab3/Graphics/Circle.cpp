#include "Circle.h"


void Circle::DrawCirclePoints(int xc, int yc, int x, int y)
{
    Plot(xc+x, yc+y);
    Plot(xc-x, yc+y);
    Plot(xc+x, yc-y);
    Plot(xc-x, yc-y);
    Plot(xc+y, yc+x);
    Plot(xc-y, yc+x);
    Plot(xc+y, yc-x);
    Plot(xc-y, yc-x);
}

void Circle::DrawCircle(int xc, int yc, int r)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;

    DrawCirclePoints(xc, yc, x, y);
    while(y >= x){
        x += 1;
        if( d > 0){
            y -= 1;
            d += 4 * (x - y) + 10;
        }
        else{
            d += 4 * x + 6;
        }
        DrawCirclePoints(xc, yc, x, y);
    }
}

void Circle::Plot(int x, int y){
	Console::SetCursorPosition(x , y);
	Console::Write(" ");
}

void Circle::Draw(){
    Console::SetBackgroundColor(GetColor());
    DrawCircle(GetStartPt().x, GetStartPt().y, radius);
    Console::Reset();
}