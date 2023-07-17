#include "Map.h"
#include <map>
#include <unordered_map>
#include <string>


struct CityRecord {
	string name;
	uint64_t Population;
	double Latitude, Longitude;
};

//the hash key has to be a easy hashable type like integer or string
// if i want to use a more complex data as index  in map
//have to tell to the compiler how to use the hash function in my specific case
// redefine hash function eith my data type (CityRecord)
namespace std
{

	template<>
	struct hash<CityRecord> 
		
{
		size_t operator()(const CityRecord& key)const
		{
			return hash<string>()(key.name);
		}
	
		
	};
}
//this functionality can be used in case of non unique data that could return multiple elements (city with same name)


void Map() {
	//this type of map is ordered thank to a self balancing binary tree
	map<string, CityRecord> cityMap;	// first argument is the key used to index the data, in this case it index by name
	cityMap["Torino"] = CityRecord{ "Torino", 1000, 9.4, 8.4 };
	cityMap["Milano"] = CityRecord{ "Milano", 2000, 6.4, 9.6 };
	cityMap["Roma"] = CityRecord{ "Roma", 7452, 9.7, 1.6 };
	cityMap["Torino"] = CityRecord{ "Firenze", 453, 3.4, 2.6 };
	cityMap["Venezia"] = CityRecord{ "Venezia", 87667, 9.8, 8.6 };

	//data fetching
	//CityRecord& TurinData = cityMap["Torino"];
	

}

void Unordered_Map() {
	//use ash table to gether the hash that find the searched element, sometimes the data are stored inthe same order as inserted but is not guaranteed
	unordered_map<string, CityRecord> cityMap;	// first argument is the key used to index the data, in this case it index by name
	cityMap["Torino"] = CityRecord{ "Torino", 1000, 9.4, 8.4 };
	cityMap["Milano"] = CityRecord{ "Milano", 2000, 6.4, 9.6 };
	cityMap["Roma"] = CityRecord{ "Roma", 7452, 9.7, 1.6 };
	cityMap["Torino"] = CityRecord{ "Firenze", 453, 3.4, 2.6 };
	cityMap["Venezia"] = CityRecord{ "Venezia", 87667, 9.8, 8.6 };

	//data fetching
	CityRecord& TurinData = cityMap["Torino"];

	//use city record as key through the hash template for city record
	unordered_map<CityRecord, int> founded_map;
	founded_map[CityRecord{ "Torino", 1000, 9.4, 8.4 }] = 1000;
	founded_map[CityRecord{ "Milano", 2000, 6.4, 9.6 }] = 1500;
	founded_map[CityRecord{ "Roma", 7452, 9.7, 1.6 }] = 1200;
	founded_map[CityRecord{ "Firenze", 453, 3.4, 2.6 }] = 2000;
	founded_map[CityRecord{ "Venezia", 87667, 9.8, 8.6 }] = 5667;

	//iterating through map (nonsense, if we need to iterate is easier to use vector)
	for (auto& kv : cityMap) {
		const string& name = kv.first;
		CityRecord& city = kv.second;
		cout << name << endl;;
	}

	/* c++ 17 version of iterating
	for (auto& [name, city] : cityMap) {
		cout << name << city << endl;
	}
	*/
}