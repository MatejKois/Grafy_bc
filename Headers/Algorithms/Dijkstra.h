#ifndef GRAFY_DIJKSTRA_H
#define GRAFY_DIJKSTRA_H


#include "Algorithm.h"
#include "../Matrix/DistanceMatrix.h"

class Dijkstra : public Algorithm
{
public:
    void calculate(DistanceMatrix& matrix) override;
};


#endif //GRAFY_DIJKSTRA_H
