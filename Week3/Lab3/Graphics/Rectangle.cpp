#include "Rectangle.h"

void Rectangle::Draw()
{
	for(Line& line : lines){
		line.Draw();
	}
}