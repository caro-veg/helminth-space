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
    return makeTree(_g.getNodeVector(), 0, 2, 0);
}

shared_ptr<Node> KDTree::makeTree(vector<shared_ptr<Node> > &_nodes, int _dim, int _k, int _direction)
{

    if(_nodes.size()==0)
        return nullptr;

    nodeNumber++;

    //initial dimension passed should be 0
    int dim = _dim;

    //recursively find median in each new partition of node vector
    //alternate between dimensions 0 and 1
    shared_ptr<Node> node = findMedian(_nodes, dim);
    node->setDimension(dim);
    node->setDirection(_direction);
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

        node->setLeft(makeTree(leftNodes, dim, _k, 1));
        node->setRight(makeTree(rightNodes, dim, _k, 2));

        //left->setParent(node);
        //cout << "hello" << endl;
        //node->getRight()->setParent(node);

        //if(node->getLeft()!=nullptr) cout << node->getLeft()->getCoordinates().at(0) << " " << node->getLeft()->getCoordinates().at(1) << endl;
        //if(node->getRight()!=nullptr) cout << node->getRight()->getCoordinates().at(0) << " " << node->getRight()->getCoordinates().at(1) << endl;
    }

    return node;
}

void KDTree::linkParents(shared_ptr<Node> _root)
{
    if(_root!=nullptr)
    {
        if(_root->getLeft()!=nullptr)
            _root->getLeft()->setParent(_root);
        if(_root->getRight()!=nullptr)
            _root->getRight()->setParent(_root);

        linkParents(_root->getLeft());
        linkParents(_root->getRight());
    }
}


void KDTree::findNodesWithinRadius(shared_ptr<Node> _focus, double _radius, vector<shared_ptr<Node> > &_nodes)
{
    if(_focus==nullptr)
        return;

    shared_ptr<Node> node = _focus->getParent();
    while(node != nullptr)
    {
        double distance;
        distance = calculateDistance(_focus, node);
        if(distance <= _radius)
        {
            _nodes.push_back(node);
        }

        shared_ptr<Node> parent = node->getParent();
        //cout << "length of target vector 1: " << _nodes.size() << endl;
        if(abs(_focus->getCoordinates().at(node->getDimension()) - node->getCoordinates().at(node->getDimension())) <= _radius)
        {
            if(node->getDirection() == 1)
            {
                //cout << "left" << endl;
                findNodesWithinRadius(_focus, node->getLeft(), _radius, _nodes);
            }

            else if(node->getDirection() == 2)
            {
                //cout << "right" << endl;
                findNodesWithinRadius(_focus, node->getRight(), _radius, _nodes);
            }
        }
        //cout << "length of target vector 2: " << _nodes.size() << endl;
        node = parent;
    }

    findNodesWithinRadius(_focus, _focus->getLeft(), _radius, _nodes);
    findNodesWithinRadius(_focus, _focus->getRight(), _radius, _nodes);

    //cout << _nodes.size() << endl;

}


void KDTree::findNodesWithinRadius(shared_ptr<Node> _focus, shared_ptr<Node> _comp, double _radius, vector<shared_ptr<Node> > &_nodes)
{
    if(_focus==nullptr || _comp==nullptr)
        return;

    //cout << "length of target vector 3: " << _nodes.size() << endl;
    if(_focus!=_comp)
    {
        double distance = calculateDistance(_focus, _comp);
        if(distance <= _radius)
        {
            //cout << distance << " " << _radius << endl;
            //cout << _focus->getCoordinates().at(0) << " " << _focus->getCoordinates().at(1) << endl;
            //cout << _comp->getCoordinates().at(0) << " " << _comp->getCoordinates().at(1) << endl;
            _nodes.push_back(_comp);
            //cout << _nodes.at(_nodes.size()-1)->getCoordinates().at(0) << " " << _nodes.at(_nodes.size()-1)->getCoordinates().at(1) << endl;
        }
    }

    findNodesWithinRadius(_focus, _comp->getLeft(), _radius, _nodes);
    findNodesWithinRadius(_focus, _comp->getRight(), _radius, _nodes);
    //cout << "length of target vector 4: " << _nodes.size() << endl;
}


void KDTree::findNodesWithinRadius2(shared_ptr<Node> _focus, double _radius, vector<shared_ptr<Node> > &_nodes)
{
    findNodesWithinRadius2(_focus, root, _radius, _nodes);
}


void KDTree::findNodesWithinRadius2(shared_ptr<Node> _focus, shared_ptr<Node> _comp, double _radius, vector<shared_ptr<Node> > &_nodes)
{
    if(_focus==nullptr || _comp==nullptr)
        return;
    if(_focus!=_comp)
    {
        double distance = calculateDistance(_focus, _comp);
        //if(distance <= _radius)
        {
            _nodes.push_back(_comp);
            //cout << _comp->getCoordinates().at(0) << " " << _comp->getCoordinates().at(1) << endl;

        }
    }

    findNodesWithinRadius2(_focus, _comp->getLeft(), _radius, _nodes);
    findNodesWithinRadius2(_focus, _comp->getRight(), _radius, _nodes);
}


shared_ptr<Node> KDTree::getRoot()
{
    return root;
}

int KDTree::getNodeNumber()
{
    return nodeNumber;
}

void KDTree::printTree()
{
    printTree(root, 0);
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
