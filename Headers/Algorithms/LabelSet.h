#ifndef GRAFY_LABELSET_H
#define GRAFY_LABELSET_H


#include "Algorithm.h"

class LabelSet : public Algorithm
{
public:
    void calculate(DistanceMatrix& matrix) override;
};


#endif //GRAFY_LABELSET_H
