#ifndef UTILITY_FUNCTIONS_H_INCLUDED
#define UTILITY_FUNCTIONS_H_INCLUDED

#include <vector>
#include <memory>
#include <algorithm>
#include "Node.h"

using std::vector;
using std::shared_ptr;


enum sex_enum {male, female};


shared_ptr<Node> findMedian(vector<shared_ptr<Node> > _a, int _dim);



#endif // UTILITY_FUNCTIONS_H_INCLUDED
