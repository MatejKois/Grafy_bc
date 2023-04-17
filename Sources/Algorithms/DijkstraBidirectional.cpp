#include "../../Headers/Algorithms/DijkstraBidirectional.h"
#include <pthread.h>

#define INFTY 9999999

namespace Grafy
{
    void DijkstraBidirectional::calculate(DistanceMatrix& matrix)
    {
        for (int y = 1; y <= matrix.size(); ++y)
        {
            for (int x = 1; x <= matrix.size(); ++x)
            {
                if (y != x)
                {
                    matrix.dist(y, x) = calculateDistance(matrix, y, x);
                }
            }
        }
    }

    int DijkstraBidirectional::calculateDistance(DistanceMatrix& matrix, int a, int b)
    {
        Heap prioQueueForward;
        Heap prioQueueBackward;
        int u, v;
        int mu = INFTY;
        bool processedForward[matrix.size() + 1];
        bool processedBackward[matrix.size() + 1];
        int distancesForward[matrix.size() + 1];
        int distancesBackward[matrix.size() + 1];
        for (int i = 0; i <= matrix.size(); ++i)
        {
            processedForward[i] = false;
            processedBackward[i] = false;
            distancesForward[i] = INFTY;
            distancesBackward[i] = INFTY;
        }
        distancesForward[a] = 0;
        distancesBackward[b] = 0;

        prioQueueForward.push(0, a);
        prioQueueBackward.push(0, b);

        while (!prioQueueForward.empty() && !prioQueueBackward.empty())
        {
            u = prioQueueForward.pop();
            v = prioQueueBackward.pop();
            processedForward[u] = true;
            processedBackward[v] = true;
            for (int i = 1; i <= matrix.size(); ++i)
            {
                if (u == i || matrix.dist(u, i) <= 0)
                { // no edge
                    continue;
                }
                if (!processedForward[i]
                    && distancesForward[i] > distancesForward[u] + matrix.dist(u, i))
                {
                    distancesForward[i] = distancesForward[u] + matrix.dist(u, i);
                    prioQueueForward.push(distancesForward[i], i);
                }
                if (processedBackward[i]
                    && distancesForward[u] + matrix.dist(u, i) + distancesBackward[i] < mu)
                {
                    mu = distancesForward[u] + matrix.dist(u, i) + distancesBackward[i];
                }
            }
            for (int i = 1; i <= matrix.size(); ++i)
            {
                if (v == i || matrix.dist(v, i) <= 0)
                { // no edge
                    continue;
                }
                if (!processedBackward[i]
                    && distancesBackward[i] > distancesBackward[v] + matrix.dist(v, i))
                {
                    distancesBackward[i] = distancesBackward[v] + matrix.dist(v, i);
                    prioQueueBackward.push(distancesBackward[i], i);
                }
                if (processedForward[i]
                    && distancesBackward[v] + matrix.dist(v, i) + distancesForward[v] < mu)
                {
                    mu = distancesBackward[v] + matrix.dist(v, i) + distancesForward[v];
                }
            }
            if (distancesForward[u] + distancesBackward[v] >= mu)
            {
                return mu;
            }
        }
    }
}
