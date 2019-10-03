#include <iostream>
#include "Node.h"

using namespace std;

Node::Node() : fitness(1)
{

}

Node::~Node() {}


void Node::setCoordinates(vector<double> _coordinates)
{
    coordinates = _coordinates;
}

void Node::setFitness(double _fitness)
{
    fitness = _fitness;
}

vector<double> Node::getCoordinates()
{
    return coordinates;
}

double Node::getFitness()
{
    return fitness;
}

