#ifndef GRAFY_LABELSETPTHREAD_H
#define GRAFY_LABELSETPTHREAD_H


#include "Algorithm.h"
#include "LabelCorrectPthread.h"

namespace Grafy
{
    class LabelSetPthread : public Algorithm
    {
    public:
        void calculate(DistanceMatrix& matrix) override;

    private:
        static void* calculateByRow(void* args);
    };
}


#endif //GRAFY_LABELSETPTHREAD_H
