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
    cout << generator() << endl << endl;


    Graph g(9);
    g.makeGrid(3);
    //g.linkNodes(e);
    g.printLinkMap();

    Population p(g);

    return 0;
}
