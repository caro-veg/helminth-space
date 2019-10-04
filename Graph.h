#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <memory>
#include <random>
#include "Node.h"

using std::vector;
using std::shared_ptr;
using std::mt19937_64;


class Graph
{
private:
    vector<shared_ptr<Node> > nodeVector;


public:
    //constructs nodes, but not connections - need to be set separately
    Graph();
    ~Graph();

    //create _N nodes without properties
    void createNodes(int _N);

    //distribute nodes according to defined coordinates, e.g. read from file
    //requires that nodes are already created
    void setNodeCoordinates(vector<vector<double> > _coordinates);
    //distribute nodes according to Poisson distribution: number of nodes grows linearly with distance
    //from centre node
    void setNodeCoordinatesPoisson(double _mean, double _maxRadius, double _n, mt19937_64 _generator);

    void setNodeFitness(vector<double> _fitnesses);

    vector<double> calculateDistances();

    vector<shared_ptr<Node> > &getNodeVector();

};

#endif // GRAPH_H_INCLUDED
