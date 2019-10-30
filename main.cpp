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
    g.setNodeCoordinatesPoisson(4, 1000, 1000, generator);
    g.setNodeNumbers();


    //KDTree kd;
    //kd.setRoot(kd.makeTree(g));
    //kd.linkParents(kd.getRoot());
    //g.setNodeNumbers();


    OverlayGrid og;
    og.calculateSideLength(g, 10);
    og.makeGrid(g, 3, 1.6);


    Person p(g);
    p.setMovementRate(3);
    p.setPredisposition(9);

    vector<vector<double> > trajectories;
    vector<double> distances;
    uniform_int_distribution<int> unifDist(0, g.getNodeVector().size()-1);


    for(int i=0; i<1000; ++i)
    {
        //cout << "######## " << i << " ############" << endl;
        vector<double> coordinates1;
        vector<double> coordinates2;
        p.setNodeNumber(g.getNodeVector().at(0)->getNodeNumber());
        coordinates1.push_back(static_cast<double>(i));
        coordinates1.push_back(p.getCoordinates().at(0));
        coordinates1.push_back(p.getCoordinates().at(1));
        //cout << "prior " << p.getCoordinates().at(0) << " " << p.getCoordinates().at(1) << endl;
        //p.relocate(generator, g, kd, 3000);
        //p.relocate(generator);
        p.relocate(generator, g, og, 3, 1.6);
        coordinates2.push_back(static_cast<double>(i));
        //cout << "post " << p.getCoordinates().at(0) << " " << p.getCoordinates().at(1) << endl;
        coordinates2.push_back(p.getCoordinates().at(0));
        coordinates2.push_back(p.getCoordinates().at(1));
        trajectories.push_back(coordinates1);
        trajectories.push_back(coordinates2);

        double distance = (coordinates1.at(0) - coordinates2.at(0)) * (coordinates1.at(0) - coordinates2.at(0)) + (coordinates1.at(1) - coordinates2.at(1)) * (coordinates1.at(1) -coordinates2.at(1));
        distance = sqrt(distance);
        distances.push_back(distance);
        //cout << endl << endl;
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
