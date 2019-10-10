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
    vector<vector<vector<shared_ptr<Node> > > > nodes;

public:
    OverlayGrid();
    ~OverlayGrid();

    void calculateSideLength(Graph &_g, int _numberOfCells);
    void calculateDistances(Graph &_g);
    void makeGrid(Graph &_g);

    double getSideLength();
    const vector<vector<double> > &getDistances();
    vector<vector<vector<shared_ptr<Node> > > > getNodes();
};

#endif // OVERLAYGRID_H_INCLUDED
