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
        double xCells = ceil(xLength / sideLength);
        maxX = minX + xCells * sideLength;
    }

}


void OverlayGrid::makeGrid(Graph &_g)
{
    //make grid
    int xCells = static_cast<int>(round((maxX - minX)/sideLength));
    int yCells = static_cast<int>(round((maxY - minY)/sideLength));

    vector<vector<shared_ptr<Node> > > temp1;
    for(int i=0; i<xCells; ++i)
    {
        nodesByCells.push_back(temp1);
    }
    cout << xCells << " " << yCells << endl;
    //count villages in each grid cell
    for(int i=0; i<xCells; ++i)
    {
        for(int j=0; j<yCells; ++j)
        {
            vector<shared_ptr<Node> > temp2;

            for(unsigned k=0; k<_g.getNodeVector().size(); ++k)
            {
                if((_g.getNodeVector().at(k)->getCoordinates().at(0) >= (minX + i*sideLength)) &&
                   (_g.getNodeVector().at(k)->getCoordinates().at(0) <= (minX + (i+1)*sideLength)) &&
                   (_g.getNodeVector().at(k)->getCoordinates().at(1) >= (minY + j*sideLength)) &&
                   (_g.getNodeVector().at(k)->getCoordinates().at(1) <= (minY + (j+1)*sideLength)))
                {
                    temp2.push_back(_g.getNodeVector().at(k));
                }
            }
            nodesByCells.at(j).push_back(temp2);
        }
    }

    //initialise distance matrix
    double totalCells = xCells * yCells;
    vector<double> help(totalCells, 0);
    for(int i=0; i<totalCells; ++i)
    {
        distances.push_back(help);
    }

    for(unsigned i=0; i<nodesByCells.size(); ++i)
    {
        for(unsigned j=0; j<nodesByCells.at(i).size(); ++j)
        {
            for(unsigned k=0; k<nodesByCells.size(); ++k)
            {
                for(unsigned l=0; l<nodesByCells.at(k).size(); ++l)
                {
                    double distance = sideLength * (abs(static_cast<double>(k)-static_cast<double>(i)) + abs(static_cast<double>(l)-static_cast<double>(j)));
                    cout << k << " " << i << " " << l << " " << j << " " << distance << endl;
                    cout << i + j*yCells << " " << k + l*yCells << endl;
                    distances.at(i + j*yCells).at(k + l*yCells) = distance;
                }
            }
        }

    }
}



void OverlayGrid::calculateDistances()
{
    for(unsigned i=0; i<nodesByCells.size(); ++i)
    {
        for(unsigned j=0; j<nodesByCells.at(i).size(); ++j)
        {
            for(unsigned k=0; k<nodesByCells.size(); ++k)
            {
                for(unsigned l=0; l<nodesByCells.at(k).size(); ++l)
                {
                    double distance = sideLength * (abs(static_cast<double>(k)-static_cast<double>(i)) + abs(static_cast<double>(l)-static_cast<double>(j)));
                    cout << k << " " << i << " " << l << " " << j << " " << distance << endl;
                    distances.at(i + j*nodesByCells.size()).at(k + l*nodesByCells.at(i).size()) = distance;
                }
            }
        }

    }
}



double OverlayGrid::getSideLength()
{
    return sideLength;
}

const vector<vector<double> > &OverlayGrid::getDistances()
{
    return distances;
}


vector<vector<vector<shared_ptr<Node> > > > OverlayGrid::getNodesByCells()
{
    return nodesByCells;
}
