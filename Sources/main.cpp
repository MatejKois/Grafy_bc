#include <iostream>
#include <chrono>
#include "../Headers/Matrix/DistanceMatrix.h"
#include "../Headers/Algorithms/Dijkstra.h"
#include "../Headers/Algorithms/DijkstraBidirectional.h"
#include "../Headers/Algorithms/DijkstraPthread.h"
#include "../Headers/Algorithms/DijkstraMPI.h"
#include "../Headers/Algorithms/heap.h"
#include "../Headers/Algorithms/Floyd.h"
#include "../Headers/Algorithms/FloydPthread.h"
#include "../Headers/Parser/Parser.h"
#include "../Headers/Generator/GraphGenerator.h"
#include "../Headers/Generator/GraphMerger.h"

#include <mpi.h>

void mpiExample()
{
// Initialize MPI
    MPI_Init(nullptr, nullptr);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::cout << "Rank: " << rank << ", size: " << size << "\n";

    const int rows = 5;
    const int cols = 5;
    int matrix[rows][cols];

    if (rank == 0)
    {
        // Initialize matrix
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                matrix[i][j] = -1;
            }
        }
    }
    if (rank == 0)
    {
        // Print matrix
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    const int rows_per_process = rows / size;

    int* row_data = new int[cols * rows_per_process];
    MPI_Scatter(matrix, cols * rows_per_process, MPI_INT, row_data, cols * rows_per_process, MPI_INT, 0,
                MPI_COMM_WORLD);

    for (int i = 0; i < rows_per_process; i++)
    {
        // Do something with row_data[i]
        for (int j = 0; j < cols; j++)
        {
            row_data[i * cols + j] = 2;
        }
    }

    int* final_matrix = nullptr;
    if (rank == 0)
    {
        final_matrix = new int[rows * cols];
    }

    MPI_Gather(row_data, cols * rows_per_process, MPI_INT, final_matrix, cols * rows_per_process, MPI_INT, 0,
               MPI_COMM_WORLD);

    if (rank == 0)
    {
        // Print final matrix
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << final_matrix[i * cols + j] << " ";
            }
            std::cout << std::endl;
        }
    }

    delete[] row_data;
    delete[] final_matrix;

    // Finalize MPI
    MPI_Finalize();
}

int main()
{
    DistanceMatrix test(5);
    GraphGenerator().generate(test, 2, 10);
    DistanceMatrix test2(test);

    DijkstraMPI().calculate(test);
    Dijkstra().calculate(test2);
    test.print();
    test2.print();

    return 0;
}
