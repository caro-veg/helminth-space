#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <memory>
#include <map>
#include <tuple>
#include "Node.h"

using std::vector;
using std::shared_ptr;
using std::map;
using std::tuple;

class Graph
{
private:
    vector<shared_ptr<Node> > nodeVector;
    //list of links between nodes
    vector<vector<int> > adjacencyList;
    //map to store edge connections and distance
    map<pair<int, int>, double> linkMap;

public:
    //constructs nodes and connections between them
    Graph(vector<tuple<int, int, double> > &_connections, int _N);
    //constructs nodes, but not connections - need to be set separately
    Graph(int _N);
    ~Graph();

    //make connection between nodes
    void linkNodes(vector<tuple<int, int, double> > &_connections);
    //function to generate graph with grid topology
    void makeGrid(int _gridLength);
    //function to generate adjacency matrices at random


    vector<shared_ptr<Node> > &getNodeVector();
    map<pair<int, int>, double> const &getLinkMap();
    void printLinkMap();
};

#endif // GRAPH_H_INCLUDED
