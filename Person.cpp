#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Person.h"

using namespace std;



Person::Person(Graph &_graph) : graph(_graph), age(0)
{
    srand(time(NULL));
    if(rand() % 100 < 50)
        sex = female;
    else
        sex = male;
}


Person::~Person()
{

}


void Person::aging(double _ageInterval)
{
    age +=_ageInterval;
}


void Person::die()
{

}


void Person::setNodeNumber(int _nodeNumber)
{
    try
    {
        if(_nodeNumber < 0 || _nodeNumber > graph.getNodeVector().size())
        {
            throw 1;
        }
        nodeNumber = _nodeNumber;
    }
    catch(int e)
    {
        nodeNumber = 0;
        cout << "Person's node number out of range, node number set to 0" << endl;
    }
}



double Person::getAge()
{
    return age;
}


sex_enum Person::getSex()
{
    return sex;
}


vector<shared_ptr<Parasite> > Person::getParasites()
{
    return parasites;
}
