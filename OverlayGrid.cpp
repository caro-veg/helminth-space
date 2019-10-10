#include <iostream>
#include <cmath>
#include "OverlayGrid.h"

using namespace std;

OverlayGrid::OverlayGrid() : minX(0), maxX(0), minY(0), maxY(0)
{

}

OverlayGrid::~OverlayGrid() {}


void OverlayGrid::calculateSideLength(Graph &_g, int _numberOfCells)
{
    for(unsigned i=0; i<_g.getNodeVector().size(); ++i)
    {
        if(_g.getNodeVector().at(i)->getCoordinates().at(0) < minX)
            minX = _g.getNodeVector().at(i)->getCoordinates().at(0);
        if(_g.getNodeVector().at(i)->getCoordinates().at(0) > maxX)
            maxX = _g.getNodeVector().at(i)->getCoordinates().at(0);
        if(_g.getNodeVector().at(i)->getCoordinates().at(1) < minY)
            minY = _g.getNodeVector().at(i)->getCoordinates().at(1);
        if(_g.getNodeVector().at(i)->getCoordinates().at(1) > maxY)
            maxY = _g.getNodeVector().at(i)->getCoordinates().at(1);
    }

    double xLength = maxX - minX;
    double yLength = maxY - minY;

    if(xLength < yLength)
    {
        sideLength = xLength / static_cast<double>(_numberOfCells);
        double yCells = ceil(yLength / sideLength);
        maxY = minY + yCells * sideLength;
    }

    else
    {
        sideLength = yLength / static_cast<double>(_numberOfCells);
        double xCells = ceil(yLength / sideLength);
        maxX = minX + xCells * sideLength;
    }
}


void OverlayGrid::makeGrid(Graph &_g)
{
    //make grid
    int xCells = static_cast<int>(round((maxX - minX)/sideLength));
    int yCells = static_cast<int>(round((maxY - minY)/sideLength));

    vector<vector<shared_ptr<Node> > > temp;
    for(int i=0; i<xCells; ++i)
    {
        nodes.push_back(temp);
    }

    //count villages in each grid cell
    for(unsigned i=0; i<_g.getNodeVector().size(); ++i)
    {
        for(int j=0; j<xCells; ++j)
        {
            for(int k=0; k<yCells; ++k)
            {
                if((_g.getNodeVector().at(i)->getCoordinates().at(0) > j*sideLength) &&
                   (_g.getNodeVector().at(i)->getCoordinates().at(0) < (j+1)*sideLength) &&
                   (_g.getNodeVector().at(i)->getCoordinates().at(1) > k*sideLength) &&
                   (_g.getNodeVector().at(i)->getCoordinates().at(1) < (k+1)*sideLength))
                {
                    nodes.at(j).at(k).push_back(_g.getNodeVector().at(i));
                }
            }
        }
    }
}



double OverlayGrid::getSideLength()
{
    return sideLength;
}
