#include <iostream>
#include "Output.h"

using namespace std;

Output::Output(Graph &_g, Population &_p, int _timeSteps) : g(_g), p(_p)
{
    vector<double> helpVector;
    helpVector.reserve(p.getPeople().size());
    for(int i=0; i<_timeSteps; ++i)
    {
        trajectories.push_back(helpVector);
    }
}

Output::~Output() {}

void Output::printToCsvNodeCoordinates(Graph &_g, string _filename)
{
    ofstream file;
    file.open((_filename + ".csv").c_str());
    for(unsigned i=0; i<_g.getNodeVector().size(); ++i)
    {
        file << _g.getNodeVector().at(i)->getCoordinates().at(0) << "," << _g.getNodeVector().at(i)->getCoordinates().at(1) << endl;
    }
    file.close();
}


vector<vector<double> > Output::getTrajectories()
{
    return trajectories;
}
