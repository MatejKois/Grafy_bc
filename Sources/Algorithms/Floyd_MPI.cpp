#include <chrono>
#include <cstring>
#include <mpi.h>

#include "../../Headers/Algorithms/Floyd_MPI.h"
#include "../../Headers/Parser/Parser.h"
#include "../../Headers/Algorithms/Floyd.h"

namespace Grafy
{
    void Floyd_MPI::calculate(const std::string& graphFileName, bool doCheck)
    {
//        MPI_Init(nullptr, nullptr);

        int mpiRank, mpiSize;
        MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
        MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

        auto start = std::chrono::high_resolution_clock::now();

        int* verticesCount = new int{0};

        if (mpiRank == 0)
        {
            int edgesCountDummy; // not needed for this algorithm
            Parser::countEdgesAndVertices(graphFileName, edgesCountDummy, *verticesCount);
        }

        MPI_Bcast(verticesCount, 1, MPI_INT, 0, MPI_COMM_WORLD);

        DistanceMatrix matrix(*verticesCount);

        if (mpiRank == 0)
        {
            Parser::parse(graphFileName, matrix);
            start = std::chrono::high_resolution_clock::now();
        }

        const int matrixSizeColumns = *verticesCount + 1;
        const int rowsPerProcess = matrixSizeColumns % mpiSize == 0 ?
                                   matrixSizeColumns / mpiSize :
                                   matrixSizeColumns / mpiSize + matrixSizeColumns % mpiSize;

        int* broadcastMatrix = new int[mpiSize * rowsPerProcess * matrixSizeColumns]();
        if (mpiRank == 0)
        {
            std::memcpy(broadcastMatrix, matrix.data(), matrixSizeColumns * matrixSizeColumns * sizeof(int));
        }

        int* rowsAssignedToProcess = new int[rowsPerProcess * matrixSizeColumns];


        for (int k = 1; k <= *verticesCount; ++k)
        {
            MPI_Bcast(broadcastMatrix, mpiSize * rowsPerProcess * matrixSizeColumns, MPI_INT, 0, MPI_COMM_WORLD);

            std::memcpy(rowsAssignedToProcess, broadcastMatrix + mpiRank * matrixSizeColumns * rowsPerProcess,
                        rowsPerProcess * matrixSizeColumns * sizeof(int));

            for (int indexInScatteredRows = 0; indexInScatteredRows < rowsPerProcess; ++indexInScatteredRows)
            {
                int startNode = rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns];
                for (int endNode = 1; endNode <= *verticesCount; ++endNode)
                {
                    if (startNode != endNode
                        && rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + endNode] >
                           rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + k] +
                           broadcastMatrix[k * matrixSizeColumns + endNode])
                    {
                        rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + endNode] =
                                rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + k] +
                                broadcastMatrix[k * matrixSizeColumns + endNode];
                    }
                }
            }

            MPI_Gather(rowsAssignedToProcess, matrixSizeColumns * rowsPerProcess, MPI_INT, broadcastMatrix,
                       rowsPerProcess * matrixSizeColumns,
                       MPI_INT, 0,
                       MPI_COMM_WORLD);
        }

        if (mpiRank == 0)
        {
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start
            );
//            std::cout << "Floyd_MPI finished, " << duration.count() << " us elapsed\n";
            printf("Floyd_MPI;%s;%ld\n", graphFileName.c_str(), duration.count());


            if (doCheck)
            {
                DistanceMatrix result(*verticesCount, broadcastMatrix);
                result.print();
                DistanceMatrix check(matrix);
                Floyd().calculate(check);
                if (result == check)
                {
                    std::cout << "Matrices are equal.\n";
                } else
                {
                    std::cout << "Matrices are NOT equal!\n";
                }
            }
        }

        delete verticesCount;
        delete[] rowsAssignedToProcess;
        delete[] broadcastMatrix;

//        MPI_Finalize();
    }
}
