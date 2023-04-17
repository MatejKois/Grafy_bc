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

int main()
{
    Grafy::DistanceMatrix test1(8);
//    Grafy::Parser::parse("/home/dev/Projects/Grafy/Examples/test.hrn", test1, true);
    Grafy::LabelSet_MPI().calculate(test1, "/home/dev/Projects/Grafy/Examples/test.hrn");
//    Grafy::LabelCorrectPthread().calculate(test1);
//    test1.print();

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
