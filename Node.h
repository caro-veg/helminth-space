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
    double fitness; //node fitness: "attraction" of location for people

    //needed for rejection algorithm
    vector<int> cellCoordinates;


public:
    Node();
    ~Node();

    void setCoordinates(vector<double> _coordinates);
    void setFitness(double _fitness);
    void setCellCoordinates(vector<int> _cellCoordinates);

    vector<double> getCoordinates();
    double getFitness();
    vector<int> getCellCoordinates();
};

#endif // NODE_H_INCLUDED
