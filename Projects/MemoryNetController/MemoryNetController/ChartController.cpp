// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "ChartController.h"


void ChartController::InsertChartNode(Node* n)
{
	nodes.push_back(n);
}

void ChartController::UpdateConnectionNode(Node A, Node B, int cost)
{
	//add cost
	connections.push_back({ A.id,B.id });
}

void ChartController::UpdateConnectionNode(Node A, Node B, int costAtoB, int costBtoA)
{
	//add cost
	connections.push_back({ A.id,B.id });
	connections.push_back({ B.id,A.id });
}

void ChartController::RemoveNodeFromChart(int nodeId)
{
	for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end();) {
		if ((*it)->id == nodeId) {
			it = nodes.erase(it);
		}
		else {
			++it;
		}
	}
	
}

/*

*/
void ChartController::Commit()
{
	ofstream Dataset("Dataset.js");
	const string NodesDatasetHead = "const NodesDataset = [";
	const string NodesDatasetFoot =  "];";
	Dataset << NodesDatasetHead << endl;
	for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		Dataset << "{ id:" << (*it)->id << ", label: '" << (*it)->label << "'}," << endl;
	}
	Dataset << NodesDatasetFoot << endl;
	Dataset << endl;

	const string ConnectionsDataseetHead = "const ConnectionDataset = [";
	const string ConnectionsDatasetFoot = "];";
	Dataset << ConnectionsDataseetHead << endl;
	for (vector<Couple>::iterator it = connections.begin(); it != connections.end(); it++) {
		Dataset << "{ from:" << it->a << ", to: " << it->b << "}," << endl;
	}
	Dataset << ConnectionsDatasetFoot << endl;

	Dataset.close();
}


void ChartController::RemoveConnection(Node A, Node B)
{
	for (vector<Couple>::iterator it = connections.begin(); it != connections.end();) {
		if ((it->a == A.id && it->b == B.id) || (it->b == A.id && it->a == B.id)) {
			it = connections.erase(it);
		}
		else {
			++it;
		}
	}
}

