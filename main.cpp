#include <iostream>
#include <random>
#include "Population.h"
#include "Graph.h"
#include "Output.h"
#include "Recorder.h"
#include "OverlayGrid.h"
#include "KDTree.h"


using namespace std;

int main(int arc, char *argv[])
{
    cout << "Hello world!" << endl;


    /*unsigned seed = strtol(argv[1], NULL, 10);
    double poissonMean = strtod(argv[2], NULL);
    double  maxRadius = strtod(argv[3], NULL);
    double circles = strtod(argv[4], NULL);
    int timeSteps = strtol(argv[5], NULL, 10);
    int initNodeNumber = strtol(argv[6], NULL, 10);
    double movementRate = strtod(argv[7], NULL, 10);
    double predisposition = strtod(argv[8], NULL, 10);*/


    unsigned seed = 1234;
    mt19937_64 generator(seed);

    int timeSteps=10;

    Recorder rec;
    Output out;

    Graph g;
    g.setNodeCoordinatesPoisson(4, 10, 10, generator);
    g.setNodeNumbers();

    KDTree kd;
    kd.setRoot(kd.makeTree(g));
    kd.linkParents(kd.getRoot());
    //kd.printTree();


    //OverlayGrid og;
    //og.calculateSideLength(g, 10);
    //og.makeGrid(g, 6, 1.6);

    Person p(g);
    p.setMovementRate(3);
    p.setPredisposition(9);

    vector<vector<double> > trajectories;
    vector<double> distances;
    uniform_int_distribution<int> unifDist(0, g.getNodeVector().size()-1);



    for(int i=0; i<10; ++i)
    {
        vector<double> coordinates1;
        vector<double> coordinates2;
        int position = unifDist(generator);
        p.setNodeNumber(position);
        coordinates1.push_back(static_cast<double>(i));
        coordinates1.push_back(p.getCoordinates().at(0));
        coordinates1.push_back(p.getCoordinates().at(1));
        p.relocate(generator, g, kd, 1);
        coordinates2.push_back(static_cast<double>(i));
        coordinates2.push_back(p.getCoordinates().at(0));
        coordinates2.push_back(p.getCoordinates().at(1));
        trajectories.push_back(coordinates1);
        trajectories.push_back(coordinates2);

        double distance = calculateDistance(g.getNodeVector().at(position), g.getNodeVector().at(p.getNodeNumber()));
        distances.push_back(distance);
    }

    ofstream file;
    file.open("trajectories_single-jump_single-person.csv");
    for(unsigned i=0; i<trajectories.size(); ++i)
    {
        for(unsigned j=0; j<trajectories.at(i).size(); ++j)
        {
            file << trajectories.at(i).at(j) << ",";
        }
        file << endl;
    }
    file.close();

    file.open("distances.csv");
    for(unsigned i=0; i<distances.size(); ++i)
    {
        file << distances.at(i) << endl;
    }
    file.close();


    return 0;
}
