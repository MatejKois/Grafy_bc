#ifndef GRAFY_GRAPHGENERATOR_H
#define GRAFY_GRAPHGENERATOR_H


#include "../Matrix/DistanceMatrix.h"

class GraphGenerator
{
public:
    void generate(DistanceMatrix& matrix, int distanceMin, int distanceMax);

private:
    /// @brief creates complete graph - a list of edges
    static void makeCompleteGraph(int verticesCount, int distanceMin, int distanceMax, int** allEdges);

    /// @brief sorts the edges using quicksort algorithm, so the kruskal will work
    void quickSortArray(int** array, int left, int right);

    /// @brief swaps two edges
    void swap(int** array, int left, int right);

    /// @brief creates a tree from the complete graph using kruskal's algorithm
    static void makeTree(DistanceMatrix& matrix, int** sortedEdges, int verticesCount);

    /// @brief adds random edges to the tree
    static void addMoreEdges(DistanceMatrix& matrix, int** allEdges, int verticesCount);
};


#endif //GRAFY_GRAPHGENERATOR_H
