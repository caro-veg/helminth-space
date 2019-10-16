#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cmath>
#include "Person.h"

using namespace std;


Person::Person(Graph &_graph) : graph(_graph), nodeNumber(0), coordinates(), movementRate(0), predisposition(1), age(0), parasites(0), femaleParasites(0), alive(true)
{
    coordinates.reserve(2);

    srand(time(NULL));
    if(rand() % 100 < 50)
        sex = female;
    else
        sex = male;
}


Person::~Person()
{

}


void Person::setNodeNumber(int _nodeNumber)
{
        nodeNumber = _nodeNumber;
        coordinates = graph.getNodeVector().at(nodeNumber)->getCoordinates();
}

void Person::setCoordinates(vector<double> _coordinates)
{
    coordinates = _coordinates;
}

void Person::setPredisposition(double _predisposition)
{
    predisposition = _predisposition;
}

void Person::setMovementRate(double _movementRate)
{
    movementRate = _movementRate;
}


void Person::relocate(mt19937_64 _generator)    //generalize so that this can be used as part of rejection algorithm or KD-tree --> pass vector of relevant nodes in
{                                               //and probability function to use: exponential or power low
    vector<double> probabilities;
    probabilities.reserve(graph.getNodeVector().size()-1);
    //calculate probabilities to move to each node

    for(unsigned i=0; i<graph.getNodeVector().size(); ++i)
    {
        if(i != nodeNumber)
        {
            //calculate distances between current node and each other node in network
            double temp = (graph.getNodeVector().at(nodeNumber)->getCoordinates().at(0) - graph.getNodeVector().at(i)->getCoordinates().at(0)) * (graph.getNodeVector().at(nodeNumber)->getCoordinates().at(0) - graph.getNodeVector().at(i)->getCoordinates().at(0))
            + (graph.getNodeVector().at(nodeNumber)->getCoordinates().at(1) - graph.getNodeVector().at(i)->getCoordinates().at(1)) * (graph.getNodeVector().at(nodeNumber)->getCoordinates().at(1) - graph.getNodeVector().at(i)->getCoordinates().at(1));

            double distance = sqrt(temp);
            double probability = graph.getNodeVector().at(i)->getFitness() * exp(-distance/predisposition) / predisposition;
            probabilities.push_back(probability);
        }
        else
            probabilities.push_back(0);
    }
    //for(double x:probabilities) cout << x << " ";
    //cout << endl;

    //probabilities.at(nodeNumber) = 0;

    //draw from multinomial distribution to determine which node person moves to
    discrete_distribution<int> discDist(probabilities.begin(), probabilities.end());
    //for(double x:discDist.probabilities()) cout << x << " ";
    //cout << endl;

    //cout << nodeNumber << endl;
    int newNodeNumber = discDist(_generator);
    setNodeNumber(newNodeNumber);
}


void Person::relocateRejection(mt19937_64 _generator, Graph &_g, OverlayGrid &_og, double _alpha, double _gamma)
{
    //determine position relative to overlay grid
    vector<int> gridCoords = _g.getNodeVector().at(nodeNumber)->getCellCoordinates();
    int xCells = _og.getXCells();
    int yCells = _og.getYCells();
    int position = gridCoords.at(0) * yCells + gridCoords.at(1);

    //draw from multinomial distribution to determine which cell in grid person moves to
    //use distances from cell position (one row)
    discrete_distribution<int> discDist1(_og.getHazards().at(position).begin(), _og.getHazards().at(position).end());
    int newCellNumber = discDist1(_generator);
    int newCellX = newCellNumber / yCells;
    int newCellY = newCellNumber % yCells;

    newCellX = 2; newCellY = 0;
    //calculate distance from current node to all nodes in new cell
    vector<shared_ptr<Node> > targetNodes = _og.getNodesByCells().at(newCellX).at(newCellY);

    if(targetNodes.size() > 0)
    {
        vector<double> probabilities;
        probabilities.reserve(targetNodes.size() - 1);

        for(unsigned i=0; i<targetNodes.size(); ++i)
        {
            if(i != nodeNumber)
            {
                double temp = (targetNodes.at(i)->getCoordinates().at(0) - _g.getNodeVector().at(nodeNumber)->getCoordinates().at(0)) * (targetNodes.at(i)->getCoordinates().at(0) - _g.getNodeVector().at(nodeNumber)->getCoordinates().at(0))
                            + (targetNodes.at(i)->getCoordinates().at(1) - _g.getNodeVector().at(nodeNumber)->getCoordinates().at(1)) * (targetNodes.at(i)->getCoordinates().at(1) - _g.getNodeVector().at(nodeNumber)->getCoordinates().at(1));

                double distance = sqrt(temp);
                double probability = 1 + distance / _alpha;
                probability = pow(probability, -_gamma);
                probabilities.push_back(probability);
            }
            else
                probabilities.push_back(0);
        }

        discrete_distribution<int> discDist2(probabilities.begin(), probabilities.end());
        int n = discDist2(_generator);
        int newNodeNumber = targetNodes.at(n)->getNodeNumber();
        setNodeNumber(newNodeNumber);
    }
}


void Person::aging(double _ageInterval)
{
    age +=_ageInterval;
}


void Person::die()
{

}


void Person::setParasites(int _parasites)
{
    parasites = _parasites;
}

void Person::setFemaleParasites(int _femaleParasites)
{
    femaleParasites = _femaleParasites;
}


int Person::getNodeNumber()
{
    return nodeNumber;
}

vector<double> Person::getCoordinates()
{
    return coordinates;
}


double Person::getAge()
{
    return age;
}

sex_enum Person::getSex()
{
    return sex;
}


int Person::getParasites()
{
    return parasites;
}

int Person::getFemaleParasites()
{
    return femaleParasites;
}

double Person::getMovementRate()
{
    return movementRate;
}

double Person::getPredisposition()
{
    return predisposition;
}

bool Person::getAlive()
{
    return alive;
}
