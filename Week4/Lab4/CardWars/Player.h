#pragma once
#include <string>
#include <vector>
#include <Card.h>

class Player{

private:
	std::string name;
	int score;
	std::vector<Card> pile;
	std::vector<Card> won;

public:

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

	bool HasCards();
	void PushCard(Card card);
	Card PopCard();
	void WonCards(std::vector<Card> cards);
};