#include <iostream>
#include "Console.h"
#include "Input.h"
#include "WarGame.h"
#include "Tester.h"
#include <HighScore.h>

int main()
{
    Tester cardWarsTest;
    Console::ResizeWindow(150, 30);

    int menuSelection = 0;
    std::vector<std::string> menuOptions{ "1. Show Cards", "2. Show High Scores", "3. Play Card Wars", "4. Exit" };
    std::string highScoreFile = "HighScores.csv";
    std::string cardsFile = "cards.csv";

    WarGame war(cardsFile);

    std::vector<HighScore> scores = HighScore::LoadHighScores("HighScores.csv");

    do
    {
        Console::Clear();
        menuSelection = Input::GetMenuSelection(menuOptions);
        Console::Clear();


        //----------------------------------------------------------------
        //                                                              //
        //    Call your methods in the appropriate case statement       //
        //                                                              //
        switch (menuSelection)
        {
        case 1:
        {
            WarGame::ShowCards();
            break;
        }
        case 2:
        {
            HighScore::ShowHighScores(scores);
            break;
        }
        case 3:
        {
            std::string playerName = Input::GetString("Enter your name: ");        
            war.PlayGame(playerName, scores, highScoreFile);
            break;
        }
        default:
            break;
        }

        Input::PressEnter();

    } while (menuSelection != menuOptions.size());

}