#include <iostream>
#include <cmath>
#include "Graph.h"

using namespace std;


Graph::Graph() {}


Graph::~Graph() { }


void Graph::createNodes(int _N)
{
    nodeVector.reserve(_N);
    for(int i=0; i<_N; ++i)
    {
        nodeVector.push_back(shared_ptr<Node> (new Node()));
    }

}


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


void Graph::setNodeCoordinatesPoisson(double _mean, double _maxRadius, double _n, mt19937_64 _generator)
{
    nodeVector.push_back(shared_ptr<Node> (new Node()));
    nodeVector.at(0)->setCoordinates(vector<double> {0,0});

    double deltaR = _maxRadius / _n;

    poisson_distribution<int> poissonDist(_mean);
    uniform_real_distribution<double> unifDist360(0, 360);
    uniform_real_distribution<double> unifDistDeltaR(0, deltaR);

    for(int i=1; i<(_n-1); ++i)
    {
        double r1 = i * deltaR;
        int deltaNodes = poissonDist(_generator);

        for(int j=0; j<deltaNodes; ++j)
        {
            nodeVector.push_back(shared_ptr<Node> (new Node()));
            double phi = unifDist360(_generator);
            double delta = unifDistDeltaR(_generator);
            double r = r1 + delta;
            double x = r * cos(phi);
            double y = r * sin(phi);
            nodeVector.back()->setCoordinates(vector<double> {x, y});
        }
    }
}


void Graph::setNodeNumbers()
{
    for(int i=0; i<nodeVector.size(); ++i)
        nodeVector.at(i)->setNodeNumber(i);
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


vector<double> Graph::calculateDistances()
{
    vector<double> distances;
    for(unsigned i=0; i<nodeVector.size(); ++i)
    {
        double temp = (nodeVector.at(0)->getCoordinates().at(0) - nodeVector.at(i)->getCoordinates().at(0)) * (nodeVector.at(0)->getCoordinates().at(0) - nodeVector.at(i)->getCoordinates().at(0))
                        + (nodeVector.at(0)->getCoordinates().at(1) - nodeVector.at(i)->getCoordinates().at(1)) * (nodeVector.at(0)->getCoordinates().at(1) - nodeVector.at(i)->getCoordinates().at(1));
        double distance = sqrt(temp);
        distances.push_back(distance);
    }

    return(distances);
}


vector<shared_ptr<Node> > &Graph::getNodeVector()
{
    return nodeVector;
}

