#ifndef GRAFY_LABELCORRECT_H
#define GRAFY_LABELCORRECT_H


#include "Algorithm.h"
#include "../GraphStructures/DistanceMatrix.h"

namespace Grafy
{
    class LabelCorrect : public Algorithm
    {
    public:
        void calculate(EdgesList& graph, DistanceMatrix& resultMatrix) override;
    };
}


#endif //GRAFY_LABELCORRECT_H
