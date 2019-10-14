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

    int xCells;
    int yCells;

    vector<vector<double> > hazards;
    vector<vector<vector<shared_ptr<Node> > > > nodesByCells;

public:
    OverlayGrid();
    ~OverlayGrid();

    void calculateSideLength(Graph &_g, int _numberOfCells);    //needs to be run before makeGrid() and calculateDistances()
    void makeGrid(Graph &_g, double _alpha, double _gamma);   //determines which nodes are in which cell
                                //needs to be run before distances between cells can be calculated

    double getSideLength();
    int getXCells();
    int getYCells();
    const vector<vector<double> > &getHazards();
    vector<vector<vector<shared_ptr<Node> > > > getNodesByCells();
};

#endif // OVERLAYGRID_H_INCLUDED
