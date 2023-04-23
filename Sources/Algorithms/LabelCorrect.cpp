#include "../../Headers/Algorithms/LabelCorrect.h"
#include <stack>

namespace Grafy
{
    void LabelCorrect::calculate(EdgesList& graph, DistanceMatrix& resultMatrix)
    {
        for (int rowStartNode = 1; rowStartNode <= graph.numVertices(); ++rowStartNode)
        {
            int current = rowStartNode;
            std::stack<int> stack;

            stack.push(current);
            while (!stack.empty())
            {
                current = stack.top();
                stack.pop();

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
                        stack.push(endNode);
                    }
                }
            }
        }
    }
}
