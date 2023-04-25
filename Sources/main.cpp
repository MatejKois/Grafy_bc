#include <iostream>
#include <chrono>

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

int main()
{
//    auto start = std::chrono::high_resolution_clock::now();
//    // ----------------------------------------------------------------------


    Grafy::LabelSet_MPI().calculate("../Examples/priklad.hrn", false);


//    // ----------------------------------------------------------------------
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
//            std::chrono::high_resolution_clock::now() - start
//    );
//    std::cout << "Finished, " << duration.count() << " us elapsed\n";


    return 0;
}
