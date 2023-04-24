#include <mpi.h>
#include <cstring>

#include "../../Headers/Algorithms/Floyd_MPI.h"
#include "../../Headers/Parser/Parser.h"
#include "../../Headers/Algorithms/Floyd.h"

namespace Grafy
{
    void Floyd_MPI::calculate(const std::string& graphFileName)
    {
        MPI_Init(nullptr, nullptr);

        int mpiRank, mpiSize;
        MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
        MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

        int* edgesCount = new int{0};
        int* verticesCount = new int{0};

        if (mpiRank == 0)
        {
            Parser::countEdgesAndVertices(graphFileName, *edgesCount, *verticesCount);
        }

        MPI_Bcast(edgesCount, 1, MPI_INT, 0, MPI_COMM_WORLD);
        MPI_Bcast(verticesCount, 1, MPI_INT, 0, MPI_COMM_WORLD);

        DistanceMatrix matrix(*verticesCount);

        if (mpiRank == 0)
        {
            Parser::parse(graphFileName, matrix);
        }

        const int matrixSizeColumns = *verticesCount + 1;
        const int rowsPerProcess = matrixSizeColumns % mpiSize == 0 ?
                                   matrixSizeColumns / mpiSize :
                                   matrixSizeColumns / mpiSize + matrixSizeColumns % mpiSize;

        int* broadcastMatrix = matrix.data();

        MPI_Bcast(broadcastMatrix, matrixSizeColumns * matrixSizeColumns, MPI_INT, 0, MPI_COMM_WORLD);

        int* rowsAssignedToProcess = new int[rowsPerProcess * matrixSizeColumns];
        std::memcpy(rowsAssignedToProcess, broadcastMatrix + mpiRank * matrixSizeColumns * rowsPerProcess,
                    rowsPerProcess * matrixSizeColumns * sizeof(int));


        for (int k = 1; k <= *verticesCount; ++k)
        {
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
        }


        int* finalMatrix = new int[mpiSize * rowsPerProcess * matrixSizeColumns]();
        MPI_Gather(rowsAssignedToProcess, matrixSizeColumns * rowsPerProcess, MPI_INT, finalMatrix,
                   rowsPerProcess * matrixSizeColumns,
                   MPI_INT, 0,
                   MPI_COMM_WORLD);

        if (mpiRank == 0)
        {
            DistanceMatrix result(*verticesCount, finalMatrix);
            result.print();
            DistanceMatrix check(matrix);
            Floyd().calculate(check);
            check.print();

            if (result == check)
            {
                std::cout << "Matrices are equal.\n";
            } else
            {
                std::cout << "Matrices are NOT equal!\n";
            }

//            for (int i = 0; i < matrixSizeColumns; ++i)
//            {
//                printf("-----+");
//            }
//            printf("\n  X  |");
//            for (int i = 1; i < matrixSizeColumns; ++i)
//            {
//                printf("%5d|", i);
//            }
//            printf("\n");
//            for (int i = 0; i < matrixSizeColumns; ++i)
//            {
//                printf("-----+");
//            }
//            printf("\n");
//            for (int y = 0; y < matrixSizeColumns; ++y)
//            {
//                for (int x = 0; x < matrixSizeColumns; ++x)
//                {
//                    printf("%5d|", finalMatrix[y * matrixSizeColumns + x]);
//                }
//                printf("\n");
//            }
//            for (int i = 0; i < matrixSizeColumns; ++i)
//            {
//                printf("-----+");
//            }
//            printf("\n");
//// -------------------------------------------------------------------
//            for (int i = 0; i < matrixSizeColumns; ++i)
//            {
//                printf("-----+");
//            }
//            printf("\n  X  |");
//            for (int i = 1; i < matrixSizeColumns; ++i)
//            {
//                printf("%5d|", i);
//            }
//            printf("\n");
//            for (int i = 0; i < matrixSizeColumns; ++i)
//            {
//                printf("-----+");
//            }
//            printf("\n");
//            for (int y = 0; y < matrixSizeColumns; ++y)
//            {
//                for (int x = 0; x < matrixSizeColumns; ++x)
//                {
//                    printf("%5d|", check.dist(y, x));
//                }
//                printf("\n");
//            }
//            for (int i = 0; i < matrixSizeColumns; ++i)
//            {
//                printf("-----+");
//            }
//            printf("\n");
//
//            if (result == check)
//            {
//                std::cout << "Matrices are equal.\n";
//            } else
//            {
//                std::cout << "Matrices are NOT equal!\n";
//            }
        }

        delete verticesCount;
        delete[] rowsAssignedToProcess;
        delete[] finalMatrix;

        MPI_Finalize();
    }
}
