#ifndef GRAFY_PARSER_H
#define GRAFY_PARSER_H


#include <string>
#include "../Matrix/DistanceMatrix.h"

namespace Grafy
{
    class Parser
    {
    public:
        /// @returns number of vertices in graph stored in file
        static int getVerticesCount(const std::string& filename);

        /// @brief parses graph from file to distance matrix
        static bool parse(const std::string& filename, DistanceMatrix& matrix, bool weighted);

        /// @brief writes matrix to file as list of edges
        static bool writeToFile(const std::string& filename, DistanceMatrix& matrix);
    };
}


#endif //GRAFY_PARSER_H
