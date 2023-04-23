#include <cstring>
#include <iostream>
#include "../../Headers/GraphStructures/EdgesList.h"

namespace Grafy
{
    EdgesList::EdgesList(int numEdges, int numVertices)
            : numEdges_(numEdges), numVertices_(numVertices)
    {
        list_ = new int[3 * numEdges];
        startPositions_ = new int[numVertices + 2];
    }

    EdgesList::EdgesList(EdgesList& other)
            : numEdges_(other.numEdges_), numVertices_(other.numVertices_)
    {
        list_ = new int[3 * other.numEdges_];
        startPositions_ = new int[other.numVertices_ + 2];
        std::memcpy(list_, other.list_, 3 * other.numEdges_ * sizeof(int));
        std::memcpy(startPositions_, other.startPositions_, (other.numVertices_ + 1) * sizeof(int));
    }

    EdgesList::~EdgesList()
    {
        delete[] list_;
        delete[] startPositions_;
    }

    void EdgesList::updateStartPositions()
    {
        startPositions_[0] = 0;
        int current = 0;
        for (int i = 0; i < numEdges_; ++i)
        {
            if (list_[3 * i] > current)
            {
                ++current;
                startPositions_[current] = i;
            }
        }
        startPositions_[numVertices_ + 1] = numEdges_;
    }

    void EdgesList::print()
    {
        std::cout << "-------------------------\n";
        for (int i = 1; i <= numVertices_; ++i)
        {
            for (int pos = startPositions_[i]; pos < startPositions_[i + 1]; ++pos)
            {
                std::cout << " " <<
                          list_[3 * pos] << "-" <<
                          list_[3 * pos + 1] << " " <<
                          list_[3 * pos + 2] << "\n";
            }
        }
        std::cout << "-------------------------\n";
    }
}
