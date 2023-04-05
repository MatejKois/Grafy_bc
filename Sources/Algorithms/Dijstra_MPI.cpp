#include <mpi.h>
#include <stack>

#include "../../Headers/Algorithms/DijkstraMPI.h"

void DijkstraMPI::calculate(DistanceMatrix& matrix)
{
    MPI_Init(nullptr, nullptr);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::cout << "Rank: " << rank << ", size: " << size << "\n";

    const int matrixSize = matrix.size() + 1;
    const int rowsPerProcess = matrixSize / size;
    int* graphBcast = new int[matrixSize * matrixSize];

    if (rank == 0)
    {
        for (int y = 0; y < matrixSize; ++y)
        {
            for (int x = 0; x < matrixSize; ++x)
            {
                graphBcast[y * matrixSize + x] = matrix.dist(y, x);
            }
        }
    }

    int* rowData = new int[matrixSize * rowsPerProcess];
    MPI_Bcast(graphBcast, matrixSize * matrixSize, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(graphBcast, matrixSize * matrixSize, MPI_INT, rowData, matrixSize * rowsPerProcess, MPI_INT, 0,
                MPI_COMM_WORLD);

    for (int indexInScatteredRows = 1; indexInScatteredRows < rowsPerProcess; indexInScatteredRows++)
    {
        // row start node is located at the start of the row
        int rowStartNode = rowData[indexInScatteredRows * matrixSize];
        int current = rowStartNode;
        std::stack<int> stack;

        stack.push(current);
        while (!stack.empty())
        {
            current = stack.top();
            stack.pop();

            for (int endNode = 1; endNode < matrixSize; ++endNode)
            {
                //               			   no edge from current to endNode
                if (rowStartNode == endNode || graphBcast[current * matrixSize + endNode] <= 0)
                {
                    continue;
                }

                if (rowData[indexInScatteredRows * matrixSize + endNode] <= 0
                    ||
                    rowData[indexInScatteredRows * matrixSize + endNode] >=
                    rowData[indexInScatteredRows * matrixSize + current] + graphBcast[current * matrixSize + endNode])
                {
                    rowData[indexInScatteredRows * matrixSize + endNode] =
                            rowData[indexInScatteredRows * matrixSize + current] +
                            graphBcast[current * matrixSize + endNode];
                    stack.push(endNode);
                }
            }
        }
    }

    int* finalMatrix = nullptr;
    if (rank == 0)
    {
        finalMatrix = new int[matrixSize * matrixSize];
    }

    MPI_Gather(rowData, matrixSize * rowsPerProcess, MPI_INT, finalMatrix, matrixSize * matrixSize, MPI_INT, 0,
               MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                matrix.dist(i, j) = finalMatrix[i * matrixSize + j];
            }
        }
    }

    delete[] rowData;
    delete[] graphBcast;
    delete[] finalMatrix;

    MPI_Finalize();
}
