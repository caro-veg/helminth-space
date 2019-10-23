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
    void findNodesWithinRadius(shared_ptr<Node> _focus, shared_ptr<Node> _comp, double _radius, vector<shared_ptr<Node> > &_nodes);
    int nodeNumber;

    void printTree(shared_ptr<Node> _root, int _level);

public:
    KDTree();
    ~KDTree();

    void setRoot(shared_ptr<Node> _root);

    shared_ptr<Node> makeTree(Graph &_g);
    void linkParents(shared_ptr<Node> _root);
    void findNodesWithinRadius(shared_ptr<Node> _focus, double _radius, vector<shared_ptr<Node> > &_nodes);

    shared_ptr<Node> getRoot();
    int getNodeNumber();
    void printTree();
};

#endif // KDTREE_H_INCLUDED
