#include <iostream>
#include "Node.h"

using namespace std;

Node::Node() : occupied(false)
{

}

Node::~Node() {}


void Node::setNumber(int _number)
{
    number = _number;
}


void Node::addDestinationNode(shared_ptr<Node> _node, double _distance)
{
    pair<shared_ptr<Node>, double> connection(_node, _distance);
    destinationNodes.push_back(connection);
}


void Node::setOccupied(bool _occupied)
{
    occupied = _occupied;
}


int Node::getNumber()
{
    return number;
}


vector<pair<shared_ptr<Node>, double> > Node::getDestinationNodes()
{
    return destinationNodes;
}


bool Node::getOccupied()
{
    return occupied;
}
