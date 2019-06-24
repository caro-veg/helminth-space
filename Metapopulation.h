#ifndef METAPOPULATION_H_INCLUDED
#define METAPOPULATION_H_INCLUDED

#include <vector>
#include <memory>
#include <random>
#include "Graph.h"
#include "Population.h"

using std::vector;
using std::shared_ptr;
using std::mt19937_64;


class Metapopulation
{
private:
    Graph &graph;
    vector<shared_ptr<Population> > populations;

public:
    Metapopulation(Graph &_graph, int _metaPopulationSize);
    ~Metapopulation();

    void setupPopulations(vector<int> _popSizes, vector<double> _means, vector<double> _variances, mt19937_64 _generator);

    vector<shared_ptr<Population> > getPopulations();
};

#endif // METAPOPULATION_H_INCLUDED
