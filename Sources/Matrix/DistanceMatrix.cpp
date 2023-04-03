#include "../../Headers/Matrix/DistanceMatrix.h"
#include <cstdio>
#include <string>

DistanceMatrix::DistanceMatrix(int size)
        : sizeX_(size + 1), sizeY_(size + 1)
{
    matrix_ = new int* [this->sizeY_];
    for (int i = 0; i < this->sizeY_; ++i)
    {
        matrix_[i] = new int[this->sizeX_]{0};
    }
}

DistanceMatrix::DistanceMatrix(int sizeY, int sizeX)
        : sizeX_(sizeX), sizeY_(sizeY)
{
    matrix_ = new int* [this->sizeY_];
    for (int i = 0; i < this->sizeY_; ++i)
    {
        matrix_[i] = new int[this->sizeX_]{0};
    }
}

DistanceMatrix::DistanceMatrix(DistanceMatrix& other)
        : sizeX_(other.sizeX_), sizeY_(other.sizeY_)
{
    matrix_ = new int* [other.sizeX_];
    for (int i = 0; i < other.sizeX_; ++i)
    {
        matrix_[i] = new int[other.sizeX_]{0};
        for (int j = 0; j < other.sizeX_; ++j)
        {
            this->matrix_[i][j] = other.matrix_[i][j];
        }
    }
}

int& DistanceMatrix::dist(int a, int b)
{
    return this->matrix_[a][b];
}

int** DistanceMatrix::data()
{
    return this->matrix_;
}

void DistanceMatrix::print()
{
    if (this->sizeX_ > 16)
    {
        printf("Matrix too large to print!\n");
        return;
    }
    for (int i = 0; i < this->sizeX_; ++i)
    {
        printf("-----+");
    }
    printf("\n  X  |");
    for (int i = 1; i < this->sizeX_; ++i)
    {
        printf("%5d|", i);
    }
    printf("\n");
    for (int i = 0; i < this->sizeX_; ++i)
    {
        printf("-----+");
    }
    printf("\n");
    for (int y = 1; y < this->sizeY_; ++y)
    {
        printf("%5d|", y);
        for (int x = 1; x < this->sizeX_; ++x)
        {
            if (y == x)
            {
                printf("  x  |");
            } else
            {
                printf("%5d|", this->matrix_[y][x]);
            }
        }
        printf("\n");
    }
    for (int i = 0; i < this->sizeX_; ++i)
    {
        printf("-----+");
    }
    printf("\n");
}

DistanceMatrix::~DistanceMatrix()
{
    for (int i = 0; i < this->sizeY_; ++i)
    {
        delete[] this->matrix_[i];
    }
    delete[] this->matrix_;
    this->matrix_ = nullptr;
}
