#ifndef RECORDER_H_INCLUDED
#define RECORDER_H_INCLUDED

#include <vector>
#include "Population.h"

using std::vector;


class Recorder
{
private:
    vector<vector<vector<double> > > trajectories;


public:
    Recorder();
    //Recorder(int _timeSteps);
    ~Recorder();
    void recordTrajectories(Population &_p);
    const vector<vector<vector<double> > > &getTrajectories();
};

#endif // RECORDER_H_INCLUDED
