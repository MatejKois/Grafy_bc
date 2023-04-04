#ifndef GRAFY_DIJKSTRAPTHREAD_H
#define GRAFY_DIJKSTRAPTHREAD_H

#include <pthread.h>
#include "Algorithm.h"

typedef struct dijkstraArgs
{
    DistanceMatrix* matrix;
    int* assigned;
    pthread_mutex_t* mutex;
} DIJKSTRA_ARGS;

class DijkstraPthread : public Algorithm
{
public:
    void calculate(DistanceMatrix& matrix) override;

private:
    static void* calculateByRow(void* args);
};


#endif //GRAFY_DIJKSTRAPTHREAD_H
