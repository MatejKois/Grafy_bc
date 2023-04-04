#include "../../Headers/Algorithms/FloydPthread.h"

#define FLOYD_MAX_THREADS 4

void FloydPthread::calculate(DistanceMatrix& matrix)
{
    pthread_t threads[FLOYD_MAX_THREADS];
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, nullptr);

    int* assigned = new int;
    *assigned = 1;

    FLOYD_ARGS args = {
            &matrix,
            assigned,
            &mutex
    };

    for (int i = 0; i < FLOYD_MAX_THREADS; ++i)
    {
        pthread_create(&threads[i], nullptr, &assignThreads, &args);
    }
    for (int i = 0; i < FLOYD_MAX_THREADS; ++i)
    {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);

    delete assigned;
}

void* FloydPthread::assignThreads(void* args)
{
    auto* floydArgs = static_cast<FLOYD_ARGS*>(args);

    while (true)
    {
        pthread_mutex_lock(floydArgs->mutex);
        if (*floydArgs->assigned > floydArgs->matrix->size())
        {
            pthread_mutex_unlock(floydArgs->mutex);
            break;
        }
        int k = (*floydArgs->assigned)++;
        pthread_mutex_unlock(floydArgs->mutex);

        for (int startNode = 1; startNode <= floydArgs->matrix->size(); ++startNode)
        {
            for (int endNode = 1; endNode <= floydArgs->matrix->size(); ++endNode)
            {
                if (startNode != endNode
                    && floydArgs->matrix->dist(startNode, k) != 0
                    && floydArgs->matrix->dist(k, endNode) != 0
                    && (floydArgs->matrix->dist(startNode, endNode) == 0
                        || floydArgs->matrix->dist(startNode, endNode) >
                           floydArgs->matrix->dist(startNode, k) + floydArgs->matrix->dist(k, endNode)))
                {
                    pthread_mutex_lock(floydArgs->mutex);
                    floydArgs->matrix->dist(startNode, endNode) =
                            floydArgs->matrix->dist(startNode, k) + floydArgs->matrix->dist(k, endNode);
                    pthread_mutex_unlock(floydArgs->mutex);
                }
            }
        }
    }
    return nullptr;
}
