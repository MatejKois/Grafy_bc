#include "../../Headers/Generator/GraphMerger.h"
#include <cmath>
#include <random>

void GraphMerger::merge(DistanceMatrix& matrix1, DistanceMatrix& matrix2, DistanceMatrix& merged, int bridgesToAddcount,
                        int distanceMin, int distanceMax)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> randDistDistance(distanceMin, distanceMax);

    // will be used for adding random bridges - first vertex is selected from the first graph
    std::uniform_int_distribution<int> randDistV1(1, matrix1.size());

    // second vertex is selected from the second graph
    std::uniform_int_distribution<int> randDistV2(matrix1.size() + 1, merged.size());

    // first matrix is copied into the merged matrix
    for (int y = 0; y <= matrix1.size(); ++y)
    {
        for (int x = 0; x <= matrix1.size(); ++x)
        {
            merged.dist(y, x) = matrix1.dist(y, x);
        }
    }
    // second matrix is copied as well, but with the vertex numbers offset
    for (int y = 1; y <= matrix2.size(); ++y)
    {
        for (int x = 1; x <= matrix2.size(); ++x)
        {
            merged.dist(y + matrix1.size(), x + matrix1.size()) = matrix2.dist(y, x);
        }
    }

    // adding random bridges to connect the two graphs
    for (int i = 0; i < bridgesToAddcount; ++i)
    {
        int v1 = randDistV1(mt);
        int v2 = randDistV2(mt);
        int randDistance = randDistDistance(mt);
        merged.dist(v1, v2) = randDistance;
        merged.dist(v2, v1) = randDistance;
    }
}
