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

    shared_ptr<Node> makeTree(vector<shared_ptr<Node> > _nodes, int _dim, int _k);


public:
    KDTree();
    ~KDTree();

    //void makeTree(Graph &_g, int _index, int _k);
    vector<shared_ptr<Node> > findNearestN(int _N) const;    //find N nearest neighbours
    vector<shared_ptr<Node> > findNodesWithinRadius(double _radius) const;
};

#endif // KDTREE_H_INCLUDED
