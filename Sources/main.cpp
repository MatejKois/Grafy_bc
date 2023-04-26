#include <chrono>
#include <fstream>
#include <iostream>

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

static void measure(bool pthread)
{
    std::ofstream floyd;
    if (pthread)
    {
        floyd.open("../Examples/results_FloydPthread.csv");
    } else
    {
        floyd.open("../Examples/results_Floyd.csv");
    }
    for (int verticesCount = 100; verticesCount <= 1000; verticesCount += 100)
    {
        for (int divider = 10; divider > 1; --divider)
        {
            int edgesToAddCount = verticesCount / divider * verticesCount;
            char filename[200];
            sprintf(filename, "../Examples/%dV_%dH.hrn", verticesCount, edgesToAddCount);

            Grafy::DistanceMatrix test(verticesCount);
            Grafy::Parser::parse(filename, test);

            auto start = std::chrono::high_resolution_clock::now();

            if (pthread)
            {
                Grafy::FloydPthread().calculate(test);
            } else
            {
                Grafy::Floyd().calculate(test);
            }

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start
            );

            char msg[200];
            sprintf(msg, "%dV_%dH;%ld\n", verticesCount, edgesToAddCount, duration.count());
            floyd << msg;
        }
    }
    floyd.close();


    std::ofstream labelcorrect;
    if (pthread)
    {
        labelcorrect.open("../Examples/results_LabelCorrectPthread.csv");
    } else
    {
        labelcorrect.open("../Examples/results_LabelCorrect.csv");
    }
    for (int verticesCount = 100; verticesCount <= 1000; verticesCount += 100)
    {
        for (int divider = 10; divider > 1; --divider)
        {
            int edgesToAddCount = verticesCount / divider * verticesCount;
            char filename[200];
            sprintf(filename, "../Examples/%dV_%dH.hrn", verticesCount, edgesToAddCount);

            int numEdges, numVertices;
            Grafy::Parser::countEdgesAndVertices(filename, numEdges, numVertices);
            Grafy::EdgesList list(numEdges, numVertices);
            Grafy::Parser::parse(filename, list);
            Grafy::DistanceMatrix test(verticesCount);

            auto start = std::chrono::high_resolution_clock::now();

            if (pthread)
            {
                Grafy::LabelCorrectPthread().calculate(list, test);
            } else
            {
                Grafy::LabelCorrect().calculate(list, test);
            }

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start
            );

            char msg[200];
            sprintf(msg, "%dV_%dH;%ld\n", verticesCount, edgesToAddCount, duration.count());
            labelcorrect << msg;
        }
    }
    labelcorrect.close();


    std::ofstream labelset;
    if (pthread)
    {
        labelset.open("../Examples/results_LabelSetPthread.csv");
    } else
    {
        labelset.open("../Examples/results_LabelSet.csv");
    }
    for (int verticesCount = 100; verticesCount <= 1000; verticesCount += 100)
    {
        for (int divider = 10; divider > 1; --divider)
        {
            int edgesToAddCount = verticesCount / divider * verticesCount;
            char filename[200];
            sprintf(filename, "../Examples/%dV_%dH.hrn", verticesCount, edgesToAddCount);

            int numEdges, numVertices;
            Grafy::Parser::countEdgesAndVertices(filename, numEdges, numVertices);
            Grafy::EdgesList list(numEdges, numVertices);
            Grafy::Parser::parse(filename, list);
            Grafy::DistanceMatrix test(verticesCount);

            auto start = std::chrono::high_resolution_clock::now();

            if (pthread)
            {
                Grafy::LabelSetPthread().calculate(list, test);
            } else
            {
                Grafy::LabelSet().calculate(list, test);
            }

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                    std::chrono::high_resolution_clock::now() - start
            );

            char msg[200];
            sprintf(msg, "%dV_%dH;%ld\n", verticesCount, edgesToAddCount, duration.count());
            labelset << msg;
        }
    }
    labelset.close();
}

int main()
{
//    std::cout << "Finished reading from file\n";
//    // ----------------------------------------------------------------------
//    auto start = std::chrono::high_resolution_clock::now();
//    // ----------------------------------------------------------------------

    measure(true);

//    // ----------------------------------------------------------------------
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
//            std::chrono::high_resolution_clock::now() - start
//    );
//    std::cout << "Finished, " << duration.count() << " us elapsed\n";
//    // ----------------------------------------------------------------------


    return 0;
}
