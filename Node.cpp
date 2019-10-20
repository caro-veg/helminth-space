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

void Node::setLeft(shared_ptr<Node> _node)
{
    left = _node;
}

void Node::setRight(shared_ptr<Node> _node)
{
    right = _node;
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

shared_ptr<Node> Node::getLeft()
{
    return left;
}

shared_ptr<Node> Node::getRight()
{
    return right;
}
