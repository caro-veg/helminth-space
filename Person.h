#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <vector>
#include <utility>
#include <memory>
#include "Utility_Functions.h"
#include "Graph.h"
#include "Parasite.h"

using std::pair;
using std::vector;
using std::shared_ptr;

class Person
{
    friend class Population;
private:
    Graph &graph;
    pair<double, double> coordinates;   //for spatially explicit model
    int nodeNumber;                     //for network model

    double age;
    sex_enum sex;
    vector<shared_ptr<Parasite> > parasites;


public:
    Person(Graph &_graph);
    ~Person();

    void aging(double _ageInterval);
    void die();

    void setNodeNumber(int _nodeNumber);

    pair<double, double> getCoordinates();
    int getNodeNumber();
    double getAge();
    sex_enum getSex();
    vector<shared_ptr<Parasite> > getParasites();
};

#endif // PERSON_H_INCLUDED
