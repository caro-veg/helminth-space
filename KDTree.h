#ifndef KDTREE_H_INCLUDED
#define KDTREE_H_INCLUDED

#include <vector>
#include <memory>
#include "Graph.h"
#include "Node.h"

class KDTree
{
private:
    shared_ptr<Node> root;


public:
    KDTree();
    ~KDTree();

    void makeTree(Graph &_g, int _index, int _dimensions);
    void findNearestN(int _N) const;    //find N nearest neighbours
    void findNodesWithinRadius(double _radius) const;
};

#endif // KDTREE_H_INCLUDED
