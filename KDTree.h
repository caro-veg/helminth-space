#ifndef KDTREE_H_INCLUDED
#define KDTREE_H_INCLUDED

#include <vector>
#include <memory>
#include "Graph.h"

using std::vector;
using std::shared_ptr;

class KDTree
{
private:
    shared_ptr<Node> root;

    shared_ptr<Node> makeTree(vector<shared_ptr<Node> > &_nodes, int _dim, int _k);

    int nodeNumber;

public:
    KDTree();
    ~KDTree();

    void setRoot(shared_ptr<Node> _root);

    shared_ptr<Node> makeTree(Graph &_g);
    vector<shared_ptr<Node> > findNearestN(int _N) const;    //find N nearest neighbours
    vector<shared_ptr<Node> > findNodesWithinRadius(double _radius) const;

    shared_ptr<Node> getRoot();
    int getNodeNumber();
    void printTree(shared_ptr<Node> _root, int _level);
};

#endif // KDTREE_H_INCLUDED
