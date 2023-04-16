#ifndef GRAFY_ALGORITHM_H
#define GRAFY_ALGORITHM_H


#include <string>
#include "../Matrix/DistanceMatrix.h"

class Algorithm
{
public:
    virtual ~Algorithm() = default;

    virtual void calculate(DistanceMatrix& matrix) = 0;

    virtual void calculate(DistanceMatrix& matrix, const std::string& graphFileName) = 0;
};


#endif //GRAFY_ALGORITHM_H
