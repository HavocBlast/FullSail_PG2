#include "HeroesDB.h"
#include <iostream>
#include "Console.h"
#include <algorithm> 
#include <locale>
#include <string>



//----------------------------------------------------------------
//                                                              //
//		        ADD YOUR METHOD DEFINITIONS HERE                //
//                                                              //

void HeroesDB::ShowHeroes(int heroesToShow)
{
	if(heroesToShow == 0){
		for (Hero hero : _heroes){
		Console::WriteLine(std::to_string(hero.Id()) + ": " + hero.Name());
		}
	}
	else{
		for(int i = 0; i < heroesToShow; i++){
			Console::WriteLine(std::to_string(_heroes[i].Id()) + ": " + _heroes[i].Name());
		}
	}
}

bool HeroesDB::RemoveHero(std::string name)
{
	bool heroRemoved = false;
	for (int i = 0; i < _heroes.size(); i++)
	{
		if(_stricmp(_heroes[i].Name().c_str(), name.c_str()) == 0)
		{
			_heroes.erase(_heroes.begin() + i);
			heroRemoved = true;
			break;
		}
		else
		{
			heroRemoved = false;
		}
	}
	return heroRemoved;
}

std::vector<Hero> HeroesDB::StartsWith(std::string prefix)
{
	std::vector<Hero> matchedHeroes;

	for(int i = 0; i < _heroes.size(); i++){
		if(isPrefix(prefix, _heroes[i].Name())){
			matchedHeroes.push_back(_heroes[i]);
		}
	}
	return matchedHeroes;
}

void HeroesDB::PrintHero(Hero& heroRef)
{
	Console::WriteLine(std::to_string(heroRef.Id()) + ": " + heroRef.Name(), Yellow);

	Console::WriteLine("\tSTATS:", Cyan);
	Console::WriteLine("\t\tIntelligence: " + std::to_string(heroRef.Powerstats().Intelligence), White);
	Console::WriteLine("\t\tStrength: " + std::to_string(heroRef.Powerstats().Strength), White);
	Console::WriteLine("\t\tSpeed: " + std::to_string(heroRef.Powerstats().Speed), White);
	Console::WriteLine("\t\tDurability: " + std::to_string(heroRef.Powerstats().Durability), White);
	Console::WriteLine("\t\tPower: " + std::to_string(heroRef.Powerstats().Power), White);
	Console::WriteLine("\t\tCombat: " + std::to_string(heroRef.Powerstats().Combat), White);

	Console::WriteLine("\tAPPEARANCE:", Cyan);
	Console::WriteLine("\t\tRace: " + heroRef.Appearance().Race, White);

	std::string heightStr;
	for(int i = 0; i < heroRef.Appearance().Height.size(); i++){
		if(i == heroRef.Appearance().Height.size() - 1){
			heightStr += heroRef.Appearance().Height[i];
		}
		else{
			heightStr += heroRef.Appearance().Height[i] + ", ";
		}
	}
	Console::WriteLine("\t\tHeight: " + heightStr, White);

	std::string weightStr;
	for(int i = 0; i < heroRef.Appearance().Weight.size(); i++){
		if(i == heroRef.Appearance().Weight.size() - 1){
			weightStr += heroRef.Appearance().Weight[i];
		}
		else{
			weightStr += heroRef.Appearance().Weight[i] + ", ";
		}
	}
	Console::WriteLine("\t\tWeight: " + weightStr, White);
	Console::WriteLine("\t\tEye Color: " + heroRef.Appearance().EyeColor, White);
	Console::WriteLine("\t\tHair Color: " + heroRef.Appearance().HairColor, White);

	Console::WriteLine("\tBIO:", Cyan);
	Console::WriteLine("\t\tFull Name: " + heroRef.Biography().FullName, White);
	Console::WriteLine("\t\tAlter Egos: " + heroRef.Biography().AlterEgos, White);

	std::string aliaStr;
	for(int i = 0; i < heroRef.Biography().Aliases.size(); i++){
		if(i == heroRef.Biography().Aliases.size() - 1){
			aliaStr += heroRef.Biography().Aliases[i];
		}
		else{
			aliaStr += heroRef.Biography().Aliases[i] + ", ";
		}
	}
	Console::WriteLine("\t\tAliases: " + aliaStr, White);

	Console::WriteLine("\t\tPlace of Birth: " + heroRef.Biography().PlaceOfBirth, White);
	Console::WriteLine("\t\tFirst Appearance: " + heroRef.Biography().FirstAppearance, White);
	Console::WriteLine("\t\tPublisher: " + heroRef.Biography().Publisher, White);
	Console::WriteLine("\t\tAlignment: " + heroRef.Biography().Alignment, White);

	Console::WriteLine("\tWORK:", Cyan);
	Console::WriteLine("\t\tOccupation: " + heroRef.Work().Occupation, White);

	Console::WriteLine("\tCONNECTIONS:", Cyan);
	Console::WriteLine("\t\tGroup Affiliation: " + heroRef.Connections().GroupAffiliation, White);
	Console::WriteLine("\t\tRelatives: " + heroRef.Connections().Relatives, White);
}

bool HeroesDB::FindHero(std::string name, Hero& heroRef){
	bool heroFound = false;
	for (int i = 0; i < _heroes.size(); i++){
		if(_stricmp(_heroes[i].Name().c_str(), name.c_str()) == 0)
		{
			heroRef = _heroes[i];
			heroFound = true;
			break;
		}
		else
		{
			heroFound = false;
		}
	}
	return heroFound;
}

void HeroesDB::RemoveAllHeroes(std::string name, std::vector<Hero>& heroesFound)
{
	for(int i = 0; i < _heroes.size(); i++){
		if(isPrefix(name, _heroes[i].Name())){
			heroesFound.push_back(_heroes[i]);
			RemoveHero(_heroes[i].Name());
		}
	}
}

//----------------------------------------------------------------
//                                                              //
//		        DO NOT EDIT THE CODE BELOW                      //
//                                                              //

//DEFINE the method in CPP file
//  *** don't forget the "HeroesDB::" in front of the method name.
Hero HeroesDB::GetBestHero()
{
	return _heroes[51];
}

HeroesDB::HeroesDB()
{
	DeserializeFromFile("heroes.json");
}

bool HeroesDB::charComparer(char c1, char c2)
{
	return std::tolower(c1, std::locale()) == std::tolower(c2, std::locale());
}
bool HeroesDB::isPrefix(const std::string& prefix, const std::string& word)
{
	return  (std::mismatch(prefix.begin(), prefix.end(),
		word.begin(), word.end(),
		charComparer)).first == prefix.end();
}


bool HeroesDB::Deserialize(const std::string& s)
{
	rapidjson::Document doc;
	if (!InitDocument(s, doc))
		return false;

	if (!doc.IsArray())
		return false;


	_heroes.reserve(doc.Size());

	for (rapidjson::SizeType i = 0; i < doc.Size(); ++i)
	{
		rapidjson::Value& node = doc[i];
		Hero myHero(node);
		_heroes.push_back(myHero);
	}

	return true;
}


bool HeroesDB::Serialize(rapidjson::Writer<rapidjson::StringBuffer>* writer) const
{
	return true;
}