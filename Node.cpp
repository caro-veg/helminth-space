#include <iostream>
#include "Node.h"

using namespace std;

Node::Node() : occupied(false)
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

void Node::setOccupied(bool _occupied)
{
    occupied = _occupied;
}


vector<double> Node::getCoordinates()
{
    return coordinates;
}

double Node::getFitness()
{
    return fitness;
}

bool Node::getOccupied()
{
    return occupied;
}
