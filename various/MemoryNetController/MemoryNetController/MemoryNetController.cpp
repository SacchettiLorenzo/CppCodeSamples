// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <iostream>
#include <memory>
#include <stdlib.h>    
#include <time.h>
#include "Node.h"
#include "ChartController.h"

using namespace std;

int globalIdCounter;

void spawn(int ammount);

int main()
{
    srand(time(NULL));
    ChartController CC;
    const int ammount = 25;
    vector<Node> bestpath;

    //TEST CASE
  
    Node one;
    Node two;
    Node three;
    Node four;
    Node five;
    Node six;
    Node seven;
    Node eight;
    Node nine;
    Node ten;
    Node eleven;
    Node twelve;
    Node thirteen;
    Node fourteen;
    Node fifteen;
    Node sixteen;
    Node seventeen;
    Node eighteen;
    Node nineteen;
    Node twenty;
    Node twentyone;
    Node twentytwo;
    Node twentythree;
    Node twentyfour;
    Node twentyfive;

    one.label = to_string(one.id);
    two.label = to_string(two.id);
    three.label = to_string(three.id);
    four.label = to_string(four.id);
    five.label = to_string(five.id);
    six.label = to_string(six.id);
    seven.label = to_string(seven.id);
    eight.label = to_string(eight.id);
    nine.label = to_string(nine.id);
    ten.label = to_string(ten.id);
    eleven.label = to_string(eleven.id);
    twelve.label = to_string(twelve.id);
    thirteen.label = to_string(thirteen.id);
    fourteen.label = to_string(fourteen.id);
    fifteen.label = to_string(fifteen.id);
    sixteen.label = to_string(sixteen.id);
    seventeen.label = to_string(seventeen.id);
    eighteen.label = to_string(eighteen.id);
    nineteen.label = to_string(nineteen.id);
    twenty.label = to_string(twenty.id);
    twentyone.label = to_string(twentyone.id);
    twentytwo.label = to_string(twentytwo.id);
    twentythree.label = to_string(twentythree.id);
    twentyfour.label = to_string(twentyfour.id);
    twentyfive.label = to_string(twentyfive.id);

    Node::Connect(fourteen, one,0);
    Node::Connect(one,twenty,0);
    Node::Connect(one,twentyfour,0);
    Node::Connect(twentyfour,four,0);
    Node::Connect(four,eight,0);
    Node::Connect(twenty,eighteen,0);
    Node::Connect(twenty,eight,0);
    Node::Connect(eight,fifteen,0);
    Node::Connect(eight,nine,0);
    Node::Connect(eighteen,thirteen , 0);
    Node::Connect(thirteen,six,0);
    Node::Connect(sixteen,nine,0);
    Node::Connect(nine,fifteen,0);
    Node::Connect(nine,twentythree,0);
    Node::Connect(nine,twentytwo,0);
    Node::Connect(six,twentyfive,0);
    Node::Connect(six,ten,0);
    Node::Connect(twentytwo,eleven,0);
    Node::Connect(seventeen,two,0);
    Node::Connect(two,five,0);
    Node::Connect(five,twelve,0);
    Node::Connect(five,eleven , 0);
    Node::Connect(five,ten,0);
    Node::Connect(twentyfive,ten,0);
    Node::Connect(twentyfive,twentythree,0);
    Node::Connect(eleven,three,0);
    Node::Connect(three,ten,0);
    Node::Connect(ten,fifteen,0);
    Node::Connect(twentythree,twelve,0);

    vector<Node> nodes{one,two,three,four,five,six,seven,eight,nine,ten,eleven,
                       twelve,thirteen,fourteen,fifteen,sixteen,seventeen,eighteen,
                       nineteen,twenty,twentyone,twentytwo,twentythree,twentyfour,
                       twentyfive};
    
    
    bestpath = Node::FindBestPath(fourteen.id, twentytwo.id, nodes);


    //spawn nodes and create random connections
    /*
    for (size_t i = 0; i < ammount; i++)
    {
        Node newNode;
        newNode.label = to_string(newNode.id);
        nodes.push_back(newNode);
    }
    for (vector<Node>::iterator it = nodes.begin(); it != nodes.end();it++) {
        
        CC.InsertChartNode(&(*it));
    }

    const int numconnection = 30;
    for (size_t i = 0; i < numconnection; i++)
    {
        int a = (rand() % ammount);
        int b = (rand() % ammount);
        Node::Connect(nodes.at(a), nodes.at(b), 0);
        CC.UpdateConnectionNode(nodes.at(a), nodes.at(b), 0);
    }
    

    CC.Commit();
    //vector<Node> result = Node::FindBestPath(0, 1, nodes);

    /*
    for (vector<Node>::iterator it = result.begin(); it != result.end(); it++) {
        cout << (*it).label << endl;
    }
    */
 
}


