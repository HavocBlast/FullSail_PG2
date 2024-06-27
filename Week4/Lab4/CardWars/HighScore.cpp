#include "HighScore.h"


void HighScore::Deserialize(std::string cvsData, char delimiter)
{
    std::string outStr;
	std::stringstream sString(cvsData);
	std::getline(sString, name, delimiter);
	std::getline(sString, outStr, delimiter); 
	score = std::stoi(outStr);
}

std::vector<HighScore> HighScore::LoadHighScores(std::string filePath)
{
	std::vector<HighScore> scores;
	// Open stream
    std::ifstream inputFile(filePath);
	std::string line;
	// Get data from csv
	while (!inputFile.eof())
	{
		std::getline(inputFile, line);
		std::string highScoreCSV;
		std::stringstream hsPart(line);
		while(std::getline(hsPart, highScoreCSV, '\n')){
			HighScore currentHighScore(highScoreCSV, '[');
			scores.push_back(currentHighScore);
		}
		line = "";
	}
	// Close stream
    inputFile.close();
	return scores;
}

void HighScore::ShowHighScores(const std::vector<HighScore>& scores)
{
	std::cout << "----HIGH SCORE----\n";
	for(HighScore score : scores){
		Console::Write(score.GetName());
		Console::SetCursorLeft(17);
		Console::Write(std::to_string(score.GetScore()) + "\n", Yellow);
	}
}

void HighScore::Serialize(std::ofstream& outFile, char delimiter) const
{
	outFile << name << delimiter << score;
}

void HighScore::SaveHighScores(std::string filePath, const std::vector<HighScore>& scores)
{
	std::ofstream outputFile(filePath);

	if(outputFile.is_open()){
		bool isFirst = true;
		for(auto& score : scores){	
			if(!isFirst)
				outputFile << "\n";
			score.Serialize(outputFile, '[');
			isFirst = false;
		}
	}
	else{
		std::cout << "path does not exist\n";
	}
	outputFile.close();
}
