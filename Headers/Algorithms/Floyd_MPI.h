#ifndef GRAFY_FLOYD_MPI_H
#define GRAFY_FLOYD_MPI_H


#include "Algorithm.h"
#include "../GraphStructures/DistanceMatrix.h"

namespace Grafy
{
    class Floyd_MPI : public Algorithm
    {
    public:
        void calculate(const std::string& graphFileName, bool doCheck) override;

        void calculate(DistanceMatrix& matrix) override
        {};

        void calculate(EdgesList& graph, DistanceMatrix& resultMatrix) override
        {};
    };
}


#endif //GRAFY_FLOYD_MPI_H
