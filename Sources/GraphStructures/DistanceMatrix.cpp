#include "../../Headers/GraphStructures/DistanceMatrix.h"
#include <cstdio>
#include <string>
#include <cstring>

#define MATRIX_DIST_INF 999999

namespace Grafy
{
    DistanceMatrix::DistanceMatrix(int size)
            : size_(size + 1)
    {
        matrix_ = new int[size_ * size_];
        for (int i = 0; i < size_; ++i)
        {
            for (int j = 1; j < size_; ++j)
            {
                matrix_[i * size_ + j] = MATRIX_DIST_INF;
            }
            matrix_[i * size_ + i] = 0; // adds 0 for distance between the same node
            matrix_[i * size_] = i; // adds the row-vertex number at the row start for indexing purposes
        }
    }

    DistanceMatrix::DistanceMatrix(DistanceMatrix& other)
            : size_(other.size_)
    {
        matrix_ = new int[other.size_ * other.size_];
        std::memcpy(matrix_, other.matrix_, other.size_ * other.size_ * sizeof(int));
    }

    int& DistanceMatrix::dist(int y, int x)
    {
        return matrix_[y * size_ + x];
    }

    int* DistanceMatrix::data()
    {
        return matrix_;
    }

    void DistanceMatrix::print()
    {
        if (size_ > 16)
        {
            printf("GraphStructures too large to print!\n");
            return;
        }
        for (int i = 0; i < size_; ++i)
        {
            printf("-----+");
        }
        printf("\n  X  |");
        for (int i = 1; i < size_; ++i)
        {
            printf("%5d|", i);
        }
        printf("\n");
        for (int i = 0; i < size_; ++i)
        {
            printf("-----+");
        }
        printf("\n");
        for (int y = 1; y < size_; ++y)
        {
            printf("%5d|", y);
            for (int x = 1; x < size_; ++x)
            {
                if (matrix_[y * size_ + x] <= 0 || matrix_[y * size_ + x] >= MATRIX_DIST_INF)
                {
                    printf("  -  |");
                } else
                {
                    printf("%5d|", matrix_[y * size_ + x]);
                }
            }
            printf("\n");
        }
        for (int i = 0; i < size_; ++i)
        {
            printf("-----+");
        }
        printf("\n");
    }

    DistanceMatrix::~DistanceMatrix()
    {
        delete[] matrix_;
        matrix_ = nullptr;
    }

    bool DistanceMatrix::operator==(DistanceMatrix& other)
    {
        if (size_ != other.size_)
        {
            return false;
        }
        for (int y = 0; y < size_; ++y)
        {
            for (int x = 0; x < size_; ++x)
            {
                if (dist(y, x) != other.dist(y, x))
                {
                    return false;
                }
            }
        }
        return true;
    }
}

#undef MATRIX_DIST_INF
