#pragma once
#include<set>
#include<map>
#include<string>

template <typename T, typename ID = int>
class Node
{

private:

	struct Comparator
	{
		bool operator()(const std::pair<Node<T, ID>* ,int>& a, const std::pair<Node<T, ID>* ,int>& b) const {
			return a.second < b.second;
		}
	};

	std::set<std::pair<Node<T, ID>*, int>, Comparator> adjacents;
	T value;
	ID id;

public:
	Node(const Node& other) {
		this->set_value(other.value);
		this->replace_adjacents(other.adjacents);
	}
	Node(ID id) {
		this->id = id;
	}

	Node(ID id, T value) {
		this->id = id;
		this->value = value;
	}

	Node(T value, std::initializer_list<std::pair<Node<T, ID>*, int>> adjacents) {

		this->value = value;
		for (const auto& it : adjacents) {
			this->add_adjacent(it.first, it.second);
		}
	}
	bool has_adjacent() {
		return !adjacents.empty();
	}
	std::set<std::pair<Node<T, ID>*, int>, Comparator>& get_adjacents() {
		return this->adjacents;
	}
	
	bool add_adjacent(Node<T,ID>* other,int distance) {
		//todo check self connection
		return this->adjacents.insert(std::make_pair(other, distance)).second;
	}
	bool replace_adjacents(std::set<std::pair<Node<T,ID>*, int>>& adjacents) {
		this->adjacents = adjacents;
		return true;
	}

	T get_value() {
		return value;
	}

	void set_value(T value) {
		this->value = value;
	}

	ID get_id() {
		return id;
	}

	void set_id(ID id) {
		this->id = id;
	}


};