#ifndef GRAFY_GRAPHMERGER_H
#define GRAFY_GRAPHMERGER_H


#include "../Matrix/DistanceMatrix.h"

namespace Grafy
{
    class GraphMerger
    {
    public:
        /// @brief merges two martices (graphs) into one
        /// @param bridgesToAddcount number of bridges to add to the merged graph
        /// @param distanceMin minimum distance when generating bridge
        /// @param distanceMax maximum distance when generating bridge
        static void
        merge(DistanceMatrix& matrix1, DistanceMatrix& matrix2, DistanceMatrix& merged, int bridgesToAddcount,
              int distanceMin, int distanceMax);
    };
}


#endif //GRAFY_GRAPHMERGER_H
