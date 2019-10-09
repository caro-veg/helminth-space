#ifndef OUTPUT_H_INCLUDED
#define OUTPUT_H_INCLUDED

#include <vector>
#include <string>
#include <fstream>
#include "Graph.h"
#include "Population.h"
#include "Recorder.h"

using std::vector;
using std::string;

class Output
{
private:

public:
    Output();
    ~Output();

    template<typename T>
    void printToCsvFile(const vector<vector<T> > &_vector, string _filename)
    {
        std::ofstream file;
        file.open((_filename + ".csv").c_str());
        for(int i=0; i<_vector.size(); ++i)
        {
            for(int j=0; j<_vector.at(i).size(); ++j)
            {
                file << _vector.at(i).at(j) << ",";
            }
            file << std::endl;
        }
        file << std::endl;

        file.close();
    }

    template<typename T>
    void printToCsvFile(const vector<T> &_vector, string _filename)
    {
        std::ofstream file;
        file.open((_filename + ".csv").c_str());
        for(int i=0; i<_vector.size(); ++i)
            file << _vector.at(i) << std::endl;
        file.close();
    }

    void printToCsvNodeCoordinates(Graph &_g, string _filename);

    void printToCsvTrajectories(Recorder &_rec, string _filename);


};

#endif // OUTPUT_H_INCLUDED
