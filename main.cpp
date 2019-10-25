#include <iostream>
#include <random>
#include "Population.h"
#include "Graph.h"
#include "Output.h"
#include "Recorder.h"
#include "OverlayGrid.h"
#include "KDTree.h"


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
    g.setNodeCoordinatesPoisson(4, 100, 100, generator);
    g.setNodeNumbers();

    KDTree kdt;
    kdt.setRoot(kdt.makeTree(g));
    kdt.linkParents(kdt.getRoot());

    Person p(g);
    p.setNodeNumber(108);
    p.setMovementRate(3);
    p.setPredisposition(9);

    OverlayGrid og;
    og.calculateSideLength(g, 5);
    og.makeGrid(g, 2, 1.2);

    cout << og.getSideLength() << endl;
    int x = g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(0);
    int y = g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(1);
    vector<shared_ptr<Node> > test = og.getNodesByCells().at(x).at(y);
    /*cout << test.size() << endl;
    for(unsigned i=0; i<test.size(); ++i)
    {
        cout << test.at(i)->getCoordinates().at(0) << " " << test.at(i)->getCoordinates().at(1) << endl;
    }*/
    cout << endl << "Dupdup" << endl;
    for(int i=0; i<5; ++i)
    {
        cout << g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(0) << " " << g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(1) << endl;
        cout << p.getCoordinates().at(0) << " " << p.getCoordinates().at(1) << endl;
        //p.relocate(generator, g, kdt, 200);
        //int prev = p.getNodeNumber();
        p.relocate(generator, g, og, 2, 1.2);
        cout << g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(0) << " " << g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(1) << endl;
        cout << p.getCoordinates().at(0) << " " << p.getCoordinates().at(1) << endl;
        //if(prev!=p.getNodeNumber()) cout << "I moved!" << endl;
        cout << endl;
    }



    cout << endl;
    x = g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(0);
    y = g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(1);
    test = og.getNodesByCells().at(x).at(y);
    cout << test.size() << endl;
    for(unsigned i=0; i<test.size(); ++i)
    {
        cout << test.at(i)->getCoordinates().at(0) << " " << test.at(i)->getCoordinates().at(1) << endl;
    }

    cout << g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(0) << " " << g.getNodeVector().at(p.getNodeNumber())->getCellCoordinates().at(1) << endl;

    cout << endl;
    for(unsigned i=0; i<og.getNodesByCells().size(); ++i)
    {
        for(unsigned j=0; j<og.getNodesByCells().at(i).size(); ++j)
        {
            cout << og.getNodesByCells().at(i).at(j).size() << " ";
        }
        cout << endl;
    }


    return 0;
}
