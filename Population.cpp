#include <iostream>
#include "Population.h"

using namespace std;


Population::Population(Graph &_graph) : graph(_graph)
{

}


Population::~Population()
{

}


void Population::setupPopulation(int _popSize)
{
    //create people vector
    for(int i=0; i<_popSize; ++i)
    {
           people.push_back(shared_ptr<Person> (new Person(graph)));
    }
}


void Population::distributePopulation(mt19937_64 _generator)
{
    uniform_int_distribution<int> unifDist(0, graph.getNodeVector().size()-1);
    for(unsigned i=0; i<people.size(); ++i)
    {
        int nodeNumber = unifDist(_generator);
        people.at(i)->setNodeNumber(nodeNumber);
        people.at(i)->setCoordinates(graph.getNodeVector().at(nodeNumber)->getCoordinates());
    }
}


void Population::setupAgelessPopulation(int _popSize, double _mean, double _variance, mt19937_64 _generator)
{
    //create people vector
    for(int i=0; i<_popSize; ++i)
    {
           people.push_back(shared_ptr<Person> (new Person(graph)));
    }

    //assign parasite load to each person
    double k = _mean * _mean / (_variance - _mean);
    double p = (_variance - _mean) / _variance;

    negative_binomial_distribution<int> nbDist(k, p);
    for(int i=0; i<_popSize; ++i)
    {
        people.at(i)->parasites = nbDist(_generator);
        //determine number of female parasites
    }
}



void Population::setupAgeStructuredPopulation()
{
    //draw life spans of individuals
    //generate birth dates for individuals: -lifeSpans*runif(pars$N)
    //generate death dates for individuals: birth dates + lifeSpans

    //burn-in: equilibrate the population over x years
    //while death dates < x run loop
        //replacing deaths by births (death dates by birth dates) and
        //assigning new death dates by setting new life spans

    //calculate parasite burden for each individual
        //calculate s from gamma function and shape parameter k
       /** double shape = _k;
        double scale = 1/_k;
        gamma_distribution<double> gammaDist(shape, scale);
        vector<double> s;

        for(int i=0; i<_popSize; ++i)
            s.push_back(gammaDist(_generator));

        //multiply s with population age profile to get mean worm burdens by age group

        //draw total worm burden of each person from Poisson distribution with mean calculated in previous step
        poisson_distribution<int> poissonDist(mean);

        for(int i=0; i<_popSize; ++i)
        {
            int wormBurden = poissonDist(_generator);
            cout << wormBurden << endl;
        } **/
}


void Population::setLifeSpans()
{
    //access demography death rates

    //for a sequence of ages (descritised by dT) assign death rate according to demography death rates

    //construct vector of probabilities of surviving each year

    //construct population survival curve (cumulative probability of dying in the ith year)

    //for loop over people vectors: draw a lifespan from the population survival curve and assign to person
}

void Population::setMovementRates(vector<double> _movementRates)
{
    for(unsigned i=0; i<people.size(); ++i)
    {
        people.at(i)->setMovementRate(_movementRates.at(i));
    }
}


void Population::setPredispositions(vector<double> _predispositions)
{
    for(unsigned i=0; i<people.size(); ++i)
    {
        people.at(i)->setPredisposition(_predispositions.at(i));
    }
}

void Population::setPredispositions(double _shape, double _scale, mt19937_64 _generator)
{
    gamma_distribution<double> gammaDist(_shape, _scale);
    for(unsigned i=0; i<people.size(); ++i)
    {
        double predisposition = gammaDist(_generator);
        people.at(i)->setPredisposition(predisposition);
    }
}


void Population::relocation(vector<double> _u, mt19937_64 _generator)
{
    for(unsigned i=0; i<people.size(); ++i)
    {
        poisson_distribution<int> poissonDist(people.at(i)->getMovementRate());
        if(_u.at(i) < static_cast<double> (poissonDist(_generator)))
        {
            people.at(i)->relocate(_generator);
        }
    }
}


void Population::relocation(mt19937_64 _generator, Graph &_g, OverlayGrid &_og, double _alpha, double _gamma)
{
    for(unsigned i=0; i<people.size(); ++i)
    {
        people.at(i)->relocate(_generator, _g, _og, _alpha, _gamma);
    }
}


vector<shared_ptr<Person> > Population::getPeople()
{
    return people;
}
