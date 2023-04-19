#ifndef GRAFY_PARSER_H
#define GRAFY_PARSER_H


#include <string>
#include "../GraphStructures/DistanceMatrix.h"
#include "../GraphStructures/EdgesList.h"

namespace Grafy
{
    class Parser
    {
    public:
        /// @returns counts number of vertices and edges in graph stored in file
        static void countEdgesAndVertices(const std::string& filename, int& edgesCount, int& verticesCount);

        /// @brief parses graph from file to distance matrix
        static bool parse(const std::string& filename, DistanceMatrix& matrix);

        /// @brief parses graph from file to distance matrix
        static bool parse(const std::string& filename, EdgesList& list);

        /// @brief writes matrix to file as list of edges
        static bool writeToFile(const std::string& filename, DistanceMatrix& matrix);
    };
}


#endif //GRAFY_PARSER_H
