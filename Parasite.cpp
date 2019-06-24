#include <iostream>
#include "Parasite.h"

using namespace std;

Parasite::Parasite() : age(0) {}

Parasite::~Parasite() {}

void Parasite::aging(double _ageInterval)
{
    age += _ageInterval;
}

void Parasite::die()
{

}

double Parasite::getAge()
{
    return age;
}
