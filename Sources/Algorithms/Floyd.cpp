#include "../../Headers/Algorithms/Floyd.h"

void Floyd::calculate(DistanceMatrix& matrix)
{
    for (int k = 1; k <= matrix.size(); ++k)
    {
        for (int y = 1; y <= matrix.size(); ++y)
        {
            for (int x = 0; x <= matrix.size(); ++x)
            {
                if (y != x
                    && matrix.dist(y, k) != 0
                    && matrix.dist(k, x) != 0
                    && (matrix.dist(y, x) == 0
                        || matrix.dist(y, x) > matrix.dist(y, k) + matrix.dist(k, x)))
                {
                    matrix.dist(y, x) = matrix.dist(y, k) + matrix.dist(k, x);
                }
            }
        }
    }
}
