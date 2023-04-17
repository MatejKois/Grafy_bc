#include "../../Headers/Algorithms/LabelSet.h"
#include "../../Headers/Algorithms/heap.h"

namespace Grafy
{
    void LabelSet::calculate(DistanceMatrix& matrix)
    {
        for (int rowStartNode = 1; rowStartNode <= matrix.size(); ++rowStartNode)
        {
            int current = rowStartNode;
            Heap heap;

            heap.push(0, current);
            while (!heap.empty())
            {
                current = heap.pop();

                for (int endNode = 1; endNode <= matrix.size(); ++endNode)
                {
                    //			                   no edge from current to endNode
                    if (rowStartNode == endNode || matrix.dist(current, endNode) <= 0)
                    {
                        continue;
                    }

                    if (matrix.dist(rowStartNode, endNode) <= 0
                        ||
                        matrix.dist(rowStartNode, endNode) >=
                        matrix.dist(rowStartNode, current) + matrix.dist(current, endNode))
                    {
                        matrix.dist(rowStartNode, endNode) =
                                matrix.dist(rowStartNode, current) + matrix.dist(current, endNode);
                        heap.push(matrix.dist(rowStartNode, endNode), endNode);
                    }
                }
            }
        }
    }
}
