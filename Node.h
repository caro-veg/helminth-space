#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <memory>
#include <vector>

using std::vector;
using std::shared_ptr;

class Node
{
private:
    vector<double> coordinates;   //spatial coordinates
    int nodeNumber; //needed as accessory variable in rejection algorithm
    double fitness; //node fitness: "attraction" of location for people

    //needed for rejection algorithm and super-node kd-tree
    vector<int> cellCoordinates;

    //needed for kd-tree
    shared_ptr<Node> left, right, parent;
    int dimension;  // does node split tree with regards to x or y coordinate?
    int direction;  // direction of node relative to parent: 0 - none (root node), 1 - left, 2 - right


public:
    Node();
    ~Node();

    void setCoordinates(vector<double> _coordinates);
    void setNodeNumber(int _nodeNumber);
    void setFitness(double _fitness);
    void setCellCoordinates(vector<int> _cellCoordinates);
    void setLeft(shared_ptr<Node> _node);
    void setRight(shared_ptr<Node> _node);
    void setParent(shared_ptr<Node> _node);
    void setDimension(int _dimension);
    void setDirection(int _direction);

    vector<double> getCoordinates();
    int getNodeNumber();
    double getFitness();
    vector<int> getCellCoordinates();
    shared_ptr<Node> getLeft();
    shared_ptr<Node> getRight();
    shared_ptr<Node> getParent();
    int getDimension();
    int getDirection();
};

#endif // NODE_H_INCLUDED
