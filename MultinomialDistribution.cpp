#include <iostream>
#include <cmath>
#include "MultinomialDistribution.h"

using namespace std;

MultinomialDistribution::MultinomialDistribution(vector<double> _probabilities)
{
    probabilities = _probabilities;
    for(unsigned i=0; i<probabilities.size(); ++i)
    {
        if(i>0)
            probabilities.at(i) = probabilities.at(i) + probabilities.at(i-1);
        probMap[i] = probabilities.at(i);
    }
}

MultinomialDistribution::~MultinomialDistribution() {};


int MultinomialDistribution::drawNumber(double _rn)
{
    for(unsigned i=0; i<probabilities.size(); ++i)
    {
        if(_rn < probabilities.at(i))
        {
            return i;
        }

    }
}

double MultinomialDistribution::getProb(int _n)
{
    return probMap[_n];
}


int MultinomialDistribution::bisection(int _a, int _b, double _u)
{
    //cout << _u << " " << getProb(0) << endl;
    if(_u <= getProb(0))
        return 0;

    /*if(_u >= getProb(probs.size()-1))
    {
        //cout << "hello " << getProb(probs.size()-1) << endl;
        return (probs.size());
    }*/

    if((getProb(_a) - _u) * (getProb(_b) - _u) >= 0)
    {
        _a = 0;
        _b = probabilities.size();
    }

    double c = _a;
    while(abs(_a - _b) > 1)
    {
        c = round((_a + _b) / 2);
        //cout << "Root finding: " << c << " " << getProb(c) << endl;
        double d;

        if(_u > getProb(c) && _u <= getProb(c+1))
            return c+1;

        if((getProb(c)-_u) * (getProb(_a)-_u) < 0)
        {
            _b = c;
            //cout << "b " << b << endl;
        }
        else
        {
            _a = c;
            //cout << "a " << a << endl;
        }
    }

    //return c;
}


void MultinomialDistribution::setProbabilities(vector<double> _probabilities)
{
    probabilities = _probabilities;
    for(unsigned i=0; i<probabilities.size(); ++i)
    {
        if(i>0)
            probabilities.at(i) = probabilities.at(i) + probabilities.at(i-1);
        probMap[i] = probabilities.at(i);
    }
}

vector<double> &MultinomialDistribution::getProbabilities()
{
    return probabilities;
}

map<int, double> &MultinomialDistribution::getProbMap()
{
    return probMap;
}
