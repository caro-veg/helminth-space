#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <utility>
#include <memory>
#include <vector>

using std::pair;
using std::vector;
using std::shared_ptr;

class Node
{
private:
    pair<double, double> coordinates;
    int number;
    //map of destination nodes with distance
    vector<pair<shared_ptr<Node>, double> > destinationNodes;
    bool occupied;

public:
    Node();
    ~Node();

    void setNumber(int _number);
    void addDestinationNode(shared_ptr<Node> _node, double _distance);
    void setOccupied(bool _occupied);

    int getNumber();
    vector<pair<shared_ptr<Node>, double> > getDestinationNodes();
    bool getOccupied();
};

#endif // NODE_H_INCLUDED
