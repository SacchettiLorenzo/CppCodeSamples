#pragma once
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include "Node.h"

using namespace std;

class ChartController
{
private:
	struct Couple{
		int a;
		int b;
	};

	vector<Node*> nodes;
	vector<Couple>connections;
public:
	 ChartController() = default;
	void InsertChartNode(Node* n);
	void UpdateConnectionNode(Node A, Node B, int cost);
	void UpdateConnectionNode(Node A, Node B, int costAtoB, int costBtoA);
	void RemoveConnection(Node A, Node B);
	void RemoveNodeFromChart(int nodeId);
	 void Commit();
};

