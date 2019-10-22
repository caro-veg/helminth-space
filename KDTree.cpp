#include <iostream>
#include "KDTree.h"
#include "Utility_Functions.h"

using namespace std;


KDTree::KDTree() : nodeNumber(0)
{
}

KDTree::~KDTree() {}


void KDTree::setRoot(shared_ptr<Node> _root)
{
    root = _root;
}

shared_ptr<Node> KDTree::makeTree(Graph &_g)
{
    return makeTree(_g.getNodeVector(), 0, 2);
}

shared_ptr<Node> KDTree::makeTree(vector<shared_ptr<Node> > &_nodes, int _dim, int _k)
{

    if(_nodes.size()==0)
        return nullptr;

    nodeNumber++;

    //initial dimension passed should be 0
    int dim = _dim;

    shared_ptr<Node> node;

    //recursively find median in each new partition of node vector
    //alternate between dimensions 0 and 1
    node = findMedian(_nodes, dim);
    dim = (dim + 1) % _k;
    vector<shared_ptr<Node> >::const_iterator first = _nodes.begin();
    vector<shared_ptr<Node> >::const_iterator median = _nodes.begin() + _nodes.size()/2;
    vector<shared_ptr<Node> >::const_iterator last = _nodes.end();
    //cout << endl << endl << "Median: " << node->getCoordinates().at(0) << " " << node->getCoordinates().at(1) << endl;
    if(node != nullptr)
    {
        vector<shared_ptr<Node> > leftNodes(first, median);
        vector<shared_ptr<Node> > rightNodes(median+1, last);

        /*for(int i=0; i<leftNodes.size(); ++i)
        {
            cout << "left " << i << " " << leftNodes.at(i)->getCoordinates().at(0) << " " << leftNodes.at(i)->getCoordinates().at(1) << endl;
        }
        cout << endl;
        for(int i=0; i<rightNodes.size(); ++i)
        {
            cout << "right " << i << " " << rightNodes.at(i)->getCoordinates().at(0) << " " << rightNodes.at(i)->getCoordinates().at(1) << endl;
        }*/

        node->setLeft(makeTree(leftNodes, dim, _k));
        node->setRight(makeTree(rightNodes, dim, _k));

        //if(node->getLeft()!=nullptr) cout << node->getLeft()->getCoordinates().at(0) << " " << node->getLeft()->getCoordinates().at(1) << endl;
        //if(node->getRight()!=nullptr) cout << node->getRight()->getCoordinates().at(0) << " " << node->getRight()->getCoordinates().at(1) << endl;
    }

    return node;
}


shared_ptr<Node> KDTree::getRoot()
{
    return root;
}

int KDTree::getNodeNumber()
{
    return nodeNumber;
}


void KDTree::printTree(shared_ptr<Node> _root, int _level)
{
    if(_root!=nullptr)
    {
        cout << "Level: " << _level << " " << _root->getCoordinates().at(0) << " " << _root->getCoordinates().at(1) << endl;
        _level += 1;
        if(_root->getLeft()!=nullptr)// &&_root->getRight()!=nullptr)
        printTree(_root->getLeft(), _level);
        if(_root->getRight()!=nullptr)
        printTree(_root->getRight(), _level);
    }
}
