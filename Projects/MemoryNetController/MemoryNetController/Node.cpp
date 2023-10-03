// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Node.h"

Node::Connection::Connection(Node* n, int cost) {
	this->node = n;
	this->cost = cost;
}

//connect A and B with the same cost from A to B and B to A
void Node::Connect(Node& A, Node& B, int cost) {
	A.connections[B.id] = Node::Connection(&B, cost);
	B.connections[A.id] = Node::Connection(&A, cost);

}
//connecto A and B with costAtoB as cost from A to A anb constBtoA as cost from B to A
void Node::Connect(Node& A, Node& B, int costAtoB, int costBtoA) {
	A.connections[B.id] = Node::Connection(&B, costAtoB);
	B.connections[A.id] = Node::Connection(&A, costBtoA);
}

void Node::Disconnect(Node& A, Node& B) {
	A.connections.erase(B.id);
	B.connections.erase(A.id);
}

/*
vector<Node> Node::FindBestPath(int A, int B, vector<Node> nodes) {
	unordered_map<int,int> alreadyVisitedNodeId;
	Node* lifesaver = nullptr;
	return Node::FindBestPath(A, B, nodes,&alreadyVisitedNodeId,lifesaver);
}

vector<Node> Node::FindBestPath(int A, int B, vector<Node> nodes, unordered_map<int,int>* alreadyVisitedNodeId,Node* lifesaver)
{

	vector<Node> bestpath;
	if (A == B)return  bestpath;
	Node a = nodes[A-1];
	if (a.connections.size() > 2)lifesaver = &a;
	Node b = nodes[B-1];

	(*alreadyVisitedNodeId)[A] = A;

	while (a != b) 
	{
		{
			cout << "a: " << a.id << endl;
			//cout << "b: " << b.id << endl;
		
		}
		if (a.connections.size() == 1) {
			unordered_map<int ,Node::Connection>::iterator it = a.connections.begin();
			Node k;
			k = *((*it).second.node);
			k.connections.clear();
			if ((*it).second.node->id == a.id) { // if node is self connected
				bestpath.push_back(k);
			}
			else { // if node is connected with other node
			a = *((*it).second.node);
			(*alreadyVisitedNodeId)[a.id] = a.id;
			bestpath.push_back(k);
			}
		}
		else {
			//recursive code for finding the best path
			
			int counter = 0;
			for (auto k : a.connections)
			{
				auto search = alreadyVisitedNodeId->find(k.second.node->id);
					if (search == alreadyVisitedNodeId->end())
					{
						FindBestPath(k.second.node->id, B, nodes,alreadyVisitedNodeId,lifesaver);
					}
					else {
						counter++;
						if (counter == a.connections.size()) {
							FindBestPath(lifesaver->id, B, nodes, alreadyVisitedNodeId, lifesaver);
						}
						else
							continue; 
					}
			}
		}

	}

	return bestpath;

}
*/

vector<Node> Node::FindBestPath(int A, int B, vector<Node> nodes) {
	unordered_map<int, int> alreadyVisitedNodeId;
	Node backTrackNode;
	return Node::FindBestPath(A,B,nodes,&alreadyVisitedNodeId,&backTrackNode);
}

vector<Node> Node::FindBestPath(int A, int B, vector<Node> nodes, unordered_map<int, int>* alreadyVisitedNodeId,Node* backTrackNode)
{
	// add condition if a == b
	vector<Node> bestpath;


	cout << "going from: " << A << " to: " << B << endl;
	Node a = nodes[A - 1];
	Node b = nodes[B - 1];
	//Node backtrackNode = a;
	if (a.id == b.id) {
		cout << "arrived" << endl;
		return bestpath;
	}

	(*alreadyVisitedNodeId).insert({ a.id,a.id });

	//single node trace
	bool singleNodeTrace = false;

	if (a.connections.size() < 3) {
		singleNodeTrace = true;
	}
	else {
		*backTrackNode = a;
	}

	if (singleNodeTrace == true)
	{
		while (a.connections.size() < 3) {
			for (auto k : a.connections) {
				auto search = (*alreadyVisitedNodeId).find(k.second.node->id);
				if (search == (*alreadyVisitedNodeId).end()) {
					a = *k.second.node;
					cout << "going from: " << a.id << " to: " << B << endl;
					(*alreadyVisitedNodeId).insert({ a.id,a.id });
					break;
				}
				else {
					a = *backTrackNode;
					cout << "going from: " << a.id << " to: " << B << endl;
					continue;
					//return to lasty element with more than 2 connection
				}
			}
		}
		singleNodeTrace = false;
		FindBestPath(a.id, B, nodes,alreadyVisitedNodeId, backTrackNode);
	}
	else {
		for (auto k : a.connections) {
			auto search = (*alreadyVisitedNodeId).find(k.second.node->id);
			if (search == (*alreadyVisitedNodeId).end()) {

			FindBestPath(k.second.node->id, B, nodes,alreadyVisitedNodeId, backTrackNode);
			}
		}
	}


	return bestpath;
}
