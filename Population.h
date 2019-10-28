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
    vector<shared_ptr<Person> > people;


public:
    Population(Graph &_graph);
    ~Population();


    //set up population without age structure and parasites
    void setupPopulation(int _popSize);

    void distributePopulation(mt19937_64 &_generator);

    //set up population without age structure but with parasites
    //currently uses mean and variance of negative binomial distribution to calculate parameters k and p
    //will be changed to accept fitted parameters later
    void setupAgelessPopulation(int _popSize, double _mean, double _variance, mt19937_64 &_generator);
    void setupAgeStructuredPopulation();         //set up age-structured population
    void setLifeSpans();                        //set dT: discretisation of drawing of lifespans

    void setMovementRates(vector<double> _movementRates);
    void setPredispositions(vector<double> _predispositions);
    void setPredispositions(double _shape, double _scale, mt19937_64 &_generator);

    void relocation(vector<double> _u, mt19937_64 &_generator);
    void relocation(mt19937_64 &_generator, Graph &_g, OverlayGrid &_og, double _alpha, double _gamma);

    vector<shared_ptr<Person> > getPeople();
};

#endif // POPULATION_H_INCLUDED
