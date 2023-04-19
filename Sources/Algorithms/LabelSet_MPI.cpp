#include <mpi.h>
#include <cstring>

#include "../../Headers/Algorithms/LabelSet_MPI.h"
#include "../../Headers/GraphStructures/heap.h"
#include "../../Headers/Parser/Parser.h"

namespace Grafy
{
    void LabelSet_MPI::calculate(DistanceMatrix& matrix, const std::string& graphFileName)
    {
        MPI_Init(nullptr, nullptr);

        int mpiRank, mpiSize;
        MPI_Comm_rank(MPI_COMM_WORLD, &mpiRank);
        MPI_Comm_size(MPI_COMM_WORLD, &mpiSize);

        if (mpiRank == 0)
        {
            Parser::parse(graphFileName, matrix);
            matrix.print();
        }

        const int matrixSizeColumns = matrix.size() + 1;
        const int rowsPerProcess =
                matrixSizeColumns % mpiSize == 0 ? matrixSizeColumns / mpiSize : matrixSizeColumns / mpiSize +
                                                                                 matrixSizeColumns % mpiSize;
        int* graphBcast = matrix.data();


        MPI_Bcast(graphBcast, matrixSizeColumns * matrixSizeColumns, MPI_INT, 0, MPI_COMM_WORLD);

        int* rowsAssignedToProcess = new int[rowsPerProcess * matrixSizeColumns]();
        std::memcpy(rowsAssignedToProcess, graphBcast + mpiRank * rowsPerProcess * matrixSizeColumns,
                    rowsPerProcess * matrixSizeColumns * sizeof(int));

        for (int indexInScatteredRows = 0; indexInScatteredRows < rowsPerProcess; indexInScatteredRows++)
        {
            // row start node is located at the start of the row
            int rowStartNode = rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns];
            int current = rowStartNode;
            Heap heap;

            heap.push(0, current);
            while (!heap.empty())
            {
                current = heap.pop();

                for (int endNode = 1; endNode < matrixSizeColumns; ++endNode)
                {
                    //               			   no edge from current to endNode
                    if (rowStartNode == endNode || graphBcast[current * matrixSizeColumns + endNode] <= 0)
                    {
                        continue;
                    }

                    if (rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + endNode] <= 0
                        ||
                        rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + endNode] >=
                        rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + current] +
                        graphBcast[current * matrixSizeColumns + endNode])
                    {
                        rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + endNode] =
                                rowsAssignedToProcess[indexInScatteredRows * matrixSizeColumns + current] +
                                graphBcast[current * matrixSizeColumns + endNode];
                        heap.push(matrix.dist(rowStartNode, endNode), endNode);
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
            std::memcpy(matrix.data(), finalMatrix, matrixSizeColumns * matrixSizeColumns * sizeof(int));
            matrix.print();
        }

        delete[] rowsAssignedToProcess;
        delete[] finalMatrix;

        MPI_Finalize();
    }
}
