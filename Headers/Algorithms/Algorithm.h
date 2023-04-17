#ifndef GRAFY_ALGORITHM_H
#define GRAFY_ALGORITHM_H


#include <string>
#include "../Matrix/DistanceMatrix.h"

namespace Grafy
{
    class Algorithm
    {
    public:
        virtual ~Algorithm() = default;

        virtual void calculate(DistanceMatrix& matrix)
        {};

        virtual void calculate(DistanceMatrix& matrix, const std::string& graphFileName)
        {};
    };
}


#endif //GRAFY_ALGORITHM_H
