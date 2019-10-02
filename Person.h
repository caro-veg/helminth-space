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
    vector<double> coordinates;
    double movementRate;
    double predisposition;  //predisposition for distance to move

    double age;
    sex_enum sex;
    int parasites;
    int femaleParasites;
     bool alive;


public:
    Person(Graph &_graph);
    ~Person();

    void setNodeNumber(int _nodeNumber);
    void setCoordinates(vector<double> coordinates);
    void setPredisposition(double _predisposition);
    void setMovementRate(double _movementRate);


    void relocate(mt19937_64 _generator);

    void aging(double _ageInterval);
    void die();

    void setParasites(int _parasites);
    void setFemaleParasites(int _femaleParasites);


    int getNodeNumber();
    vector<double> getCoordinates();

    double getMovementRate();
    double getPredisposition();

    double getAge();
    sex_enum getSex();
    bool getAlive();

    int getParasites();
    int getFemaleParasites();

};

#endif // PERSON_H_INCLUDED
