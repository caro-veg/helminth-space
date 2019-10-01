#include <iostream>
#include "Graph.h"

using namespace std;


Graph::Graph(int _N)
{
    nodeVector.reserve(_N);
    for(int i=0; i<_N; ++i)
        nodeVector.push_back(shared_ptr<Node> (new Node()));
}


Graph::~Graph() { }


void Graph::setNodeCoordinates(vector<vector<double> > _coordinates)
{
    try
    {
        if(nodeVector.size() != _coordinates.size())
        {
            throw 1;
        }

        for(unsigned i=0; i<nodeVector.size(); ++i)
        {
            nodeVector.at(i)->setCoordinates(_coordinates.at(i));
        }

    }
    catch(const int &e)
    {
        for(unsigned i=0; i<nodeVector.size(); ++i)
        {
            nodeVector.at(i)->setCoordinates(vector<double> {0, 0});
        }
        cout << "the number of coordinate pairs does not equal the number of nodes" << endl;
        cout << "all coordinates have been set to 0" << endl << endl;
    }

}


void Graph::setNodeFitness(vector<double> _fitnesses)
{
    try
    {
        if(nodeVector.size() != _fitnesses.size())
        {
            throw 1;
        }

        for(unsigned i=0; i<nodeVector.size(); ++i)
        {
            nodeVector.at(i)->setFitness(_fitnesses.at(i));
        }
    }
    catch(const int &e)
    {
        for(unsigned i=0; i<nodeVector.size(); ++i)
        {
            nodeVector.at(i)->setFitness(0);
        }
        cout << "the number of fitness values does not equal the number of nodes" << endl;
        cout << "all fitness values have been set to 0" << endl << endl;
    }
}


vector<shared_ptr<Node> > &Graph::getNodeVector()
{
    return nodeVector;
}

