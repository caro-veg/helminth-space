#include <iostream>
#include "KDTree.h"
#include "Utility_Functions.h"

using namespace std;


KDTree::KDTree() {}

KDTree::~KDTree() {}


shared_ptr<Node> KDTree::makeTree(vector<shared_ptr<Node> > _nodes, int _dim, int _k)
{
    if(_nodes.size()==0)
        return shared_ptr<Node>();
    if(_nodes.size()==1)
        return _nodes.at(0);

    //initial dimension passed should be 0
    int dim = _dim;

    shared_ptr<Node> node;

    //recursively find median in each new partition of node vector
    //alternate between dimensions 0 and 1
    if(node = findMedian(_nodes, dim))
    {
        dim = (dim + 1) % _k;
        vector<shared_ptr<Node> >::const_iterator first = _nodes.begin();
        vector<shared_ptr<Node> >::const_iterator median = _nodes.begin() + _nodes.size()/2;
        vector<shared_ptr<Node> >::const_iterator last = _nodes.end();
        vector<shared_ptr<Node> > leftNodes(first, median);
        vector<shared_ptr<Node> > rightNodes(median+1, last);
        node->setLeft(makeTree(leftNodes, dim, _k));
        node->setRight(makeTree(rightNodes, dim, _k));
    }

    return n;
}
