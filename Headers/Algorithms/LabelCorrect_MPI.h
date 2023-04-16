#ifndef GRAFY_LABELCORRECT_MPI_H
#define GRAFY_LABELCORRECT_MPI_H


#include "Algorithm.h"
#include "../Matrix/DistanceMatrix.h"

class LabelCorrect_MPI : public Algorithm
{
public:
    void calculate(DistanceMatrix& matrix) override;
};


#endif //GRAFY_LABELCORRECT_MPI_H
