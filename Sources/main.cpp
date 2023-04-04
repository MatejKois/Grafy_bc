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

int main()
{
    DistanceMatrix test1(300);
    GraphGenerator().generate(test1, 2, 10);

    DistanceMatrix test2(test1);

    auto begin = std::chrono::steady_clock::now();
    Floyd().calculate(test1);
    auto end = std::chrono::steady_clock::now();

    std::cout << "Floyd = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << "[microsec]\n";

    begin = std::chrono::steady_clock::now();
    FloydPthread().calculate(test2);
    end = std::chrono::steady_clock::now();

    std::cout << "Floyd(pthread) = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count()
              << "[microsec]\n";

    test1.print();
    test2.print();

    return 0;
}
