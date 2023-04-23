#include <iostream>
#include <chrono>
#include "../Headers/GraphStructures//DistanceMatrix.h"
#include "../Headers/Algorithms/LabelCorrect.h"
#include "../Headers/Algorithms/LabelCorrectPthread.h"
#include "../Headers/Algorithms/LabelCorrect_MPI.h"
#include "../Headers/Algorithms/LabelSet_MPI.h"
#include "../Headers/GraphStructures/heap.h"
#include "../Headers/Algorithms/Floyd.h"
#include "../Headers/Algorithms/FloydPthread.h"
#include "../Headers/Algorithms/LabelSet.h"
#include "../Headers/Algorithms/LabelSetPthread.h"
#include "../Headers/Parser/Parser.h"
#include "../Headers/Generator/GraphGenerator.h"
#include "../Headers/Generator/GraphMerger.h"

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

int main()
{
    int verticesCount, edgesCount;
    Grafy::Parser::countEdgesAndVertices("../Examples/test.hrn", edgesCount, verticesCount);

    Grafy::EdgesList list(edgesCount, verticesCount);
    Grafy::Parser::parse("../Examples/test.hrn", list);

    Grafy::DistanceMatrix test1(verticesCount);
    Grafy::DistanceMatrix test2(verticesCount);

    Grafy::LabelCorrect().calculate(list, test1);
    test1.print();

    Grafy::LabelSetPthread().calculate(list, test2);
    test2.print();




//    Grafy::DistanceMatrix test1(15);
//    Grafy::GraphGenerator().generate(test1, 2, 10, 5);
//    Grafy::Parser::parse("/home/dev/Projects/Grafy/Examples/test.hrn", test1, true);
//    Grafy::DistanceMatrix test2(test1);
//
//    auto begin = std::chrono::steady_clock::now();
//    Grafy::FloydPthread().calculate(test1);
//    auto end = std::chrono::steady_clock::now();
//
//    std::cout << "FloydPthread = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
//              << "[microsec]\n";
//
//    begin = std::chrono::steady_clock::now();
//    Grafy::LabelCorrectPthread().calculate(test2);
//    end = std::chrono::steady_clock::now();
//
//    std::cout << "LabelCorrectPthread = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
//              << "[microsec]\n";
//
//    test1.print();
//    test2.print();
//    compareMatrices(test1, test2);

    return 0;
}
