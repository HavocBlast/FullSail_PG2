#include "Triangle.h"

void Triangle::Draw()
{
	for(Line& line : lines){
		line.Draw();
	}
}
