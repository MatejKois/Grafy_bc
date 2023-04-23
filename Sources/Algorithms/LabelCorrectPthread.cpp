#include "../../Headers/Algorithms/LabelCorrectPthread.h"
#include <stack>

#define DIJKSTRA_MAX_THREADS 4

namespace Grafy
{
    void LabelCorrectPthread::calculate(EdgesList& graph, DistanceMatrix& resultMatrix)
    {
        pthread_t threads[DIJKSTRA_MAX_THREADS];
        pthread_mutex_t mutex;

        pthread_mutex_init(&mutex, nullptr);

        int* assigned = new int;
        *assigned = 1;

        DIJKSTRA_ARGS args = {
                &graph,
                &resultMatrix,
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
            if (*dijkstraArgs->assigned > dijkstraArgs->resultMatrix->size())
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

                for (int positionInEdgesList = dijkstraArgs->graph->startPositions()[processedNode];
                     positionInEdgesList < dijkstraArgs->graph->startPositions()[processedNode + 1];
                     ++positionInEdgesList)
                {
                    int endNode = (*dijkstraArgs->graph)[3 * positionInEdgesList + 1];
                    int processedEdgeWeight = (*dijkstraArgs->graph)[3 * positionInEdgesList + 2];

                    if (dijkstraArgs->resultMatrix->dist(rowStartNode, endNode) >
                        dijkstraArgs->resultMatrix->dist(rowStartNode, processedNode) + processedEdgeWeight)
                    {
                        dijkstraArgs->resultMatrix->dist(rowStartNode, endNode) =
                                dijkstraArgs->resultMatrix->dist(rowStartNode, processedNode) + processedEdgeWeight;
                        stack.push(endNode);
                    }
                }
            }
        }

        return nullptr;
    }
}

#undef DIJKSTRA_MAX_THREADS
