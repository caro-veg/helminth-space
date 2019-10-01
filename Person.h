#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include <vector>
#include <memory>
#include <random>
#include "Utility_Functions.h"
#include "Graph.h"

using std::vector;
using std::shared_ptr;
using std::mt19937_64;


class Person
{
    friend class Population;
private:
    Graph &graph;
    int nodeNumber;

    double age;
    sex_enum sex;
    int parasites;
    int femaleParasites;

    double predisposition;
    bool moving;
    bool alive;

public:
    Person(Graph &_graph);
    ~Person();

    void aging(double _ageInterval);
    void die();
    void relocate(mt19937_64 _generator);

    void setNodeNumber(int _nodeNumber);
    void setParasites(int _parasites);
    void setFemaleParasites(int _femaleParasites);
    void setPredisposition(double _predisposition);

    int getNodeNumber();
    vector<double> getCoordinates();

    double getAge();
    sex_enum getSex();

    int getParasites();
    int getFemaleParasites();
    double getPredisposition();

    bool getMoving();
    bool getAlive();
};

#endif // PERSON_H_INCLUDED
