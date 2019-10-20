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

    //needed for rejection algorithm
    vector<int> cellCoordinates;

    //needed for kd-tree
    shared_ptr<Node> left, right;


public:
    Node();
    ~Node();

    void setCoordinates(vector<double> _coordinates);
    void setNodeNumber(int _nodeNumber);
    void setFitness(double _fitness);
    void setCellCoordinates(vector<int> _cellCoordinates);
    void setLeft(shared_ptr<Node> _node);
    void setRight(shared_ptr<Node> _node);

    vector<double> getCoordinates();
    int getNodeNumber();
    double getFitness();
    vector<int> getCellCoordinates();
    shared_ptr<Node> getLeft();
    shared_ptr<Node> getRight();

};

#endif // NODE_H_INCLUDED
