#ifndef GRAFY_LABELSET_H
#define GRAFY_LABELSET_H


#include "Algorithm.h"

namespace Grafy
{
    class LabelSet : public Algorithm
    {
    public:
        void calculate(EdgesList& graph, DistanceMatrix& resultMatrix) override;

        void calculate(DistanceMatrix& matrix) override
        {};

        void calculate(const std::string& graphFileName, bool doCheck) override
        {};
    };
}


#endif //GRAFY_LABELSET_H
