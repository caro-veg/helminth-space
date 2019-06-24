#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED

#include <utility>
#include <vector>
#include <memory>
#include <random>
#include "Person.h"
#include "Graph.h"

using std::pair;
using std::vector;
using std::shared_ptr;
using std::mt19937_64;

class Population
{
private:

    Graph &graph;
    pair<double, double> coordinates;
    int nodeNumber;
    double reservoir;
    vector<shared_ptr<Person> > people;


public:
    Population(Graph &_graph);
    ~Population();

    void setNodeNumber(int _nodeNumber);

    //set up population without age structure
    //currently uses mean and variance of negative binomial distribution to calculate parameters k and p
    //will be changed to accept fitted parameters later
    void setupAgelessPopulation(int _popSize, double _mean, double _variance, mt19937_64 _generator);
    void setupPopulation();         //set up age-structured population
    void setLifeSpans();            /*set dT: discretisation of drawing of lifespans*/

    int getNodeNumber();
    double getReservoir();
    vector<shared_ptr<Person> > getPeople();
};

#endif // POPULATION_H_INCLUDED
