#include <iostream>
#include <cmath>
#include "OverlayGrid.h"

using namespace std;

OverlayGrid::OverlayGrid() : minX(0), maxX(0), minY(0), maxY(0), rows(0), columns(0)
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

    double xLength = (maxX - minX) * 1.00001;
    double yLength = (maxY - minY) * 1.00001;

    if(xLength < yLength)
    {
        columns = _numberOfCells;
        sideLength = xLength / static_cast<double>(_numberOfCells);
        rows = ceil(yLength / sideLength);
        maxY = minY + rows * sideLength;
    }

    else
    {
        rows = _numberOfCells;
        sideLength = yLength / static_cast<double>(_numberOfCells);
        columns = ceil(xLength / sideLength);
        maxX = minX + columns * sideLength;
    }

}


void OverlayGrid::makeGrid(Graph &_g, double _alpha, double _gamma) // for hazard calculation pass different functions: could be power law or exponential
{
    //count villages in each grid cell
    int position = -1;
    for(int i=0; i<rows; ++i)
    {
        vector<vector<shared_ptr<Node> > > temp1;

        for(int j=0; j<columns; ++j)
        {
            vector<shared_ptr<Node> > temp2;
            ++position;

            for(unsigned k=0; k<_g.getNodeVector().size(); ++k)
            {
                //cout << i << " " << j << " " << k << " " << _g.getNodeVector().at(k)->getCoordinates().at(1) << endl;
                if((_g.getNodeVector().at(k)->getCoordinates().at(0) >= (minX + i*sideLength)) &&
                   (_g.getNodeVector().at(k)->getCoordinates().at(0) < (minX + (i+1)*sideLength)) &&
                   (_g.getNodeVector().at(k)->getCoordinates().at(1) >= (minY + j*sideLength)) &&
                   (_g.getNodeVector().at(k)->getCoordinates().at(1) < (minY + (j+1)*sideLength)))
                {
                    temp2.push_back(_g.getNodeVector().at(k));
                    vector<int> v{j, i};
                    _g.getNodeVector().at(k)->setCellCoordinates(v);
                    _g.getNodeVector().at(k)->setCellNumber(position);
                    //cout << "set position " << v.at(0) << " " << v.at(1) << " " << position << endl << endl;
                }
            }
            temp1.push_back(temp2);
        }
        nodesByCells.push_back(temp1);
    }


    //initialise distance matrix
    double totalCells = columns * rows;
    vector<double> help(totalCells, 0);
    for(int i=0; i<totalCells; ++i)
    {
        hazards.push_back(help);
    }

    vector<vector<double> > coordinates;
    for(int i=0; i<rows; ++i)
    {
        for(int j=0; j<columns; ++j)
        {
            vector<double> temp3;
            temp3.push_back(i);
            temp3.push_back(j);
            coordinates.push_back(temp3);
        }
    }

    for(unsigned i=0; i<coordinates.size(); ++i)
    {
        for(unsigned j=0; j<coordinates.size(); ++j)
        {
            //cout << "############################## " << i << " " << j << endl;
            //double distance = (coordinates.at(i).at(0) - coordinates.at(j).at(0)) * (coordinates.at(i).at(0) - coordinates.at(j).at(0)) +
             //                 (coordinates.at(i).at(1) - coordinates.at(j).at(1)) * (coordinates.at(i).at(1) - coordinates.at(j).at(1));
            double xDistance = (abs(coordinates.at(i).at(0) - coordinates.at(j).at(0)) - 1) * sideLength;
            if(xDistance < 0)
                xDistance = 0;
            double yDistance = (abs(coordinates.at(i).at(1) - coordinates.at(j).at(1)) - 1) * sideLength;
            if(yDistance < 0)
                yDistance = 0;
            //cout << sideLength << " " << xDistance << " " << yDistance << endl;
            double distance = xDistance * xDistance + yDistance * yDistance;
            distance = sqrt(distance);
            //if((distance > 0) && (coordinates.at(i).at(0)==coordinates.at(j).at(0) || coordinates.at(i).at(1)==coordinates.at(j).at(1)))
              //  distance -= 1;
            //else if((coordinates.at(i).at(0)!=coordinates.at(j).at(0)) && (coordinates.at(i).at(1)!=coordinates.at(j).at(1)))
              //  distance -= sqrt(2);
            //distance = distance * sideLength;
            double hazard = 1 + distance / _alpha;  //make function that can be passed into this function
            hazard = pow(hazard, -_gamma);
            //double a = static_cast<double>(j) / static_cast<double>(columns);
            hazards.at(i).at(j) = hazard * nodesByCells.at(j/columns).at(j%columns).size();
            //cout << distance << " " << pow(hazard, -_gamma) << " " << hazard << " " << nodesByCells.at(j/columns).at(j%columns).size() << endl << endl;
            //cout << endl;
        }
    }

    //for testing: Manhattan distance for recognisable matrix values in printout
    /*for(unsigned i=0; i<coordinates.size(); ++i)
    {
        for(unsigned j=0; j<coordinates.size(); ++j)
        {
            double distance = abs(coordinates.at(i).at(0) - coordinates.at(j).at(0)) + abs(coordinates.at(i).at(1) - coordinates.at(j).at(1));
            if((distance > 0) && (coordinates.at(i).at(0)==coordinates.at(j).at(0) || coordinates.at(i).at(1)==coordinates.at(j).at(1)))
                distance -= 1;
            else if(coordinates.at(i).at(0)!=coordinates.at(j).at(0) && coordinates.at(i).at(1)!=coordinates.at(j).at(1))
                distance -=2;
            distance = distance * sideLength;
            double hazard = 1 + distance / _alpha;
            hazard = pow(hazard, -_gamma);
            hazards.at(i).at(j) = hazard;
        }
    }*/
}



double OverlayGrid::getSideLength()
{
    return sideLength;
}

int OverlayGrid::getRows()
{
    return rows;
}

int OverlayGrid::getColumns()
{
    return columns;
}

double OverlayGrid::getMinX()
{
    return minX;
}

double OverlayGrid::getMaxX()
{
    return maxX;
}

double OverlayGrid::getMinY()
{
    return minY;
}

double OverlayGrid::getMaxY()
{
    return maxY;
}

const vector<vector<double> > &OverlayGrid::getHazards()
{
    return hazards;
}


vector<vector<vector<shared_ptr<Node> > > > OverlayGrid::getNodesByCells()
{
    return nodesByCells;
}
