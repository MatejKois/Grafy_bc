#include <iostream>
#include <chrono>
#include "../Headers/Matrix/DistanceMatrix.h"
#include "../Headers/Algorithms/LabelCorrect.h"
#include "../Headers/Algorithms/DijkstraBidirectional.h"
#include "../Headers/Algorithms/LabelCorrectPthread.h"
#include "../Headers/Algorithms/LabelCorrect_MPI.h"
#include "../Headers/Algorithms/LabelSet_MPI.h"
#include "../Headers/Algorithms/heap.h"
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
    Grafy::DistanceMatrix test1(200);
    Grafy::GraphGenerator().generate(test1, 2, 10);
//    Grafy::Parser::parse("/home/dev/Projects/Grafy/Examples/test.hrn", test1, true);
    Grafy::DistanceMatrix test2(test1);
    Grafy::LabelCorrect().calculate(test1);
    Grafy::FloydPthread().calculate(test2);

//    test1.print();
//    test2.print();

    compareMatrices(test1, test2);

//    GraphGenerator().generate(test1, 2, 10);
//    DistanceMatrix test2(test1);
//
//    auto begin = std::chrono::steady_clock::now();
//    LabelCorrect().calculate(test1);
//    auto end = std::chrono::steady_clock::now();
//
//    std::cout << "LabelCorrect = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
//              << "[microsec]\n";
//
//    begin = std::chrono::steady_clock::now();
//    end = std::chrono::steady_clock::now();
//
//    std::cout << "LabelCorrect mpi = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
//              << "[microsec]\n";
//
//    test1.print();
//    test2.print();

    return 0;
}
