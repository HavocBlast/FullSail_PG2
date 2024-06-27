#include "Line.h"

void Line::Plot(int x, int y)
{
	Console::SetCursorPosition(x, y);
	Console::Write(" ");
}
void Line::Draw()
{
	Console::SetBackgroundColor(Line::GetColor());
	PlotLine(GetStartPt().x, GetStartPt().y, endPt.x, endPt.y);
	Console::Reset();
}

void Line::PlotLine(int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0);
	int sy = y0 < y1 ? 1 : -1;
	int error = dx + dy;

	while(true){
		Plot(x0, y0);
		if(x0 == x1 && y0 == y1){
			break;
		}
		int e2 = 2 * error;
		if(e2 >= dy){
			if(x0 == x1){
				break;
			}
			error = error + dy;
			x0 = x0 + sx;
		}
		if(e2 <= dx){
			if(y0 == y1){
				break;
			}
			error = error + dx;
			y0 = y0 + sy;
		}
	}
}