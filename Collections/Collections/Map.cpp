#include "Map.h"
#include <map>
#include <unordered_map>
#include <string>
#include <vector>

struct CityRecord {
	string name;
	uint64_t Population;
	double Latitude, Longitude;
};

// if i want to use a more complex data as index  in map
//have to tell to the compiler how to use the hash function in my specific case
// redefine hash function eith my data type (CityRecord)
namespace std {

	template<>
	struct hash<CityRecord> {
		size_t operator()(const CityRecord& key)const {
			return hash<string>()(key.name);
		}

		
	};
}
//this functionality can be used in case of non unique data that could return multiple elements (city with same name)

void example() {

	// data structure with several element
	// in this case i should iterate all the structure to find what i'm looking for
	/*
	vector<CityRecord> cities;
	cities.emplace_back("Torino", 1000, 9.4, 8.4);
	cities.emplace_back("Milano", 2000, 6.4, 9.6);
	cities.emplace_back("Roma", 7452, 9.7, 1.6);
	cities.emplace_back("Firenze", 453, 3.4, 2.6);
	cities.emplace_back("Venezia", 87667, 9.8, 8.6);
	*/

	/*
	// use of map
	map<string, CityRecord> cityMap;	// first argument is the key used to index the data, in this case it index by name
	cityMap["Torino"] = CityRecord{ "Torino", 1000, 9.4, 8.4 };
	cityMap["Milano"] = CityRecord{ "Milano", 2000, 6.4, 9.6 };
	cityMap["Roma"] = CityRecord{ "Roma", 7452, 9.7, 1.6 };
	cityMap["Torino"] = CityRecord{ "Firenze", 453, 3.4, 2.6 };
	cityMap["Venezia"] = CityRecord{ "Venezia", 87667, 9.8, 8.6 };

	string cityinput = "Torino"; // requested city name
	
	CityRecord& genericCity = cityMap[cityinput]; //  
	genericCity.Population;
	*/

	unordered_map<string, CityRecord> cityMap;	// first argument is the key used to index the data, in this case it index by name
	cityMap["Torino"] = CityRecord{ "Torino", 1000, 9.4, 8.4 };
	cityMap["Milano"] = CityRecord{ "Milano", 2000, 6.4, 9.6 };
	cityMap["Roma"] = CityRecord{ "Roma", 7452, 9.7, 1.6 };
	cityMap["Torino"] = CityRecord{ "Firenze", 453, 3.4, 2.6 };
	cityMap["Venezia"] = CityRecord{ "Venezia", 87667, 9.8, 8.6 };

	string cityinput = "Torino"; // requested city name

	CityRecord& genericCity = cityMap[cityinput]; //  
	genericCity.Population;

	if (cityMap.find("Milano") == cityMap.end()) // find is used to chek if an element exist before accessing with [] operator or .at() function
		cout << cityMap.at("Milano").name << " is the last city" << endl;

	unordered_map<CityRecord, uint32_t> foundedCity;
	foundedCity[CityRecord{ "Torino", 1000, 9.4, 8.4 }] = 1850; //using the full CityRecord struct as key of the map
	

}