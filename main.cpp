#include <iostream>
#include <random>
#include "Population.h"
#include "Graph.h"
#include "Output.h"
#include "Recorder.h"
#include "OverlayGrid.h"

using namespace std;

int main()
{
    cout << "Hello world!" << endl;

    unsigned seed = 1234;
    mt19937_64 generator(seed);

    int timeSteps=10;

    Recorder rec;
    Output out;

    Graph g;
    g.setNodeCoordinatesPoisson(4, 10, 10, generator);

    OverlayGrid og;
    og.calculateSideLength(g, 5);

    og.makeGrid(g);
    cout << og.getDistances().size() << " " << og.getDistances().at(0).size() << endl;

    for(unsigned i=0; i<og.getDistances().size(); ++i)
    {
        for(unsigned j=0; j<og.getDistances().at(i).size(); ++j)
        {
            cout << og.getDistances().at(i).at(j) << " ";
        }
        cout << endl;
    }

    return 0;
}
