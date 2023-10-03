// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <any>
#include <iostream>
#include <unordered_map>
#include "IdManager.h"
#include <string>
#include <thread>

using namespace std;

class Node{

public:
    int id;
    string label;

    bool operator !=(Node const& obj) {
        return id != obj.id;
    }

    struct Connection {
        Node* node;
        int cost;

        Connection() = default;
        Connection(Node* n, int cost);
    };
    unordered_map<int, Connection> connections;

    Node() {
        id = IdManager::getNextId();
        label.clear();
        
    }

    static void Connect(Node& A, Node& B, int cost);
    static void Connect(Node& A, Node& B, int costAtoB, int costBtoA);
    static void Disconnect(Node& A, Node& B);
    //static vector<Node> FindBestPath(int A, int B, vector<Node>);
    static vector<Node> FindBestPath(int A, int B, vector<Node>);

private:
    static vector<Node> FindBestPath(int A, int B, vector<Node> nodes, unordered_map<int, int>* alreadyVisitedNodeId, Node* backTrackNode);
    any value;
    
   
};

