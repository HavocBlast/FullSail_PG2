#include <iostream>
#include "HeroesDB.h"
#include "Console.h"
#include "Input.h"
#include <locale>
#include "Tester.h"

int main()
{
    Tester v2Test;
    Console::ResizeWindow(150, 30);

    HeroesDB heroDB;

    int menuSelection = 0;
    std::vector<std::string> menuOptions{ "1. Sort by Name (descending)", "2. Sort By", "3. Find Hero (Binary Search)", "4. Print Group Counts", "5. Find All Heroes by first letter", "6. Remove Hero", "7. Exit" };
    std::vector<std::string> sortByOptions { "1. Intelligence", "2. Strength", "3. Speed", "4. Durability", "5. Power", "6. Combat" };

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
            heroDB.SortByNameDescending();
            break;
        }
        case 2:
        {
            int sortBySelection = Input::GetMenuSelection(sortByOptions, "Sort by? ");
            SortBy sortByChoice = (SortBy)sortBySelection;
            heroDB.SortByAttribute(sortByChoice);
            break;
        }
        case 3:
        {
            std::string searchTerm = Input::GetString("Please enter the name of the hero to find: ");
            heroDB.FindHero(searchTerm);
            break;
        }
        case 4:
        {
            heroDB.PrintGroupCounts();
            break;
        }
        case 5:
        {
            std::string input = Input::GetString("Please enter the first letter of the heroes to find: ");
            heroDB.FindHeroesByLetter(input[0]);
            break;
        }
        case 6:
        {
            std::string name = Input::GetString("Please enter the name of the hero to remove: ");
            heroDB.RemoveHero(name);
            break;
        }
        default:
            break;
        }

        Input::PressEnter();

    } while (menuSelection != menuOptions.size());
}