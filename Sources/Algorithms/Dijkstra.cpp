#include "../../Headers/Algorithms/Dijkstra.h"
#include <stack>

void Dijkstra::calculate(DistanceMatrix& matrix)
{
    for (int rowStartNode = 1; rowStartNode <= matrix.size(); ++rowStartNode)
    {
        int current = rowStartNode;
        std::stack<int> stack;

        stack.push(current);
        while (!stack.empty())
        {
            current = stack.top();
            stack.pop();

            for (int endNode = 1; endNode <= matrix.size(); ++endNode)
            {
                //			  no edge from current to endNode
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
                    stack.push(endNode);
                }
            }
        }
    }
}
