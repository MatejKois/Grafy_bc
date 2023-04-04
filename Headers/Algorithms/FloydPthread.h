#ifndef GRAFY_FLOYDPTHREAD_H
#define GRAFY_FLOYDPTHREAD_H

#include <pthread.h>
#include "Algorithm.h"

typedef struct floydArgs
{
    DistanceMatrix* matrix;
    int* assigned;
    pthread_mutex_t* mutex;
} FLOYD_ARGS;

class FloydPthread : public Algorithm
{
public:
    void calculate(DistanceMatrix& matrix) override;

private:
    static void* assignThreads(void* args);
};

#endif //GRAFY_FLOYDPTHREAD_H
