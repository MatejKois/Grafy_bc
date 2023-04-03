#ifndef GRAFY_DIJKSTRAMPI_H
#define GRAFY_DIJKSTRAMPI_H


#include "Algorithm.h"
#include "../Matrix/DistanceMatrix.h"

class DijkstraMPI : public Algorithm
{
public:
    void calculate(DistanceMatrix& matrix) override;
};


#endif //GRAFY_DIJKSTRAMPI_H
