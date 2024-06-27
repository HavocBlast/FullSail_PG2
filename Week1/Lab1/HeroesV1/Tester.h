#pragma once
#include <vector>
#include "ResultsLib.h"
class Tester
{
public:
	const char* file;
	Tester() : file("HeroesV1.log")
	{
		std::vector<std::string> codeFiles{ "HeroesDB.h", "HeroesDB.cpp", "HeroesV1.cpp" };
		results::Log(file, codeFiles);
	}
};

