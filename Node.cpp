#include <iostream>
#include "Node.h"

using namespace std;

Node::Node() : fitness(1), left(nullptr), right(nullptr), parent(nullptr)
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
    //cout << _node->getCoordinates().at(0) << " " << _node->getCoordinates().at(1) << endl;
    left = _node;
    //cout << "dddd" << endl;
}

void Node::setRight(shared_ptr<Node> _node)
{
    right = _node;
}

void Node::setParent(shared_ptr<Node> _node)
{
    parent = _node;
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

shared_ptr<Node> Node::getParent()
{
    return parent;
}
