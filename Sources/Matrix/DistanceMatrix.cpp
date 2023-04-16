#include "../../Headers/Matrix/DistanceMatrix.h"
#include <cstdio>
#include <string>
#include <cstring>

DistanceMatrix::DistanceMatrix(int size)
        : size_(size + 1)
{
    matrix_ = new int[size_ * size_];
    for (int i = 0; i < size_; ++i)
    {
        matrix_[i * size_] = i;
    }
}

DistanceMatrix::DistanceMatrix(DistanceMatrix& other)
        : size_(other.size_)
{
    matrix_ = new int[other.size_];
    std::memcpy(matrix_, other.matrix_, other.size_ * sizeof(int));
}

int& DistanceMatrix::dist(int a, int b)
{
    return matrix_[a * size_ + b];
}

int* DistanceMatrix::data()
{
    return matrix_;
}

void DistanceMatrix::print()
{
    if (size_ > 16)
    {
        printf("Matrix too large to print!\n");
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
            if (y == x)
            {
                printf("  x  |");
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
