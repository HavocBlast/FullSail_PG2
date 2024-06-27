#include "HeroesDB.h"
#include <iostream>
#include "Console.h"
#include <algorithm> 
#include <string_view>
#include <locale>
#include <cctype>
#include <iomanip>





//----------------------------------------------------------------
//                                                              //
//		        ADD YOUR METHOD DEFINITIONS HERE                //
//                                                              //

std::vector<Hero> HeroesDB::Merge(std::vector<Hero> left, std::vector<Hero> right, SortBy selectedAttribute)
{
	std::vector<Hero> result;

	while(!left.empty() > 0 && !right.empty()){
		if(Hero::Compare(left[0], right[0], selectedAttribute) < 1){
			result.push_back(left[0]);
			left.erase(left.begin());
		}
		else{
			result.push_back(right[0]);
			right.erase(right.begin());
		}
	}

	while(!left.empty()){
		result.push_back(left[0]);
		left.erase(left.begin());
	}

	while(!right.empty()){
		result.push_back(right[0]);
		right.erase(right.begin());
	}

	return result;
}

std::vector<Hero> HeroesDB::MergeSort(std::vector<Hero> heroes, SortBy selectedAttribute)
{
	if(heroes.size() <= 1){
		return heroes;
	}

	std::vector<Hero> left;
	std::vector<Hero> right;

	for(int i = 0; i < heroes.size(); i++){
		if(i < heroes.size() / 2){
			left.push_back(heroes[i]);
		}	
		else{
			right.push_back(heroes[i]);
		}
	}

	left = MergeSort(left, selectedAttribute);
	right = MergeSort(right, selectedAttribute);

return Merge(left, right,selectedAttribute);
}

void HeroesDB::SortByAttribute(SortBy selectedAttribute)
{
	std::vector<Hero> sortedHeroes = MergeSort(_heroes, selectedAttribute);
	for(Hero hero : sortedHeroes){
		std::string attribute = hero.GetSortByAttribute(selectedAttribute);
		std::cout << std::setw(3) << hero.Id() << ":" << std::setw(5) << attribute << " " << hero.Name() << std::endl; 
	}
}

int HeroesDB::BinarySearch(std::vector<Hero> hero, std::string searchTerm, int low, int high)
{
	if(high < low){
		return -1;
	}

	int mid = (low + high) / 2;

	if (_stricmp(searchTerm.c_str(), hero[mid].Name().c_str()) < 0) {
		return BinarySearch(hero, searchTerm, low, mid - 1); // Left
	}
	else if(_stricmp(searchTerm.c_str(), hero[mid].Name().c_str()) > 0){
		return BinarySearch(hero, searchTerm, mid + 1, high); // Right
	}
	else{
		return mid;
	}
}

void HeroesDB::FindHero(std::string heroName)
{
	int result = BinarySearch(_heroes, heroName, 0 ,_heroes.size()-1);
		
	if(result == -1){
		Console::WriteLine(heroName + " is not found.");
	}
	else{
		Console::WriteLine(_heroes[result].Name() + " was found at index " + std::to_string(result) + ".");
	}
}

void HeroesDB::GroupHeroes()
{
	for(Hero hero : _heroes){
		auto currentHero = _groupedHeroes.find(hero.Name()[0]);
		if(currentHero == _groupedHeroes.end()){ // first letter not in map yet
			// Create new vector
			std::vector<Hero> foundHeroes;
			// Add the hero to the vector
			foundHeroes.push_back(hero);
			// Add the vector to the map as the value for that initial letter
			_groupedHeroes.insert(std::make_pair(hero.Name()[0], foundHeroes));
		}
		else{// Found the first letter already
			//Add the hero to the vector that is stored for that key
			_groupedHeroes[hero.Name()[0]].push_back(hero); 
		}
	}
}

void HeroesDB::PrintGroupCounts()
{
	if(_groupedHeroes.empty()){
		GroupHeroes();
	}

	Console::WriteLine("Key: Hero Count");
	for(const auto& [group, heroes] : _groupedHeroes){
		std::cout << group << ": " << heroes.size() << std::endl;
	}
}

void HeroesDB::FindHeroesByLetter(char letter)
{
	if(_groupedHeroes.empty()){
		GroupHeroes();
	}
	else{
		auto heroesFound = _groupedHeroes.find(letter);
		if(heroesFound != _groupedHeroes.end()){
			
			for(auto hero : heroesFound->second){
				std::cout << std::to_string(hero.Id()) << " : " << hero.Name() << std::endl;
			}
		}
		else{
			Console::WriteLine("There were no heroes that start with the letter " + letter);
		}
	}
}

void HeroesDB::RemoveHero(std::string name)
{
	if(_groupedHeroes.empty()){
		GroupHeroes();
	}
	auto heroFound = _groupedHeroes.find(name[0]);
	if(heroFound == _groupedHeroes.end()){
		std::cout << name << " was not found." << std::endl;
	}
	else{
		std::vector<Hero> heroesFound = heroFound->second;
		int result = BinarySearch(heroesFound,name, 0, heroesFound.size() - 1);
		if(result == -1){
			std::cout << name << " was not found." << std::endl;
		}
		else{// found hero in vector
			// remove hero from vector
			heroesFound.erase(heroesFound.begin() + result);

			// search for the hero in the _heroes vector
			int result = BinarySearch(_heroes,name, 0, _heroes.size() - 1);
			// Print that the hero was removed
			std::cout << _heroes[result].Name() << " was removed." << std::endl;
			// remove hero from _heroes vector
			_heroes.erase(_heroes.begin() + result);
			// remove letter key  from _groupedHeroes if empty
			if(heroesFound.empty()){
				_groupedHeroes.erase(name[0]);
			}
		}
	}
}

//----------------------------------------------------------------
//                                                              //
//		        DO NOT EDIT THE CODE BELOW                      //
//                                                              //


HeroesDB::HeroesDB()
{
	DeserializeFromFile("heroes.json");
}

std::string HeroesDB::toUpper(const std::string& str)
{
	std::string copy = str;
	std::transform(copy.begin(),
		copy.end(),
		copy.begin(),
		[](unsigned char c) { return std::toupper(c); });
	return copy;
}

std::string HeroesDB::toUpper2(const std::string& str)
{
	std::string copy = str;
	for (auto& c : copy) c = toupper(c);
	return copy;
}

void HeroesDB::SortByNameDescending()
{
	std::vector<Hero> sorted(_heroes); //clone the list

	size_t n = sorted.size();
	bool swapped;
	do
	{
		swapped = false;
		for (size_t i = 1; i <= n - 1; i++)
		{
			int compResult = _stricmp(sorted[i - 1].Name().c_str(), sorted[i].Name().c_str());
			//int compResult = toUpper(sorted[i - 1].Name()).compare(toUpper(sorted[i].Name()));
			if (compResult < 0)
			{
				swapped = true;
				std::swap(sorted[i - 1], sorted[i]);

				//int temp = vec[i - 1];
				//vec[i - 1] = vec[i];
				//vec[i] = temp;
			}
		}
		--n;
	} while (swapped);

	for (auto& hero : sorted)
	{
		std::cout << hero.Id() << ": " << hero.Name() << std::endl;
	}
	std::cout << std::endl;
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