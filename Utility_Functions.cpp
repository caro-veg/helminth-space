#include <iostream>
#include <functional>
#include "Utility_Functions.h"

using namespace std;
using namespace std::placeholders;



//function to find median in different dimensions of coordinate vector
shared_ptr<Node> findMedian(vector<shared_ptr<Node> > _a, int _dim)
{
    if(_dim == 0)
    {
        nth_element(_a.begin(), _a.begin() + _a.size()/2, _a.end(), [](shared_ptr<Node> _b, shared_ptr<Node> _c)
            {
                return(_b->getCoordinates().at(0) < _c->getCoordinates().at(0));
            });
    }
    else if(_dim == 1)
    {
        nth_element(_a.begin(),_a.begin() + _a.size()/2, _a.end(), [](shared_ptr<Node> _b, shared_ptr<Node> _c)
            {
                return(_b->getCoordinates().at(1) < _c->getCoordinates().at(1));
            });
    }
    else
    {
        cout << "Coordinates can only be two-dimensional." << endl;
        exit(1);
    }

    return(_a.at(_a.size()/2));
};

