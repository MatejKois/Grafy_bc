#ifndef GRAFY_FLOYDPTHREAD_H
#define GRAFY_FLOYDPTHREAD_H

#include <pthread.h>
#include "Algorithm.h"

namespace Grafy
{
    typedef struct floydArgs
    {
        DistanceMatrix* matrix;
        int* assigned;
        int* k;
        pthread_mutex_t* mutex;
    } FLOYD_ARGS;

    class FloydPthread : public Algorithm
    {
    public:
        void calculate(DistanceMatrix& matrix) override;

        void calculate(EdgesList& graph, DistanceMatrix& resultMatrix) override
        {};

        void calculate(const std::string& graphFileName, bool doCheck) override
        {};

    private:
        static void* assignThreads(void* args);
    };
}

#endif //GRAFY_FLOYDPTHREAD_H
