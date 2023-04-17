#ifndef GRAFY_FLOYD_H
#define GRAFY_FLOYD_H


#include "Algorithm.h"

namespace Grafy
{
    class Floyd : public Algorithm
    {
    public:
        void calculate(DistanceMatrix& matrix) override;
    };
}


#endif //GRAFY_FLOYD_H
