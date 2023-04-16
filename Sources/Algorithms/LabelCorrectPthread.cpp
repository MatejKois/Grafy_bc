#include "../../Headers/Algorithms/LabelCorrectPthread.h"
#include <stack>

#define DIJKSTRA_MAX_THREADS 4

void LabelCorrectPthread::calculate(DistanceMatrix& matrix)
{
    pthread_t threads[DIJKSTRA_MAX_THREADS];
    pthread_mutex_t mutex;

    pthread_mutex_init(&mutex, nullptr);

    int* assigned = new int;
    *assigned = 1;

    DIJKSTRA_ARGS args = {
            &matrix,
            assigned,
            &mutex
    };

    for (int i = 0; i < DIJKSTRA_MAX_THREADS; ++i)
    {
        pthread_create(&threads[i], nullptr, &calculateByRow, &args);
    }
    for (int i = 0; i < DIJKSTRA_MAX_THREADS; ++i)
    {
        pthread_join(threads[i], nullptr);
    }

    pthread_mutex_destroy(&mutex);

    delete assigned;
}

void* LabelCorrectPthread::calculateByRow(void* args)
{
    auto* dijkstraArgs = static_cast<DIJKSTRA_ARGS*>(args);
    std::stack<int> stack;

    while (true)
    {
        pthread_mutex_lock(dijkstraArgs->mutex);
        if (*dijkstraArgs->assigned > dijkstraArgs->matrix->size())
        {
            pthread_mutex_unlock(dijkstraArgs->mutex);
            break;
        }
        int rowStartNode = (*dijkstraArgs->assigned)++;
        pthread_mutex_unlock(dijkstraArgs->mutex);

        int processedNode = rowStartNode;
        stack.push(processedNode);
        while (!stack.empty())
        {
            processedNode = stack.top();
            stack.pop();

            for (int endNode = 1; endNode <= dijkstraArgs->matrix->size(); ++endNode)
            {
                if (rowStartNode == endNode || dijkstraArgs->matrix->dist(processedNode, endNode) <= 0)
                {
                    continue;
                }

                if (dijkstraArgs->matrix->dist(rowStartNode, endNode) <= 0
                    ||
                    dijkstraArgs->matrix->dist(rowStartNode, endNode) >=
                    dijkstraArgs->matrix->dist(rowStartNode, processedNode) +
                    dijkstraArgs->matrix->dist(processedNode, endNode))
                {
                    dijkstraArgs->matrix->dist(rowStartNode, endNode) =
                            dijkstraArgs->matrix->dist(rowStartNode, processedNode) +
                            dijkstraArgs->matrix->dist(processedNode, endNode);
                    stack.push(endNode);
                }
            }
        }
    }

    return nullptr;
}
