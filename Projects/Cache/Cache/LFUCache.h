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
	LFUCache(const int& max_size);
	LFUCache(LFUCache&&) = default;
	LFUCache& operator ==(LFUCache&& other);


	bool insert(std::string key, std::any data, size_t size);
	bool update(std::string key, std::any data, size_t size);
	std::pair<size_t, std::any> get(const std::string& key);
	bool remove(const std::string& key);
	bool resize(const int& new_size);

private:
	int max_size;

	typedef struct {
		std::any data;
		size_t size;
		int frequency;
	}Data;

	std::unordered_map<std::string, Data>::iterator LFUElement;

	std::unordered_map<std::string, Data> cache;

	//Least Frequently Used Element


	void findLFUElement();

};

