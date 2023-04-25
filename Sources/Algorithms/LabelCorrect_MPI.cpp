#include <chrono>
#include <mpi.h>
#include <stack>

#include "../../Headers/Algorithms/LabelCorrect.h"
#include "../../Headers/Algorithms/LabelCorrect_MPI.h"
#include "../../Headers/Parser/Parser.h"

namespace Grafy
{
    void LabelCorrect_MPI::calculate(const std::string& graphFileName, bool doCheck)
    {
        MPI_Init(nullptr, nullptr);

        int mpiRank, mpiSize;
        MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
        MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

        auto start = std::chrono::high_resolution_clock::now();

        int* edgesCount = new int{0};
        int* verticesCount = new int{0};

        if (mpiRank == 0)
        {
            start = std::chrono::high_resolution_clock::now();
            Parser::countEdgesAndVertices(graphFileName, *edgesCount, *verticesCount);
        }

        MPI_Bcast(edgesCount, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(verticesCount, 1, MPI_INT, 0, MPI_COMM_WORLD);

        EdgesList edgesList(*edgesCount, *verticesCount);

        if (mpiRank == 0)
        {
            Parser::parse(graphFileName, edgesList);
        }

        int* listOfEdges = edgesList.list();
        int* startPositionsOfEdges = edgesList.startPositions();

        MPI_Bcast(listOfEdges, *edgesCount * 3, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(startPositionsOfEdges, *verticesCount + 2, MPI_INT, 0, MPI_COMM_WORLD);

        const int matrixSizeColumns = *verticesCount + 1;
        const int rowsPerProcess = matrixSizeColumns % mpiSize == 0 ?
                                   matrixSizeColumns / mpiSize :
                                   matrixSizeColumns / mpiSize + matrixSizeColumns % mpiSize;

        int* rowsAssignedToProcess = new int[rowsPerProcess * matrixSizeColumns];
        for (int y = 0; y < rowsPerProcess; ++y)
        {
            for (int x = 0; x < matrixSizeColumns; ++x)
            {
                if (x == y + mpiRank * rowsPerProcess)
                {
                    rowsAssignedToProcess[y * matrixSizeColumns + x] = 0;
                } else
                {
                    rowsAssignedToProcess[y * matrixSizeColumns + x] = MATRIX_DIST_INF;
                }
            }
            rowsAssignedToProcess[y * matrixSizeColumns] = mpiRank * rowsPerProcess + y;
        }

        for (int indexInScatteredRows = 0; indexInScatteredRows < rowsPerProcess; indexInScatteredRows++)
        {
            // row start node is located at the start of the row
            int rowStartNode = rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns];
            int current = rowStartNode;
            std::stack<int> stack;

            stack.push(current);
            while (!stack.empty())
            {
                current = stack.top();
                stack.pop();

                for (int positionInEdgesList = startPositionsOfEdges[current];
                     positionInEdgesList < startPositionsOfEdges[current + 1];
                     ++positionInEdgesList)
                {
                    int endNode = listOfEdges[3 * positionInEdgesList + 1];
                    int processedEdgeWeight = listOfEdges[3 * positionInEdgesList + 2];

                    if (rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + endNode] >
                        rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + current] +
                        processedEdgeWeight)
                    {
                        rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + endNode] =
                                rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + current] +
                                processedEdgeWeight;
                        stack.push(endNode);
                    }
                }
            }
            if (rowStartNode >= matrixSizeColumns - 1)
            {
                break;
            }
        }

        int* finalMatrix = new int[mpiSize * rowsPerProcess * matrixSizeColumns]();
        MPI_Gather(rowsAssignedToProcess, matrixSizeColumns * rowsPerProcess, MPI_INT, finalMatrix,
                   rowsPerProcess * matrixSizeColumns,
                   MPI_INT, 0,
                   MPI_COMM_WORLD);

        if (mpiRank == 0)
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start
            );
            std::cout << "LabelCorrect_MPI finished, " << duration.count() << " us elapsed\n";

            DistanceMatrix result(*verticesCount, finalMatrix);
            result.print();

            if (doCheck)
            {
                DistanceMatrix check(*verticesCount);
                LabelCorrect().calculate(edgesList, check);
                if (result == check)
                {
                    std::cout << "Matrices are equal.\n";
                } else
                {
                    std::cout << "Matrices are NOT equal!\n";
                }
            }
        }

        delete edgesCount;
        delete verticesCount;
        delete[] rowsAssignedToProcess;
        delete[] finalMatrix;

        MPI_Finalize();
    }
}
