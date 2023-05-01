#include <chrono>
#include <fstream>
#include <iostream>
#include <mpi.h>

#include "../Headers/Algorithms/Floyd.h"
#include "../Headers/Algorithms/Floyd_MPI.h"
#include "../Headers/Algorithms/FloydPthread.h"
#include "../Headers/Algorithms/LabelCorrect.h"
#include "../Headers/Algorithms/LabelCorrect_MPI.h"
#include "../Headers/Algorithms/LabelCorrectPthread.h"
#include "../Headers/Algorithms/LabelSet.h"
#include "../Headers/Algorithms/LabelSet_MPI.h"
#include "../Headers/Algorithms/LabelSetPthread.h"
#include "../Headers/Generator/GraphGenerator.h"
#include "../Headers/Generator/GraphMerger.h"
#include "../Headers/GraphStructures/DistanceMatrix.h"
#include "../Headers/GraphStructures/EdgesList.h"
#include "../Headers/Parser/Parser.h"

static void compareMatrices(Grafy::DistanceMatrix& a, Grafy::DistanceMatrix& b)
{
    if (a == b)
    {
        std::cout << "Matrices are equal.\n";
    } else
    {
        std::cout << "Matrices are NOT equal!\n";
    }
}

/// @brief generates test graphs and stores them in a file
static void generateGraphs()
{
    for (int verticesCount = 100; verticesCount <= 1000; verticesCount += 100)
    {
        for (int divider = 10; divider > 1; --divider)
        {
            int edgesToAddCount = verticesCount / divider * verticesCount;

            Grafy::DistanceMatrix generated(verticesCount);
            Grafy::GraphGenerator().generate(generated, 5, verticesCount / 3, edgesToAddCount);
            char filename[200];
            sprintf(filename, "../Examples/%dV_%dH.hrn", verticesCount, edgesToAddCount);
            Grafy::Parser::writeToFile(filename, generated);
        }
    }
}

/// @brief test function that measures run times of the algorithms and saves results to a .csv file
static void measure(bool pthread)
{
    std::ofstream floyd;
    std::ofstream labelcorrect;
    std::ofstream labelset;
    if (pthread)
    {
        floyd.open("../Examples/results_FloydPthread.csv");
        labelcorrect.open("../Examples/results_LabelCorrectPthread.csv");
        labelset.open("../Examples/results_LabelSetPthread.csv");
    } else
    {
        floyd.open("../Examples/results_Floyd.csv");
        labelcorrect.open("../Examples/results_LabelCorrect.csv");
        labelset.open("../Examples/results_LabelSet.csv");
    }
    for (int verticesCount = 100; verticesCount <= 1000; verticesCount += 100)
    {
        for (int divider = 10; divider > 1; --divider)
        {
            int edgesToAddCount = verticesCount / divider * verticesCount;
            char filename[200];
            sprintf(filename, "../Examples/%dV_%dH.hrn", verticesCount, edgesToAddCount);

            Grafy::DistanceMatrix testFloyd(verticesCount);
            Grafy::DistanceMatrix testLabelCorrect(verticesCount);
            Grafy::DistanceMatrix testLabelSet(verticesCount);
            Grafy::Parser::parse(filename, testFloyd);

            int numEdges, numVertices;
            Grafy::Parser::countEdgesAndVertices(filename, numEdges, numVertices);
            Grafy::EdgesList list(numEdges, numVertices);
            Grafy::Parser::parse(filename, list);

            // Floyd ----------------------------------------------------------------------
            auto start = std::chrono::high_resolution_clock::now();
            if (pthread)
            {
                Grafy::FloydPthread().calculate(testFloyd);
            } else
            {
                Grafy::Floyd().calculate(testFloyd);
            }
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start
            );
            char msg[200];
            sprintf(msg, "%dV_%dH;%ld\n", verticesCount, edgesToAddCount, duration.count());
            floyd << msg;
            printf(">Finished floyd for %dV_%dH (%ld us)\n", verticesCount, edgesToAddCount, duration.count());
            // ----------------------------------------------------------------------------

            // LabelCorrect ---------------------------------------------------------------
            start = std::chrono::high_resolution_clock::now();
            if (pthread)
            {
                Grafy::LabelCorrectPthread().calculate(list, testLabelCorrect);
            } else
            {
                Grafy::LabelCorrect().calculate(list, testLabelCorrect);
            }
            duration = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start
            );
            sprintf(msg, "%dV_%dH;%ld\n", verticesCount, edgesToAddCount, duration.count());
            labelcorrect << msg;
            printf(">Finished label-correct for %dV_%dH (%ld us)\n", verticesCount, edgesToAddCount, duration.count());
            // ----------------------------------------------------------------------------

            // LabelSet -------------------------------------------------------------------
            start = std::chrono::high_resolution_clock::now();
            if (pthread)
            {
                Grafy::LabelSetPthread().calculate(list, testLabelSet);
            } else
            {
                Grafy::LabelSet().calculate(list, testLabelSet);
            }
            duration = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start
            );
            sprintf(msg, "%dV_%dH;%ld\n", verticesCount, edgesToAddCount, duration.count());
            labelset << msg;
            printf(">Finished label-set for %dV_%dH (%ld us)\n", verticesCount, edgesToAddCount, duration.count());
            // ----------------------------------------------------------------------------
        }
    }

    floyd.close();
    labelcorrect.close();
    labelset.close();
}

/// @brief test function that measures run time of Open MPI algorithms and prints it in the console
static void measure_MPI()
{
    MPI_Init(nullptr, nullptr);

    for (int verticesCount = 100; verticesCount <= 1000; verticesCount += 100)
    {
        for (int divider = 10; divider > 1; --divider)
        {
            int edgesToAddCount = verticesCount / divider * verticesCount;
            char filename[200];
            sprintf(filename, "../Examples/%dV_%dH.hrn", verticesCount, edgesToAddCount);

//            Grafy::Floyd_MPI().calculate(filename, false);
//            Grafy::LabelCorrect_MPI().calculate(filename, false);
            Grafy::LabelSet_MPI().calculate(filename, false);
        }
    }

    MPI_Finalize();
}

int main()
{
    // Example for running some algorithm: -------
    int edgesCount, verticesCount;
    Grafy::Parser::countEdgesAndVertices("../Examples/test.hrn", edgesCount,
                                         verticesCount); // count edges and vertices in the file
    Grafy::EdgesList list(edgesCount, verticesCount);
    Grafy::Parser::parse("../Examples/test.hrn", list); // reading graph from file to EdgesList
    Grafy::DistanceMatrix test(verticesCount); // this will be the result matrix

    Grafy::LabelSet().calculate(list, test); // create instance of LabelSet and call calculate
    test.print(); // print out the result
    // -------------------------------------------

    // Floyd -------------------------------------
    Grafy::DistanceMatrix test2(verticesCount);
    Grafy::Parser::parse("../Examples/test.hrn", test2); // for Floyd we parse the file directly into matrix
    Grafy::FloydPthread().calculate(test2);
    test2.print();
    // -------------------------------------------

    // Running Open MPI implementation -----------
    // Comment out all the code above first, then uncomment the MPI call !!!

//    Grafy::LabelSet_MPI().calculate("../Examples/test.hrn", true/*true means that we want to do check afterwards and print out the matrix*/);

    // -------------------------------------------

    return 0;
}
