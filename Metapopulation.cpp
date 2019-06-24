#include <iostream>
#include "Metapopulation.h"

using namespace std;


Metapopulation::Metapopulation(Graph &_graph, int _metaPopulationSize) : graph(_graph)
{
    populations.reserve(_metaPopulationSize);
    for(int i=0; i<_metaPopulationSize; ++i)
        populations.push_back(shared_ptr<Population> (new Population(_graph)));
}


Metapopulation::~Metapopulation()
{

}


void Metapopulation::setupPopulations(vector<int> _popSizes, vector<double> _means, vector<double> _variances, mt19937_64 _generator)
{
    try
    {
        if(_popSizes.size() != populations.size())
        {
            throw("population vector and number of population sizes given do not match");
        }

        for(int i=0; i<populations.size(); ++i)
            populations.at(i)->setupAgelessPopulation(_popSizes.at(i), _means.at(i), _variances.at(i), _generator);
    }
    catch(const char* msg)
    {
        cerr << msg << endl;
    }
}


vector<shared_ptr<Population> > Metapopulation::getPopulations()
{
    return populations;
}
