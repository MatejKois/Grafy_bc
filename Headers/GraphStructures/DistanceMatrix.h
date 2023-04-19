#ifndef GRAFY_DISTANCEMATRIX_H
#define GRAFY_DISTANCEMATRIX_H


namespace Grafy
{
    class DistanceMatrix
    {
    public:
        /// @brief constructor
        DistanceMatrix(int size);

        /// @brief copy constructor
        DistanceMatrix(DistanceMatrix& other);

        /// @returns distance between two entered vertices in graph (matrix)
        int& dist(int y, int x);

        /// @returns pointer to the matrix memory
        int* data();

        /// @returns number of verices in graph (matrix), NOT the array size !
        int size() const
        { return this->size_ - 1; }

        /// @brief prints the distance matrix to the console
        void print();

        /// @brief destructor
        ~DistanceMatrix();

        /// @brief comparison operator for comparing two matrices
        bool operator==(DistanceMatrix& other);

    private:
        int* matrix_;
        int size_;
    };
}


#endif //GRAFY_DISTANCEMATRIX_H
