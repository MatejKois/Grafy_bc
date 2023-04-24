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
#include "../Headers/Algorithms/Floyd_MPI.h"

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
    Grafy::Floyd_MPI().calculate("../Examples/test.hrn");

    return 0;
}
