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

    Person p(g);

    p.setNodeNumber(4);
    cout << p.getNodeNumber() << endl;
    p.relocate(generator);
    cout << p.getNodeNumber() << endl;

    return 0;
}
