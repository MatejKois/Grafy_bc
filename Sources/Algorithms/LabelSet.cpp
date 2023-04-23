#include "../../Headers/Algorithms/LabelSet.h"
#include "../../Headers/GraphStructures/heap.h"

namespace Grafy
{
    void LabelSet::calculate(EdgesList& graph, DistanceMatrix& resultMatrix)
    {
        for (int rowStartNode = 1; rowStartNode <= graph.numVertices(); ++rowStartNode)
        {
            int current = rowStartNode;
            Heap heap;

            heap.push(0, current);
            while (!heap.empty())
            {
                current = heap.pop();

                for (int positionInEdgesList = graph.startPositions()[current];
                     positionInEdgesList < graph.startPositions()[current + 1];
                     ++positionInEdgesList)
                {
                    int endNode = graph[3 * positionInEdgesList + 1];
                    int processedEdgeWeight = graph[3 * positionInEdgesList + 2];

                    if (resultMatrix.dist(rowStartNode, endNode) >
                        resultMatrix.dist(rowStartNode, current) + processedEdgeWeight)
                    {
                        resultMatrix.dist(rowStartNode, endNode) =
                                resultMatrix.dist(rowStartNode, current) + processedEdgeWeight;
                        heap.push(resultMatrix.dist(rowStartNode, endNode), endNode);
                    }
                }
            }
        }
    }
}
