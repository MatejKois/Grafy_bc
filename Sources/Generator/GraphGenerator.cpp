#include "../../Headers/Generator/GraphGenerator.h"
#include <random>

namespace Grafy
{
    void GraphGenerator::generate(DistanceMatrix& matrix, int distanceMin, int distanceMax, int edgesToAddCount)
    {
        int verticesCount = matrix.size();
        int** allEdges = new int* [verticesCount * verticesCount]; //complete graph will be stored here
        for (int i = 0; i < verticesCount * verticesCount; ++i)
        {
            allEdges[i] = new int[3];
        }

        makeCompleteGraph(verticesCount, distanceMin, distanceMax, allEdges);
        quickSortArray(allEdges, 0, verticesCount * verticesCount);
        makeTree(matrix, allEdges, verticesCount, distanceMin, distanceMax);
        addMoreEdges(matrix, allEdges, verticesCount, edgesToAddCount);

        for (int i = 0; i < verticesCount * verticesCount; ++i)
        {
            delete[] allEdges[i];
        }
        delete[] allEdges;
    }

    void GraphGenerator::makeCompleteGraph(int verticesCount, int distanceMin, int distanceMax, int** array)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> randDist(distanceMin, distanceMax);

        for (int y = 1; y <= verticesCount; ++y)
        {
            for (int x = 1; x <= verticesCount; ++x)
            {
                // calculating array indexes, so the edges are sorted
                int arrIndex1 = (x - 1) + (y - 1) * verticesCount;
                int arrIndex2 = (y - 1) + (x - 1) * verticesCount; // for reverse edge
                array[arrIndex1][0] = y;
                array[arrIndex1][1] = x;

                int randWeight = randDist(mt); // random edge weight
                if (y != x)
                {
                    array[arrIndex1][2] = randWeight;
                    array[arrIndex2][2] = randWeight;
                } else
                {
                    array[arrIndex1][2] = distanceMax + 1;
                    array[arrIndex2][2] = distanceMax + 1;
                }
            }
        }
    }

    void GraphGenerator::quickSortArray(int** array, int left, int right)
    {
        if (left < right)
        {
            int boundary = left;
            for (int i = left + 1; i < right; i++)
            {
                if (array[i][2] < array[left][2])
                {
                    swap(array, i, ++boundary);
                }
            }
            swap(array, left, boundary);
            quickSortArray(array, left, boundary);
            quickSortArray(array, boundary + 1, right);
        }
    }

    void GraphGenerator::swap(int** array, int left, int right)
    {
        int tmp[3];
        tmp[0] = array[right][0];
        tmp[1] = array[right][1];
        tmp[2] = array[right][2];

        array[right][0] = array[left][0];
        array[right][1] = array[left][1];
        array[right][2] = array[left][2];
        array[left][0] = tmp[0];
        array[left][1] = tmp[1];
        array[left][2] = tmp[2];
    }

    void GraphGenerator::makeTree(DistanceMatrix& matrix, int** sortedEdges, int verticesCount, int distanceMin,
                                  int distanceMax)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> randDist(distanceMin, distanceMax);

        int* componentId = new int[verticesCount + 1];
        int selectedCount = 0;

        for (int i = 1; i <= verticesCount; ++i)
        {
            componentId[i] = i;
        }

        for (int i = 0; i < verticesCount * verticesCount; ++i)
        {
            if (selectedCount >= verticesCount - 1)
            {
                break;
            }

            int v1 = sortedEdges[i][0];
            int v2 = sortedEdges[i][1];
            int weight = sortedEdges[i][2];

            if (componentId[v1] != componentId[v2])
            {
                ++selectedCount;

                // edge weight must be generated again, as the weights int sortedEdges are sorted and would all be minimal in large graphs
                int randWeight = randDist(mt);
                matrix.dist(v1, v2) = randWeight;
                matrix.dist(v2, v1) = randWeight;

                int oldId = componentId[v1] > componentId[v2] ? componentId[v1] : componentId[v2];
                int newId = componentId[v1] < componentId[v2] ? componentId[v1] : componentId[v2];

                for (int j = 1; j <= verticesCount; ++j)
                {
                    componentId[j] = componentId[j] == oldId ? newId : componentId[j];
                }
            }
        }
        delete[] componentId;
    }

    void GraphGenerator::addMoreEdges(DistanceMatrix& matrix, int** allEdges, int verticesCount, int edgesToAddCount)
    {
        std::random_device rd;
        std::mt19937 mt(rd());
        std::uniform_int_distribution<int> randDist(0, verticesCount * verticesCount - 1);
        while (edgesToAddCount > 0)
        {
            int indexInAllEdges = randDist(mt);
            int v1 = allEdges[indexInAllEdges][0];
            int v2 = allEdges[indexInAllEdges][1];
            int weight = allEdges[indexInAllEdges][2];
            if (v1 != v2 && matrix.dist(v1, v2) != weight)
            {
                matrix.dist(v1, v2) = weight;
                --edgesToAddCount;
            }
        }
    }
}
