#ifndef OVERLAYGRID_H_INCLUDED
#define OVERLAYGRID_H_INCLUDED

#include <vector>
#include <memory>
#include "Graph.h"

using std::vector;
using std::shared_ptr;

class OverlayGrid
{
private:
    double sideLength;
    double minX;
    double maxX;
    double minY;
    double maxY;

    vector<vector<double> > distances;
    vector<vector<vector<shared_ptr<Node> > > > nodesByCells;

public:
    OverlayGrid();
    ~OverlayGrid();

    void calculateSideLength(Graph &_g, int _numberOfCells);    //needs to be run before makeGrid() and calculateDistances()
    void makeGrid(Graph &_g);   //determines which nodes are in which cell
                                //needs to be run before distances between cells can be calculated
    void calculateDistances(); //can only be run after makeGrid() has been executed

    double getSideLength();
    const vector<vector<double> > &getDistances();
    vector<vector<vector<shared_ptr<Node> > > > getNodesByCells();
};

#endif // OVERLAYGRID_H_INCLUDED
