#include "../../Headers/Algorithms/Floyd.h"

void Floyd::calculate(DistanceMatrix& matrix)
{
    for (int k = 1; k <= matrix.size(); ++k)
    {
        for (int startNode = 1; startNode <= matrix.size(); ++startNode)
        {
            for (int endNode = 1; endNode <= matrix.size(); ++endNode)
            {
                if (startNode != endNode
                    && matrix.dist(startNode, k) != 0
                    && matrix.dist(k, endNode) != 0
                    && (matrix.dist(startNode, endNode) == 0
                        || matrix.dist(startNode, endNode) > matrix.dist(startNode, k) + matrix.dist(k, endNode)))
                {
                    matrix.dist(startNode, endNode) = matrix.dist(startNode, k) + matrix.dist(k, endNode);
                }
            }
        }
    }
}
