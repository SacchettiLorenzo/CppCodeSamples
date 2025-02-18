#pragma once
#include <any>
#include <string>
#include <unordered_map>
#include <chrono>
#include <iostream>
#include "Cache.h"

class LRUCache
{
public:
	LRUCache(const int& max_size);
	LRUCache(LRUCache&&) = default;
	LRUCache& operator==(LRUCache&& other);
	bool insert(std::string key, std::any data);
	std::any get(const std::string& key);
	bool remove(const std::string& key);
	bool resize(const int& new_size);

private:
	int max_size;

	typedef struct {
		std::any data;
		std::chrono::high_resolution_clock::time_point time_point;
	}Data;

	std::unordered_map<std::string, Data>::iterator Oldestlement;

	std::unordered_map<std::string, Data> cache;

	//Least Frequently Used Element


	void findOldestElement();
};

