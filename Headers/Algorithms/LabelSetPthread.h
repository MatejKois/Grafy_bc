#ifndef GRAFY_LABELSETPTHREAD_H
#define GRAFY_LABELSETPTHREAD_H


#include "Algorithm.h"
#include "LabelCorrectPthread.h"

namespace Grafy
{
    class LabelSetPthread : public Algorithm
    {
    public:
        void calculate(EdgesList& graph, DistanceMatrix& resultMatrix) override;

        void calculate(DistanceMatrix& matrix) override
        {};

        void calculate(const std::string& graphFileName, bool doCheck) override
        {};

    private:
        static void* calculateByRow(void* args);
    };
}


#endif //GRAFY_LABELSETPTHREAD_H
