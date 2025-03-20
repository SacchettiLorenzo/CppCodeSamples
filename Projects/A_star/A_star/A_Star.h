#pragma once
#include "Node.h"



template <typename T, typename ID>
class A_Star
{
private:
	struct Comparator
	{
		//smalles on top
		bool operator()(const std::pair<Node<T,ID>* ,int >& a, const std::pair<Node<T,ID>* ,int>& b) const {
			return a.second > b.second;
		}
	};

public:
	A_Star(
		std::initializer_list < std::pair<Node<T,ID>*, 
		std::initializer_list<std::pair<Node<T,ID>*, int>>>> nodes, 
		Node<T,ID>* start, 
		Node<T,ID>* goal, 
		std::initializer_list<std::pair<Node<T,ID>*, int>> heuristics, 
		std::vector<Node<T,ID>*>& path, 
		int& final_cost);

};


template<typename T, typename ID>
inline A_Star<T, ID>::A_Star(std::initializer_list<std::pair<Node<T,ID>*, std::initializer_list<std::pair<Node<T,ID>*, int>>>> nodes, Node<T,ID>* start, Node<T,ID>* goal, std::initializer_list<std::pair<Node<T,ID>*, int>> heuristics, std::vector<Node<T,ID>*>& path, int& final_cost)
{
	for (auto node : nodes) {
		for (auto adjacent : node.second) {
			static_cast<Node<T,ID>*>(node.first)->add_adjacent(adjacent.first, adjacent.second);
		}
	}

	std::unordered_map < Node<T,ID>*, int> heuristic_map;

	for (auto element : heuristics) {
		heuristic_map.insert({ element.first, element.second });
	}

	std::priority_queue<std::pair<Node<T,ID>*, int>, std::vector<std::pair<Node<T,ID>*, int>>, Comparator> open_nodes;
	std::map<void*, Node<T,ID>*> closed_nodes;

	closed_nodes.insert({ start, start });

	for (auto node : start->get_adjacents()) {
		node.second = node.second + (*heuristic_map.find(node.first)).second;
		open_nodes.push(node);
	}

	while (!open_nodes.empty())
	{
		auto pair = open_nodes.top();

		Node<T,ID>* current_node = pair.first;
		int current_cost = pair.second;
		open_nodes.pop();


		//if we want to only return the cost 
		/*if (current_node == goal) {
			final_cost = current_cost;
			return;
		}*/

		if (closed_nodes.find(current_node) != closed_nodes.end()) {
			continue;
		}


		closed_nodes.insert({ current_node, current_node });

		current_cost -= (*heuristic_map.find(current_node)).second;

		//if we want to save the path we have to check the adjacents first
		//this seems to be a repetition but if we to it later we cannot use the 
		//closed list to get the correct path
		//this also calculate the final cost
		if (path.size() == 0) {
			auto adjacents = current_node->get_adjacents();
			for (auto node : adjacents) {
				if (node.first == goal) {
					for (auto node : closed_nodes) {
						path.push_back(node.second);
					}
					path.push_back(goal);
					final_cost = current_cost + node.second;
					return;
				}
			}
		}

		for (auto node : current_node->get_adjacents()) {
			if (closed_nodes.find(node.first) == closed_nodes.end()) {
				node.second = node.second + current_cost + (*heuristic_map.find(node.first)).second;
				open_nodes.push(node);
			}
		}
	}
}

