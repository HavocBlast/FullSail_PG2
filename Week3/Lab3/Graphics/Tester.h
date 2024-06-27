#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "ResultsLib.h"
#include <filesystem>
namespace fs = std::filesystem;

class Tester
{
public:
	const char* file;
	Tester() : file("Graphics.results")
	{
		std::vector<const char*> codeFiles;
		std::vector<std::string> fileNames;
		GetFiles(fileNames);// { "Graphics.cpp" };
		for (auto& file : fileNames)
		{
			codeFiles.push_back(file.c_str());
			//std::cout << file << "\n";
		}
		results::WriteResults(codeFiles, file);
	}

	void GetFiles(std::vector<std::string>& codeFiles)
	{
		std::string path = fs::current_path().string();

		std::string cpp(".cpp");
		std::string h(".h");
		std::string proj(".vcxproj");
		for (auto& p : fs::recursive_directory_iterator(path))
		{
			if (p.path().extension() == cpp || p.path().extension() == h || p.path().extension() == proj)
			{
				codeFiles.push_back(p.path().filename().string());
			}
		}
	}

	void ShowResults()
	{
		results::ReadResults(file, std::chrono::seconds(900));
	}
};

