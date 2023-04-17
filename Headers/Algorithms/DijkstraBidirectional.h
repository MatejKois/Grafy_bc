#ifndef GRAFY_DIJKSTRABIDIRECTIONAL_H
#define GRAFY_DIJKSTRABIDIRECTIONAL_H


#include "Algorithm.h"
#include "heap.h"
#include <pthread.h>

namespace Grafy
{
    class DijkstraBidirectional : public Algorithm
    {
    public:
        void calculate(DistanceMatrix& matrix) override;

        static int calculateDistance(DistanceMatrix& matrix, int a, int b);
    };
}


#endif //GRAFY_DIJKSTRABIDIRECTIONAL_H
