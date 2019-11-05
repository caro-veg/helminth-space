#include <iostream>
#include "Node.h"

using namespace std;

Node::Node() : nodeNumber(0), fitness(1), cellNumber(0), weight(1), left(nullptr), right(nullptr), parent(nullptr), dimension(0), direction(0)
{

}

Node::~Node() {}


void Node::setCoordinates(vector<double> _coordinates)
{
    coordinates = _coordinates;
}

void Node::setNodeNumber(int _nodeNumber)
{
    nodeNumber = _nodeNumber;
}

void Node::setFitness(double _fitness)
{
    fitness = _fitness;
}

void Node::setCellCoordinates(vector<int> _cellCoordinates)
{
    cellCoordinates = _cellCoordinates;
}

void Node::setCellNumber(int _cellNumber)
{
    cellNumber = _cellNumber;
}

void Node::setWeight(double _weight)
{
    weight = _weight;
}

void Node::setLeft(shared_ptr<Node> _node)
{
    left = _node;
}

void Node::setRight(shared_ptr<Node> _node)
{
    right = _node;
}

void Node::setParent(shared_ptr<Node> _node)
{
    parent = _node;
}

void Node::setDimension(int _dimension)
{
    dimension = _dimension;
}

void Node::setDirection(int _direction)
{
    direction = _direction;
}

vector<double> Node::getCoordinates()
{
    return coordinates;
}

int Node::getNodeNumber()
{
    return nodeNumber;
}

double Node::getFitness()
{
    return fitness;
}

vector<int> Node::getCellCoordinates()
{
    return cellCoordinates;
}

int Node::getCellNumber()
{
    return cellNumber;
}

double Node::getWeight()
{
    return weight;
}

shared_ptr<Node> Node::getLeft()
{
    return left;
}

shared_ptr<Node> Node::getRight()
{
    return right;
}

shared_ptr<Node> Node::getParent()
{
    return parent;
}

int Node::getDimension()
{
    return dimension;
}

int Node::getDirection()
{
    return direction;
}
