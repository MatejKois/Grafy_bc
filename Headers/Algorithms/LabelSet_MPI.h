#ifndef GRAFY_LABELSET_MPI_H
#define GRAFY_LABELSET_MPI_H


#include "Algorithm.h"
#include "../Matrix/DistanceMatrix.h"

namespace Grafy
{
    class LabelSet_MPI : public Algorithm
    {
    public:
        void calculate(DistanceMatrix& matrix, const std::string& graphFileName) override;
    };
}


#endif //GRAFY_LABELSET_MPI_H
