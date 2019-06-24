#include <iostream>
#include "Population.h"

using namespace std;


Population::Population(Graph &_graph) : graph(_graph)
{

}


Population::~Population()
{

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
        int wormBurden = nbDist(_generator);
        people.at(i)->parasites.reserve(wormBurden);

        for(int j=0; j<wormBurden; ++j)
            people.at(i)->parasites.push_back(shared_ptr<Parasite> (new Parasite()));
    }
}


void Population::setupPopulation()
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

double Population::getReservoir()
{
    return reservoir;
}

vector<shared_ptr<Person> > Population::getPeople()
{
    return people;
}
