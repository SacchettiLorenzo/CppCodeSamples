#include <iostream>
#include "Node.h"
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "A_Star.h"

int main()
{

	Node<std::string,std::string> S("START");//start
	Node<std::string,std::string> A("A");
	Node<std::string,std::string> B("B");
	Node<std::string,std::string> C("C");
	Node<std::string,std::string> D("D");
	Node<std::string,std::string> E("E");
	Node<std::string,std::string> F("F");
	Node<std::string,std::string> H("H");
	Node<std::string,std::string> I("I");
	Node<std::string,std::string> J("J");
	Node<std::string,std::string> K("K");
	Node<std::string,std::string> G("GOAL");//goal

	std::vector<Node<std::string,std::string>*> path;
	int final_cost = 0;

	A_Star<std::string, std::string> graph(
		{ {&S,{{&A,4},{&B,10},{&C,11}}},
			{&A,{{&B,8},{&D,5}}},
			{&B,{{&D,15}}},
			{&C,{{&E,20},{&D,8},{&F,2}}},
			{&D,{{&H,16},{&I,20},{&F,1}}},
			{&E,{{&G,19}}},
			{&F,{{&G,13}}},
			{&H,{{&I,1},{&J,2}}},
			{&I,{{&G,5},{&K,13},{&J,5}}},
			{&J,{{&K,7}}},
			{&K,{{&G,16}}}
		},
		&S,
		&G,
		{
			{&S,7},
			{&A,8},
			{&B,6},
			{&C,5},
			{&D,5},
			{&E,3},
			{&F,3},
			{&G,0},
			{&H,7},
			{&I,4},
			{&J,5},
			{&K,3}
		},
		path,
		final_cost
	);

	for (auto node : path) {
		std::cout << node->get_id() << std::endl;
	}

	std::cout << final_cost << std::endl;

}

