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


void Person::relocate(mt19937_64 _generator)
{
    vector<double> probabilities;
    probabilities.reserve(graph.getNodeVector().size()-1);
    //calculate probabilities to move to each node
    cout << "hello" << endl;
    for(unsigned i=0; i<graph.getNodeVector().size(); ++i)
    {
        if(i != nodeNumber)
        {
            cout << "hello" << endl;
            //calculate distances between current node and each other node in network
            double temp = (graph.getNodeVector().at(nodeNumber)->getCoordinates().at(0) - graph.getNodeVector().at(i)->getCoordinates().at(0)) * (graph.getNodeVector().at(nodeNumber)->getCoordinates().at(0) - graph.getNodeVector().at(i)->getCoordinates().at(0))
            + (graph.getNodeVector().at(nodeNumber)->getCoordinates().at(1) - graph.getNodeVector().at(i)->getCoordinates().at(1)) * (graph.getNodeVector().at(nodeNumber)->getCoordinates().at(1) - graph.getNodeVector().at(i)->getCoordinates().at(1));
            cout << "hello" << endl;
            double distance = sqrt(temp);
            double probability = graph.getNodeVector().at(i)->getFitness() * exp(-distance/predisposition) / (predisposition * graph.getNodeVector().size()-1);
            probabilities.push_back(probability);
        }
    }
    for(double x:probabilities) cout << x << " ";

    //draw from multinomial distribution to determine which node person moves to
    discrete_distribution<int> discDist(probabilities.begin(), probabilities.end());
    for(double x:discDist.probabilities()) cout << x << " ";
    cout << endl;

    int newNodeNumber = 9; //discDist(_generator);

    nodeNumber = newNodeNumber;
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

double Person::getPredisposition()
{
    return predisposition;
}

bool Person::getAlive()
{
    return alive;
}
