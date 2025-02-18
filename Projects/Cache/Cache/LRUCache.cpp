#include "LRUCache.h"
#include <queue>


LRUCache::LRUCache(const int& max_size) : max_size(max_size)
{
	
}

LRUCache& LRUCache::operator==(LRUCache&& other) {
	if (this != &other) {
		
		delete &cache;
		delete &Oldestlement;
		
		this->max_size = other.max_size;
		this->cache = other.cache;
		this->Oldestlement = other.Oldestlement;
	}

	return *this;
}

bool LRUCache::insert(std::string key, std::any data)
{
	if (cache.size() < this->max_size) {
		cache.insert({ key,Data{data,std::chrono::high_resolution_clock::now()}}).first;
		findOldestElement();
	}
	else {
		cache.erase(Oldestlement);
		cache.insert({ key,Data{data,std::chrono::high_resolution_clock::now()} }).first;
		findOldestElement();
	}
	return false;
}

std::any LRUCache::get(const std::string& key)
{
	std::unordered_map<std::string, Data>::iterator res = cache.find(key);
	if (res != cache.end()) {
		return (*res).second.data;
	}
	else {
		return NULL;
	}
}

bool LRUCache::remove(const std::string& key)
{
	std::unordered_map<std::string, Data>::iterator to_remove = cache.find(key);
	bool res = cache.erase(key);

	if (res == true && to_remove == Oldestlement) {
		findOldestElement();
	}

	return res;
}

bool LRUCache::resize(const int& new_size)
{
	typedef std::unordered_map<std::string, Data>::iterator IT;

	auto compare = [](const IT& l, const IT& r) {
		return (*l).second.time_point < (*r).second.time_point;
		};

	std::priority_queue < IT, std::vector<IT>, decltype(compare) > pq(compare);

	for (auto it = cache.begin(); it != cache.end(); it++) {
		pq.push(it);
	}

	std::unordered_map<std::string, Data> new_cache;

	for (int i = 0; i < new_size - 1; i++) {
		new_cache.insert({ (*pq.top()).first,(*pq.top()).second });
		pq.pop();
	}

	Oldestlement = new_cache.insert({ (*pq.top()).first,(*pq.top()).second }).first;
	pq.pop();

	cache = std::move(new_cache);

	while (pq.size() != 0)
	{
		pq.pop();
	}

	this->max_size = new_size;

	//todo: return true only if everythings went good
	return true;
}

void LRUCache::findOldestElement()
{
	Oldestlement = std::min_element(cache.begin(), cache.end(),
		[](const std::pair<std::string, Data>& l, const  std::pair<std::string, Data>& r) {
			return l.second.time_point < r.second.time_point;
		});
}
