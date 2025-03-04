#include "LFUCache.h"
#include "Cache.h"

LFUCache::LFUCache(const int& max_size) : max_size(max_size)
{

}

LFUCache& LFUCache::operator==(LFUCache&& other)
{
	if (this != &other) {
		delete &cache;
		delete& LFUElement;

		this->max_size = other.max_size;
		this->cache = other.cache;
		this->LFUElement = other.LFUElement;
	}

	return *this;
}

bool LFUCache::insert(std::string key, std::any data, size_t size)
{
	if (cache.size() < this->max_size) {
		LFUElement = cache.insert({ key,Data{data,size,0} }).first;
	}
	else {
		cache.erase(LFUElement);
		LFUElement = cache.insert({ key,Data{data,size,0} }).first;
	}

	return true;
}

bool LFUCache::update(std::string key, std::any data, size_t size)
{
	auto it = cache.find(key);

	if (it != cache.end()) {
		it->second = Data{ data,0 };
	}
	else {
		insert(key, data,size);
	}
	return true;
}

std::pair<size_t,std::any> LFUCache::get(const std::string& key)
{
	std::unordered_map<std::string, Data>::iterator res = cache.find(key);
	if (res != cache.end()) {
		(*res).second.frequency++;
		if ((*res).second.frequency < (*LFUElement).second.frequency) {
			LFUElement = res;
		}
		return std::pair<size_t, std::any>((*res).second.size, (*res).second.data);
	}
	else {
		return std::pair<size_t,std::any>(0,NULL);
	}
}

bool LFUCache::remove(const std::string& key)
{
	std::unordered_map<std::string, Data>::iterator to_remove = cache.find(key);
	bool res = cache.erase(key);
	
	if (res == true && to_remove == LFUElement) {
		findLFUElement();
	}

	return res;
}

bool LFUCache::resize(const int& new_size)
{

	typedef std::unordered_map<std::string, Data>::iterator IT;
	
	auto compare = [](const IT& l, const IT& r) {
		return (*l).second.frequency < (*r).second.frequency;
		};

	std::priority_queue < IT, std::vector<IT>, decltype(compare) > pq(compare);

	for (auto it = cache.begin(); it != cache.end(); it++) {
		pq.push(it);
	}

	std::unordered_map<std::string, Data> new_cache;

	for (int i = 0; i < new_size-1; i++) {
		new_cache.insert({ (*pq.top()).first,(*pq.top()).second });
		pq.pop();
	}
	
	LFUElement = new_cache.insert({ (*pq.top()).first,(*pq.top()).second }).first;
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

void LFUCache::findLFUElement()
{
	LFUElement = std::min_element(cache.begin(), cache.end(), 
		[](const std::pair<std::string, Data> &l, const  std::pair<std::string, Data> &r) {
			return l.second.frequency < r.second.frequency;
		});
}
