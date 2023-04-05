#include <mpi.h>
#include <stack>

#include "../../Headers/Algorithms/DijkstraMPI.h"
#include "../../Headers/Generator/GraphGenerator.h"

void DijkstraMPI::calculate(DistanceMatrix& matrix)
{
    MPI_Init(nullptr, nullptr);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    const int matrixSize = matrix.size() + 1;
    const int rowsPerProcess = matrixSize / size;
    int* graphBcast = new int[matrixSize * matrixSize]();
//    std::cout << "Rank: " << rank << "\n";

    if (rank == 0)
    {
        GraphGenerator().generate(matrix, 2, 10);
        for (int y = 0; y < matrixSize; ++y)
        {
            for (int x = 0; x < matrixSize; ++x)
            {
                graphBcast[y * matrixSize + x] = matrix.dist(y, x);
                std::cout << graphBcast[y * matrixSize + x] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "---------------------------------\n";
    }
    MPI_Bcast(graphBcast, matrixSize * matrixSize, MPI_INT, 0, MPI_COMM_WORLD);

    int* rowData = new int[matrixSize * rowsPerProcess]();
    for (int y = 0; y < rowsPerProcess; ++y)
    {
        for (int x = 0; x < matrixSize; ++x)
        {
            rowData[y * matrixSize + x] = graphBcast[matrixSize * y
                                                     + matrixSize * rank * rowsPerProcess
                                                     + x];
        }
    }

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

    int* finalMatrix = new int[matrixSize * matrixSize]();
    MPI_Gather(rowData, matrixSize * rowsPerProcess, MPI_INT, finalMatrix, matrixSize * rowsPerProcess, MPI_INT, 0,
               MPI_COMM_WORLD);

    if (rank == 0)
    {
        for (int i = 0; i < matrixSize; i++)
        {
            for (int j = 0; j < matrixSize; j++)
            {
                std::cout << finalMatrix[i * matrixSize + j] << " ";
            }
            std::cout << "\n";
        }
    }

    delete[] rowData;
    delete[] graphBcast;
    delete[] finalMatrix;

    MPI_Finalize();
}
