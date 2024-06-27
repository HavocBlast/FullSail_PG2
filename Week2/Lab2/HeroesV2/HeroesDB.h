#pragma once

#include <iostream>
#include <string>
#include <map>
#include "Hero.h"
#include "enums.h"
#include <map>

class HeroesDB : public JSONBase
{
public:
    HeroesDB();
	virtual ~HeroesDB() {};
    size_t Count() { return _heroes.size(); }

    void SortByNameDescending();

    //----------------------------------------------------------------
    //                                                              //
    //		       ADD YOUR METHOD DECLARATIONS HERE                //
    //                                                              //

    std::vector<Hero> Merge(std::vector<Hero> left, std::vector<Hero> right, SortBy selectedAttribute);
    std::vector<Hero> MergeSort(std::vector<Hero> heroes, SortBy selectedAttribute);
    void SortByAttribute(SortBy selectedAttribute);
    int BinarySearch(std::vector<Hero> hero, std::string searchTerm, int low, int high);
    void FindHero(std::string heroName);
    void GroupHeroes();
    void PrintGroupCounts();
    void FindHeroesByLetter(char letter);
    void RemoveHero(std::string name);

private:
    std::vector<Hero> _heroes;
    std::map<char, std::vector<Hero>> _groupedHeroes;

    static std::string toUpper(const std::string& str);
    static std::string toUpper2(const std::string& str);
    static bool charComparer(char c1, char c2);
    static bool isPrefix(const std::string& prefix, const std::string& word);

    virtual bool Deserialize(const std::string& s);
    virtual bool Deserialize(const rapidjson::Value& obj) { return false; };
    virtual bool Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const;
};
