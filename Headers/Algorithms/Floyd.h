#ifndef GRAFY_FLOYD_H
#define GRAFY_FLOYD_H


#include "Algorithm.h"

namespace Grafy
{
    class Floyd : public Algorithm
    {
    public:
        void calculate(DistanceMatrix& matrix) override;

        void calculate(EdgesList& graph, DistanceMatrix& resultMatrix) override
        {};

        void calculate(const std::string& graphFileName, bool doCheck) override
        {};
    };
}


#endif //GRAFY_FLOYD_H
