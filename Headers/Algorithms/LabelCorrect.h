#ifndef GRAFY_LABELCORRECT_H
#define GRAFY_LABELCORRECT_H


#include "Algorithm.h"
#include "../Matrix/DistanceMatrix.h"

namespace Grafy
{
    class LabelCorrect : public Algorithm
    {
    public:
        void calculate(DistanceMatrix& matrix) override;
    };
}


#endif //GRAFY_LABELCORRECT_H
