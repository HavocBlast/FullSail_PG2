#include "Shape.h"

void Shape::Draw()
{
	Console::SetBackgroundColor(color);
	Console::SetCursorPosition(startPt.x, startPt.y);
	Console::Write(" ");
	Console::Reset();
}