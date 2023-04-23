#ifndef GRAFY_LABELSET_H
#define GRAFY_LABELSET_H


#include "Algorithm.h"

namespace Grafy
{
    class LabelSet : public Algorithm
    {
    public:
        void calculate(EdgesList& graph, DistanceMatrix& resultMatrix) override;
    };
}


#endif //GRAFY_LABELSET_H
