#ifndef GRAFY_FLOYDPTHREAD_H
#define GRAFY_FLOYDPTHREAD_H

#include <pthread.h>
#include "Algorithm.h"

namespace Grafy
{
    /// @brief arguments shared by all threads
    typedef struct floydArgs
    {
        DistanceMatrix* matrix;

        /// @brief this counts how many vertices have been assigned to all threads
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
