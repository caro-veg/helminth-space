#include <iostream>
#include "Output.h"

using namespace std;

Output::Output()
{

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


void Output::printToCsvTrajectories(Recorder &_rec, string _filename)
{
    ofstream file;
    file.open((_filename + ".csv").c_str());
    for(unsigned i=0; i<_rec.getTrajectories().size(); ++i)
    {
        for(unsigned j=0; j<_rec.getTrajectories().at(i).size(); ++j)
        {
            file << i << "," << j << ",";

            for(unsigned k=0; k<_rec.getTrajectories().at(i).at(j).size(); ++k)
            {
                file << _rec.getTrajectories().at(i).at(j).at(k) << ",";
            }

            file << endl;
        }
    }
}

