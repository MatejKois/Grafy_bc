#ifndef GRAFY_LABELCORRECTPTHREAD_H
#define GRAFY_LABELCORRECTPTHREAD_H

#include <pthread.h>
#include "Algorithm.h"

namespace Grafy
{
    /// @brief arguments shared by all threads
    typedef struct dijkstraArgs
    {
        EdgesList* graph;

        DistanceMatrix* resultMatrix;

        /// @brief this counts how many vertices have been assigned to all threads
        int* assigned;

        pthread_mutex_t* mutex;
    } DIJKSTRA_ARGS;

    class LabelCorrectPthread : public Algorithm
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


#endif //GRAFY_LABELCORRECTPTHREAD_H
