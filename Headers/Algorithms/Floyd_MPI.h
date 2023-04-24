#ifndef GRAFY_FLOYD_MPI_H
#define GRAFY_FLOYD_MPI_H


#include "Algorithm.h"
#include "../GraphStructures/DistanceMatrix.h"

namespace Grafy
{
    class Floyd_MPI : public Algorithm
    {
    public:
        void calculate(const std::string& graphFileName) override;
    };
}


#endif //GRAFY_FLOYD_MPI_H
