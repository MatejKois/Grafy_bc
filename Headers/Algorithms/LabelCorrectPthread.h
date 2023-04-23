#ifndef GRAFY_LABELCORRECTPTHREAD_H
#define GRAFY_LABELCORRECTPTHREAD_H

#include <pthread.h>
#include "Algorithm.h"

namespace Grafy
{
    typedef struct dijkstraArgs
    {
        EdgesList* graph;
        DistanceMatrix* resultMatrix;
        int* assigned;
        pthread_mutex_t* mutex;
    } DIJKSTRA_ARGS;

    class LabelCorrectPthread : public Algorithm
    {
    public:
        void calculate(EdgesList& graph, DistanceMatrix& resultMatrix) override;

    private:
        static void* calculateByRow(void* args);
    };
}


#endif //GRAFY_LABELCORRECTPTHREAD_H
