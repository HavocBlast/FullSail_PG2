#include "WarGame.h"
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Input.h"


std::vector<Card> WarGame::_cards;
std::vector<std::string> suits;
std::vector<std::string> faces;

WarGame::WarGame(std::string cardsFile)
{
    LoadCards("cards.csv");
}

void WarGame::shuffle()
{
    int ndx1, ndx2;
    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < 52; i++)
    {
        ndx1 = rand() % 52;
        ndx2 = rand() % 52;

        Card temp = _cards[ndx1];
        _cards[ndx1] = _cards[ndx2];
        _cards[ndx2] = temp;
    }
}

std::vector<std::string> ParseData(std::string inputString, std::vector<std::string> container){

    std::stringstream strStream(inputString);
    std::string placeholder;
    while(std::getline(strStream, placeholder, '?')){
        container.push_back(placeholder);
    }
    return container;
}

void WarGame::LoadCards(std::string filePath)
{
    // Open/Read the cards.csv file
    std::ifstream inputFile(filePath);
    std::string suitsLine;
    std::string facesLine;
    // Split the data to get the suits and faces 
    std::getline(inputFile, suitsLine);     // First line
    suits = ParseData(suitsLine, suits);
    std::getline(inputFile, facesLine);     // Second line
    faces = ParseData(facesLine, faces);

    inputFile.close();

    // Create 52 unique cards
    for(std::string suit : suits){
        for(std::string face : faces){
               // Store each card in the _cards vector of the class
            _cards.push_back(Card(suit, face));
        }
    }
}

void WarGame::ShowCards(){
    for(auto card : _cards){
        //TODO: Format output to match assignment Part A-2 requirements
        card.Print();
        std::cout << "\n";
    }
}

void WarGame::PlayGame(std::string name, std::vector<HighScore>& scores, std::string fileName)
{
    shuffle();
    Player npc;
    Player player;

    npc.SetName("NPC");
    player.SetName(name);
    
    // Dealing cards to player and NPC
    for(int i = 0; i < _cards.size(); i ++){
        if(i % 2){
            player.PushCard(_cards[i]);
        }
        else{
            npc.PushCard(_cards[i]);
        }
    }

    std::vector<Card> unclaimedPile;

    // Gameplay loop
    while(player.HasCards()){
        Card playerCard = player.PopCard();
        Card npcCard = npc.PopCard();

        unclaimedPile.push_back(playerCard);
        unclaimedPile.push_back(npcCard);
        int compResult = playerCard.Compare(npcCard);

        // Prints results of round
        playerCard.Print();
        Console::Write(" vs. ");
        npcCard.Print();
        
        // Calculates Who won game
        if(compResult == -1){                       // NPC Wins!
            npc.WonCards(unclaimedPile);
            unclaimedPile.clear();
            Console::Write(" NPC Win\n");
        }
        else if(compResult == 1){                   // Player Wins
            player.WonCards(unclaimedPile);
            unclaimedPile.clear();
            Console::Write(" " + player.GetName() + " Win\n");
        }
        else{                                       // Tied
	        Console::Write(" Draw! \n");
        }
    }

    if(npc.GetScore() > player.GetScore())
    {
	    Console::WriteLine("NPC Wins! " + std::to_string(npc.GetScore()) + " to " + std::to_string(player.GetScore()));
    }
    else if(npc.GetScore() == player.GetScore())
    {
	    Console::WriteLine("It was a Tie!!");
    }
    else{
	    Console::WriteLine(player.GetName() + " Wins! " + std::to_string(player.GetScore()) + " to " + std::to_string(npc.GetScore()));
        if(player.GetScore() > scores.back().GetScore())
        {
            for(int i = 0; i < scores.size(); i++)
            {
	            if(player.GetScore() > scores[i].GetScore())
	            {
                    Console::WriteLine("++++NEW HIGH SCORE++++");
                    HighScore newHS(player.GetName(), player.GetScore());
		            scores.insert(scores.begin() + i, newHS);
                    scores.pop_back();
                    HighScore::SaveHighScores("HighScores.csv", scores);
                    HighScore::ShowHighScores(scores);
                    break;
	            }
            }
        }
    }

    if(Input::GetInteger("Do you want to play again? (1: Yes, 2: No).",1,2) == 1)
    {
	    PlayGame(name, scores, fileName);
    }
}
