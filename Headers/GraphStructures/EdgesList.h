#ifndef GRAFY_EDGESLIST_H
#define GRAFY_EDGESLIST_H


#include "DistanceMatrix.h"

namespace Grafy
{
    class EdgesList
    {
    public:
        /// @brief constructor
        EdgesList(int numEdges, int numVertices);

        /// @brief copy constructor
        EdgesList(EdgesList& other);

        /// @brief destructor
        ~EdgesList();

        /// @brief updates start positions for all vertices
        void updateStartPositions();

        /// @brief returns number of edges in the graph
        int numEdges() const
        { return numEdges_; }

        /// @brief returns number of vertices in the graph
        int numVertices() const
        { return numVertices_; }

        /// @brief returns pointer to the edges list
        int* list()
        { return list_; }

        /// @brief returns pointer to the edges positions
        int* startPositions()
        { return startPositions_; }

        /// @brief prints the edges list
        void print();

        /// @brief prints the edges list
        int& operator[](int i)
        { return list_[i]; }

    private:
        /// @brief list containing all edges in graph
        int* list_;

        /// @brief tells where list of edges for a specific vertex starts
        int* startPositions_;

        /// @brief number of edges in graph
        int numEdges_;

        /// @brief number of vertices in graph
        int numVertices_;
    };
}


#endif //GRAFY_EDGESLIST_H
