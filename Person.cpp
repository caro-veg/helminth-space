#include <iostream>
#include <time.h>
#include <cstdlib>
#include <cmath>
#include "Person.h"
#include "MultinomialDistribution.h"

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

void Person::setNodeNumberOnly(int _nodeNumber)
{
    nodeNumber = _nodeNumber;
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


void Person::relocate(mt19937_64 &_generator)    //generalize so that this can be used as part of rejection algorithm or KD-tree --> pass vector of relevant nodes in
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


void Person::relocate(mt19937_64 &_generator, vector<shared_ptr<Node> > _targetNodes)
{
    vector<double> probabilities;
    //cout << "Number of target nodes: " << _targetNodes.size() << endl;
    if(_targetNodes.size() > 0)
    {
        probabilities.reserve(_targetNodes.size()-1);
    //calculate probabilities to move to each node

        for(unsigned i=0; i<_targetNodes.size(); ++i)
        {
            if(i != nodeNumber)
            {
                //calculate distances between current node and each other node in network
                double temp = (getCoordinates().at(0) - _targetNodes.at(i)->getCoordinates().at(0)) * (getCoordinates().at(0) - _targetNodes.at(i)->getCoordinates().at(0))
                + (getCoordinates().at(1) - _targetNodes.at(i)->getCoordinates().at(1)) * (getCoordinates().at(1) - _targetNodes.at(i)->getCoordinates().at(1));
                double distance = sqrt(temp);
                double probability = _targetNodes.at(i)->getFitness() * exp(-distance/predisposition) / predisposition;
                probabilities.push_back(probability);
            }
            else
                probabilities.push_back(0);

        }
        //for(double x:probabilities) cout << x << " ";
        //cout << endl;

        //draw from multinomial distribution to determine which node person moves to
        discrete_distribution<int> discDist(probabilities.begin(), probabilities.end());
        //for(double x:discDist.probabilities()) cout << x << " ";
        //cout << endl;

        //cout << nodeNumber << endl;
        int n = discDist(_generator);
        //cout << "n " << n << endl;
        //cout << _targetNodes.at(n)->getCoordinates().at(0) << " " << _targetNodes.at(n)->getCoordinates().at(1) << endl;
        int newNodeNumber = _targetNodes.at(n)->getNodeNumber();
        //cout << newNodeNumber << endl;
        setNodeNumberOnly(newNodeNumber);
        //cout << nodeNumber << endl;
        setCoordinates(_targetNodes.at(n)->getCoordinates());
    }
}


void Person::relocate(mt19937_64 &_generator, Graph &_g, KDTree &_kd, double _cutOffRadius)
{
    //determine position in tree
    shared_ptr<Node> focus = _g.getNodeVector().at(nodeNumber);
    vector<shared_ptr<Node> > targetNodes;

    //search points within cut-off radius (KD tree function)
    _kd.findNodesWithinRadius(focus, _cutOffRadius, targetNodes);
    //cout << endl << "Target nodes: " << endl;
    //for(unsigned i=0; i<targetNodes.size(); ++i)
    //    cout << targetNodes.at(i)->getCoordinates().at(0) << " " << targetNodes.at(i)->getCoordinates().at(1) << endl;
    //cout << endl;
    //pass points to relocate function --> choose which of these points to move to
    relocate(_generator, targetNodes);
}


void Person::relocate(mt19937_64 &_generator, Graph &_g, OverlayGrid &_og, double _alpha, double _gamma)
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

    //MultinomialDistribution mn1(_og.getHazards().at(position));
    //uniform_real_distribution<double> unifDist1(0.0, *max_element(mn1.getProbabilities().begin(), mn1.getProbabilities().end()));
    //double u = unifDist1(_generator);
    //cout << "u " << u << endl;
    //int newCellNumber = mn1.bisection(0, _og.getHazards().at(position).size()-1, u);
    //cout << "New cell " << newCellNumber << endl << endl;
    //for(double x:_og.getHazards().at(position)) cout << x << " ";
    //cout << endl;
    int newCellX = newCellNumber / yCells;
    int newCellY = newCellNumber % yCells;

    //cout << "target cell: " << newCellX << " " << newCellY << endl;

    //relocate to one of the nodes in the chosen cell
    vector<shared_ptr<Node> > targetNodes = _og.getNodesByCells().at(newCellX).at(newCellY);

    if(targetNodes.size() > 0)
    {
        vector<double> probabilities;
        probabilities.reserve(targetNodes.size() - 1);

        for(unsigned i=0; i<targetNodes.size(); ++i)
        {
            if(targetNodes.at(i)->getNodeNumber() != nodeNumber)
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
        //for(double x:probabilities) cout << x << " ";
        //cout << endl;

        discrete_distribution<int> discDist2(probabilities.begin(), probabilities.end());
        int n = discDist2(_generator);
        //MultinomialDistribution mn2(probabilities);
        //uniform_real_distribution<double> unifDist2(0.0, *max_element(mn2.getProbabilities().begin(), mn2.getProbabilities().end()));
        //u = unifDist2(_generator);
        //cout << "u " << u << endl;
        //int n = mn2.bisection(0, probabilities.size(), u);
        int newNodeNumber = targetNodes.at(n)->getNodeNumber();
        //cout << "New Node: " << n << endl << endl;
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
