#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Console.h"

class HighScore
{
private:
	std::string name;
	int score;

public:

	HighScore(std::string name, int score){
		this->name = name;
		this->score = score;
	}

	HighScore(std::string cvsData, char delimiter){
		Deserialize(cvsData, delimiter);
	}

	std::string GetName(){
		return name;
	}

	void SetName(std::string name){
		this->name = name;
	}

	int GetScore(){
		return score;
	}

	void SetScore(int score){
		this->score = score;
	}

	void Deserialize(std::string cvsData, char delimiter);
	static std::vector<HighScore> LoadHighScores(std::string filePath);
	static void ShowHighScores(const std::vector<HighScore>& scores);
	void Serialize(std::ofstream& outFile, char delimiter) const;
	static void SaveHighScores(std::string filePath, const std::vector<HighScore>& scores);
};

