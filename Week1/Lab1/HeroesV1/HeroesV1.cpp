#include <iostream>
#include "HeroesDB.h"
#include "Console.h"
#include "Input.h"
#include "Tester.h"


int main()
{
    Tester v1Test;
    /*
        NOTE: if you're having problems with the menu showing, it could be because you're using Windows Terminal.
        Go here to learn how to change Windows to use the Console window instead. 
        https://discord.com/channels/446669518593327105/1151952874012688384/1153398632763097212
    
    */
    Console::ResizeWindow(150, 30);

    HeroesDB heroDB;

    /*
        Here are some examples.
            - how to call methods
            - how to use the Console Write methods
            - how to access the data values of a Hero.
    */
    Hero theBest = heroDB.GetBestHero(); //how to call a non-static method
    Console::Write("The best hero is "); //how to call a static method

    //how to call the Write method and change the foreground color
    Console::Write(theBest.Name(), ConsoleColor::Yellow);

    Console::Write("! (of course).\nThe Id of the hero is ");
    Console::Write(std::to_string(theBest.Id()), ConsoleColor::Green);
    Console::Write(".\nHis combat level is ");

    //how to access the members of a Hero object
    //how to print a number using the Console::Write using the std::to_string method
    Console::Write(std::to_string(theBest.Powerstats().Combat), ConsoleColor::Red);
    Console::WriteLine("!");
    Input::PressEnter();


    int menuSelection = 0;
    std::vector<std::string> menuOptions { "1. Show Heroes", "2. Remove Hero", "3. Starts With", "4. Find Hero", "5. Remove All Heroes", "6. Show Top x", "7. Exit" };
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
            heroDB.ShowHeroes();
            break;
        }
        case 2:
        {
            std::string heroName = Input::GetString("Please enter the name of the hero to remove: ");
                if(heroDB.RemoveHero(heroName))
                {
	                Console::WriteLine(heroName + " was removed");
                }
                else
                {
	                Console::WriteLine(heroName + " was not found");
                }
            break;
        }
        case 3:
        {
            std::string prefix = Input::GetString("Please enter the start of the name to find: ");
            std::vector<Hero> herosFound = heroDB.StartsWith(prefix);
            Console::WriteLine("Found " + std::to_string(herosFound.size()) + " heros that start with " + prefix + ".");
            for(Hero hero : herosFound){
                Console::WriteLine(std::to_string(hero.Id()) + ": " + hero.Name());
            }
            break;
        }
        case 4:
        {
            std::string heroName = Input::GetString("Please enter the name of the hero to find: ");
            Hero foundHero;
            if(heroDB.FindHero(heroName, foundHero)){
                heroDB.PrintHero(foundHero);
            }
            else{
                Console::WriteLine("Hero " + heroName + " was not found!");
            }
            break;
        }
        case 5:
        {
            std::string heroName = Input::GetString("Please enter the first part of the name to remove: ");
            std::vector<Hero> heroesToRemove;
            heroDB.RemoveAllHeroes(heroName, heroesToRemove);
            if(heroesToRemove.size() == 0){
                Console::WriteLine("No heroes found that start with" + heroName + ".");
            }
            else{
                Console::WriteLine("The following heroes were removed: ");
                for(int i = 0; i < heroesToRemove.size(); i++){
                    heroDB.PrintHero(heroesToRemove[i]);
                }
            }
            break;
        }
        case 6:
        {
            int heroesToShow = Input::GetInteger("How many heroes to show: ", 0, heroDB.Count());
            heroDB.ShowHeroes(heroesToShow);
            break;
        }
        default:
            break;
        }

        Input::PressEnter();

    } while (menuSelection != menuOptions.size());
}


