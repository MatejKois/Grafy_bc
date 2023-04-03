#include <mpi.h>
#include <stack>

#include "../../Headers/Algorithms/DijkstraMPI.h"

// poslat ostatnym procesom len tie data ktore potrebuju

void DijkstraMPI::calculate(DistanceMatrix& matrix)
{
    MPI_Init(nullptr, nullptr);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int start = rank * (matrix.size() / size) + 1;
    int end = (rank == size - 1) ? matrix.size() : (rank + 1);

    int range = end - start + 1;
    DistanceMatrix partialMatrix(range, matrix.size());
    int current;

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Scatter(matrix.data(), range * matrix.size(), MPI_INT, partialMatrix.data(), range * matrix.size(), MPI_INT, 0,
                MPI_COMM_WORLD);

    for (int startNode = start; startNode <= end; ++startNode)
    {
        current = startNode;
        std::stack<int> stack;

        stack.push(current);
        while (!stack.empty())
        {
            current = stack.top();
            stack.pop();

            for (int j = 1; j <= matrix.size(); ++j)
            {
                // No edge from current to j
                if (startNode == j || matrix.dist(current, j) <= 0)
                {
                    continue;
                }

                if (partialMatrix.dist(startNode - start, j) <= 0 || partialMatrix.dist(startNode - start, j) >=
                                                                     matrix.dist(startNode, current) +
                                                                     matrix.dist(current, j))
                {
                    partialMatrix.dist(startNode - start, j) =
                            matrix.dist(startNode, current) + matrix.dist(current, j);
                    stack.push(j);
                }
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    MPI_Reduce(partialMatrix.data(), matrix.data(), matrix.size() * matrix.size(), MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

    MPI_Finalize();
}
