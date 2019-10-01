#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <memory>
#include "Node.h"

using std::vector;
using std::shared_ptr;


class Graph
{
private:
    vector<shared_ptr<Node> > nodeVector;


public:
    //constructs nodes, but not connections - need to be set separately
    Graph(int _N);
    ~Graph();

    void setNodeCoordinates(vector<vector<double> > _coordinates);
    void setNodeFitness(vector<double> _fitnesses);

    vector<shared_ptr<Node> > &getNodeVector();

};

#endif // GRAPH_H_INCLUDED
