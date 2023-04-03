#ifndef GRAFY_DISTANCEMATRIX_H
#define GRAFY_DISTANCEMATRIX_H


class DistanceMatrix {
public:
    /// @brief constructor
    DistanceMatrix(int size);

    /// @brief constructor for partial matrix
    DistanceMatrix(int sizeY, int sizeX);

    /// @brief copy constructor
    DistanceMatrix(DistanceMatrix& other);

    /// @returns distance between two entered vertices in graph (matrix)
    int& dist(int a, int b);

    /// @returns pointer to the matrix memory
    int** data();

    /// @returns number of verices in graph (matrix)
    int size() const { return this->sizeX_ - 1; }

    /// @returns number of verices in graph (matrix)
    int sizeY() const { return this->sizeY_ - 1; }

    /// @brief prints the distance matrix to the console
    void print();

    ~DistanceMatrix();

private:
    int** matrix_;
    int sizeX_;
    int sizeY_;
};


#endif //GRAFY_DISTANCEMATRIX_H
