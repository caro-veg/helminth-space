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
    g.setNodeCoordinatesPoisson(4, 10, 10, generator);
    g.setNodeNumbers();
    //g.setNodeNumbers();
    cout << g.getNodeVector().size() << endl;
    /*cout << endl << "Node coordinates" << endl;
    for(int i=0; i<g.getNodeVector().size(); ++i)
    {
        cout << g.getNodeVector().at(i)->getCoordinates().at(0) << " " << g.getNodeVector().at(i)->getCoordinates().at(1) << endl;
    }*/

    KDTree kdt;

    kdt.setRoot(kdt.makeTree(g));
    kdt.linkParents(kdt.getRoot());

    cout << kdt.getNodeNumber() << endl;

    //kdt.printTree();

    cout << kdt.getRoot()->getNodeNumber() << endl;

    vector<shared_ptr<Node> > v;
    kdt.findNodesWithinRadius(g.getNodeVector().at(15), 7.0, v);

    for(int i=0; i<v.size(); ++i)
    {
        cout << v.at(i)->getCoordinates().at(0) << " " << v.at(i)->getCoordinates().at(1) << endl;
    }

    return 0;
}
