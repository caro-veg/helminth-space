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
    int position = _g.getNodeVector().at(nodeNumber)->getCellNumber();
    //cout << "Old position " << position << endl;
    //cout << "Old cell " << gridCoords.at(0) << " " << gridCoords.at(1) << endl;

    int columns = _og.getColumns();
    int rows = _og.getRows();

    //draw from multinomial distribution to determine which cell in grid person moves to
    //use distances from cell position (one row)
    vector<double> cellHazards = _og.getHazards().at(position);
    for(unsigned i=0; i<cellHazards.size(); ++i)
    {
        cellHazards.at(i) = cellHazards.at(i) * _og.getK() / _og.getW().at(nodeNumber);
    }
    //set hazard of moving to current cell to 0 --> accounted for by the non-event happens
    //cellHazards.at(position) = cellHazards.at(position) / _og.getNodesByCells().at(position/columns).at(position%columns).size() * (_og.getNodesByCells().at(position/columns).at(position%columns).size() - 1);
    discrete_distribution<int> discDist1(cellHazards.begin(), cellHazards.end());
    int newCellNumber = discDist1(_generator);

    //MultinomialDistribution mn1(_og.getHazards().at(position));
    //uniform_real_distribution<double> unifDist1(0.0, *max_element(mn1.getProbabilities().begin(), mn1.getProbabilities().end()));
    //double u = unifDist1(_generator);
    //cout << "u " << u << endl;
    //int newCellNumber = mn1.bisection(0, _og.getHazards().at(position).size()-1, u);
    double totalCellHazard = cellHazards.at(newCellNumber);
    int newColumn = newCellNumber % columns;
    int newRow = newCellNumber / columns;
    //cout << newCellNumber << endl;
    //cout << "target cell: " << newRow << " " << newColumn << endl << endl;

    //relocate to one of the nodes in the chosen cell
    vector<shared_ptr<Node> > targetNodes = _og.getNodesByCells().at(newRow).at(newColumn);

    if(targetNodes.size() > 0)
    {
        vector<double> nodeHazards;
        nodeHazards.reserve(targetNodes.size() - 1);

        double sumNodeHazards = 0;
        for(unsigned i=0; i<targetNodes.size(); ++i)
        {
            if(targetNodes.at(i)->getNodeNumber() != nodeNumber)
            {
                double temp = (targetNodes.at(i)->getCoordinates().at(0) - _g.getNodeVector().at(nodeNumber)->getCoordinates().at(0)) * (targetNodes.at(i)->getCoordinates().at(0) - _g.getNodeVector().at(nodeNumber)->getCoordinates().at(0))
                            + (targetNodes.at(i)->getCoordinates().at(1) - _g.getNodeVector().at(nodeNumber)->getCoordinates().at(1)) * (targetNodes.at(i)->getCoordinates().at(1) - _g.getNodeVector().at(nodeNumber)->getCoordinates().at(1));

                double distance = sqrt(temp);
                double nodeHazard = 1 + distance / _alpha;
                nodeHazard = pow(nodeHazard, -_gamma);
                //cout << "node hazard: " << nodeHazard << endl;
                nodeHazard = nodeHazard * _og.getK() / _og.getW().at(nodeNumber);
                //cout << "K " << _og.getK() << " W " << _og.getW().at(nodeNumber) << endl;
                //cout << "node hazard: " << nodeHazard << endl;
                nodeHazards.push_back(nodeHazard);

                //cout << distance << " " << nodeHazard << " " << sumNodeHazards << endl;

                sumNodeHazards = sumNodeHazards + nodeHazard;
            }
            else
                nodeHazards.push_back(0);
        }
        nodeHazards.push_back(totalCellHazard - sumNodeHazards);
        //cout << totalCellHazard << " " << sumNodeHazards << " " << totalCellHazard - sumNodeHazards << endl << endl;

        discrete_distribution<int> discDist2(nodeHazards.begin(), nodeHazards.end());
        int n = discDist2(_generator);
        //MultinomialDistribution mn2(probabilities);
        //uniform_real_distribution<double> unifDist2(0.0, *max_element(mn2.getProbabilities().begin(), mn2.getProbabilities().end()));
        //u = unifDist2(_generator);
        //cout << "u " << u << endl;
        //int n = mn2.bisection(0, probabilities.size(), u);
        if(n < targetNodes.size())
        {
            int newNodeNumber = targetNodes.at(n)->getNodeNumber();
            //cout << "New Node: " << n << endl << endl;
            setNodeNumber(newNodeNumber);
        }

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
