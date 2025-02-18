#pragma once
#include <map>
#include <unordered_map>
#include <any>
#include <string>
#include <set>
#include <functional>
#include <queue>
#include <iostream>
#include "Cache.h"

class LFUCache
{
public:
	LFUCache(const int& max_size) ;

	//insert the data descarding element with least frequency
	bool insert(std::string key, std::any data) ;
	std::any get(const std::string& key) ;
	bool remove(const std::string & key);
	bool resize(const int& new_size);

private:
	int max_size;
	
	typedef struct {
		std::any data;
		int frequency;
	}Data;

	std::unordered_map<std::string, Data>::iterator LFUElement;
	
	std::unordered_map<std::string,Data> cache;

	//Least Frequently Used Element
	

	void findLFUElement();
	
};

