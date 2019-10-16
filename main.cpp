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
    g.setNodeNumbers();

    OverlayGrid og;
    og.calculateSideLength(g, 5);
    //cout << og.getSideLength() << endl << endl;

    og.makeGrid(g, 2.0, 1.6);

    //cout << og.getNodesByCells().size() << " " << og.getNodesByCells().at(2).size() << endl << endl;

    Person p(g);
    p.setNodeNumber(10);
    p.relocateRejection(generator, g, og, 3, 1.6);

    //cout << og.getHazards().size() << " " << og.getHazards().at(0).size() << endl;

    //cout << og.getHazards().at(2).at(13) << endl;


    /*for(unsigned i=0; i<og.getHazards().size(); ++i)
    {
        for(unsigned j=0; j<og.getHazards().at(i).size(); ++j)
        {
            cout << og.getHazards().at(i).at(j) << " ";
        }
        cout << endl;
    }*/

    return 0;
}
