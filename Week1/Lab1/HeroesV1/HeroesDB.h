#pragma once
#include <string>
#include "Hero.h"

#include <iostream>

class HeroesDB : public JSONBase
{
public:
    HeroesDB();
	virtual ~HeroesDB() {};
    size_t Count() { return _heroes.size(); }
    Hero GetBestHero(); //DECLARE the method in the header (.h) file

    //----------------------------------------------------------------
    //                                                              //
    //		       ADD YOUR METHOD DECLARATIONS HERE                //
    //                                                              //

    void ShowHeroes(int heroesToShow = 0);
    bool RemoveHero(std::string name);
    std::vector<Hero> StartsWith(std::string name);
    void PrintHero(Hero& heroRef);
    bool FindHero(std::string name, Hero& heroRef);
    void RemoveAllHeroes(std::string name, std::vector<Hero>& heroesFound);

private:
    std::vector<Hero> _heroes;

    static bool charComparer(char c1, char c2);
    static bool isPrefix(const std::string& prefix, const std::string& word);

    virtual bool Deserialize(const std::string& s);
    virtual bool Deserialize(const rapidjson::Value& obj) { return false; };
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};