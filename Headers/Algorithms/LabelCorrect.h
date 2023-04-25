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

        void calculate(DistanceMatrix& matrix) override
        {};

        void calculate(const std::string& graphFileName, bool doCheck) override
        {};
    };
}


#endif //GRAFY_LABELCORRECT_H
