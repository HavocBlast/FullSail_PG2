#pragma once
#include <string>
#include <vector>
#include "Card.h"
#include "Player.h"
#include "HighScore.h"

class WarGame
{

public:
	WarGame(std::string cardsFile);
	static void LoadCards(std::string cards);
	static void ShowCards();
	void PlayGame(std::string name, std::vector<HighScore>& scores, std::string fileName);
private:
	static std::vector<Card> _cards;

	static void shuffle();
};

