#ifndef MULTINOMIALDISTRIBUTION_H_INCLUDED
#define MULTINOMIALDISTRIBUTION_H_INCLUDED

#include <vector>
#include <map>

using std::vector;
using std::map;

class MultinomialDistribution
{
public:
     MultinomialDistribution(vector<double> _probabilities);
    ~MultinomialDistribution();

    int drawNumber(double _rn);
    double getProb(int _n);
    int bisection(int _n1, int _n2, double _u);

    void setProbabilities(vector<double> _probabilities);
    vector<double> &getProbabilities();
    map<int, double> &getProbMap();

private:
    vector<double> probabilities;
    map<int, double> probMap;
};

#endif // MULTINOMIALDISTRIBUTION_H_INCLUDED
