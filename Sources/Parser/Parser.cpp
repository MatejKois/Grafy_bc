#include "../../Headers/Parser/Parser.h"

#include <fstream>
#include <iostream>

int Parser::getVerticesCount(const std::string& filename)
{
    int max = 0;
    std::string word;
    std::ifstream file(filename);

    while (file >> word)
    {
        max = std::stoi(word) > max ? std::stoi(word) : max;
        file >> word;
        max = std::stoi(word) > max ? std::stoi(word) : max;
        file >> word;
    }

    file.close();
    return max;
}

void Parser::parse(const std::string& filename, DistanceMatrix& matrix, bool weighted)
{
    std::string a, b, cost;
    std::ifstream file(filename);

    while (file >> a)
    {
        file >> b;
        if (weighted)
        {
            file >> cost;
        }
        matrix.dist(std::stoi(a), std::stoi(b)) = weighted ? std::stoi(cost) : 1;
    }

    file.close();
}

bool Parser::writeToFile(const std::string& filename, DistanceMatrix& matrix)
{
    std::ofstream out(filename);

    if (!out.is_open())
    {
        return false;
    }

    for (int y = 0; y <= matrix.size(); ++y)
    {
        for (int x = 0; x <= matrix.size(); ++x)
        {
            if (matrix.dist(y, x) > 0)
            {
                out << y << " " << x << " " << matrix.dist(y, x) << "\n";
            }
        }
    }

    out.close();
    return true;
}
