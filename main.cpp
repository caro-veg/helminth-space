#include <iostream>
#include <random>
#include "Population.h"
#include "Graph.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    unsigned seed = 1234;
    mt19937_64 generator(seed);
    //cout << generator() << endl << endl;

    Graph g(10);
    vector<vector<double> > coords {{2,1}, {4,1}, {3,6}, {2,2}, {5,4}, {3,3}, {9,2}, {8,4}, {7,3}, {6,10}};
    g.setNodeCoordinates(coords);
    for(unsigned i=0; i<g.getNodeVector().size(); ++i)
    {
        cout << g.getNodeVector().at(i)->getCoordinates().at(0) << " " << g.getNodeVector().at(i)->getCoordinates().at(1) << endl;
    }

    //Person p(g);
    //p.setCoordinates(g.getNodeVector().at(p.getNodeNumber())->getCoordinates());
    //p.setMovementRate(3);
    //p.setPredisposition(0.4);

    //p.setNodeNumber(4);
    //cout << p.getNodeNumber() << endl;
    //p.relocate(generator);
    //cout << p.getNodeNumber() << endl;

    Population pop(g);
    pop.setupPopulation(10);
    pop.distributePopulation(generator);

    vector<double> movementRates(pop.getPeople().size(), 3);
    pop.setMovementRates(movementRates);
    pop.setPredispositions(3, 2, generator);

    vector<double> u;
    u.reserve(pop.getPeople().size());
    uniform_real_distribution<double> unifDist(0, 1);
    for(unsigned i=0; i<pop.getPeople().size(); ++i)
    {
        double ui = unifDist(generator);
        u.push_back(ui);
    }

    for(unsigned i=0; i<pop.getPeople().size(); ++i)
    {
        cout << pop.getPeople().at(i)->getNodeNumber() << " ";
    }
    cout << endl;

    for(unsigned i=0; i<pop.getPeople().size(); ++i)
    {
        cout << pop.getPeople().at(i)->getMovementRate() << " ";
    }
    cout << endl;

    for(unsigned i=0; i<pop.getPeople().size(); ++i)
    {
        cout << pop.getPeople().at(i)->getPredisposition() << " ";
    }
    cout << endl;


    /*for(int i=0; i<100; ++i){

    for(unsigned i=0; i<pop.getPeople().size(); ++i)
    {
        cout << pop.getPeople().at(i)->getNodeNumber() << " ";
    }
    cout << endl;

    pop.relocation(u, generator);

    for(unsigned i=0; i<pop.getPeople().size(); ++i)
    {
        cout << pop.getPeople().at(i)->getNodeNumber() << " ";
    }
    cout << endl;

    } */

    return 0;
}
