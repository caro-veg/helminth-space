#include <iostream>
#include "Recorder.h"

using namespace std;

Recorder::Recorder()
{

}

/*Recorder::Recorder(int _timeSteps) : p(_p)
{
    vector<double> helpVector;
    helpVector.reserve(p.getPeople().size());
    for(int i=0; i<_timeSteps; ++i)
    {
        trajectories.push_back(helpVector);
    }
}*/

Recorder::~Recorder() {}


void Recorder::recordTrajectories(Population &_p)
{
    if(trajectories.size()==0)
    {
        vector<vector<double> > help;
        for(unsigned i=0; i<_p.getPeople().size(); ++i)
        {
            trajectories.push_back(help);
        }
    }

    for(unsigned i=0; i<_p.getPeople().size(); ++i)
    {
        trajectories.at(i).push_back(_p.getPeople().at(i)->getCoordinates());
    }
}


const vector<vector<vector<double> > > &Recorder::getTrajectories()
{
    return trajectories;
}
