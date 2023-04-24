#ifndef GRAFY_ALGORITHM_H
#define GRAFY_ALGORITHM_H


#include <string>
#include "../GraphStructures/DistanceMatrix.h"
#include "../GraphStructures/EdgesList.h"

#define MATRIX_DIST_INF 999999

namespace Grafy
{
    class Algorithm
    {
    public:
        virtual ~Algorithm() = default;

        virtual void calculate(DistanceMatrix& matrix)
        {};

        virtual void calculate(EdgesList& graph, DistanceMatrix& resultMatrix)
        {};

        virtual void calculate(const std::string& graphFileName)
        {};
    };
}


#endif //GRAFY_ALGORITHM_H
