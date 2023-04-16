#ifndef GRAFY_LABELCORRECT_MPI_H
#define GRAFY_LABELCORRECT_MPI_H


#include "Algorithm.h"
#include "../Matrix/DistanceMatrix.h"

class LabelCorrect_MPI : public Algorithm
{
public:
    static void calculate(DistanceMatrix& matrix, const std::string& graphFileName);
};


#endif //GRAFY_LABELCORRECT_MPI_H
