#include <fstream>
#include <iostream>

#include "../../Headers/Algorithms/Algorithm.h"
#include "../../Headers/Parser/Parser.h"


namespace Grafy
{
    bool Parser::countEdgesAndVertices(const std::string& filename, int& edgesCount, int& verticesCount)
    {
        edgesCount = 0;
        verticesCount = 0;

        std::string word;
        std::ifstream file(filename);
        if (!file.is_open())
        {
            perror("Error opening file");
            return false;
        }

        while (file >> word)
        {
            verticesCount = std::stoi(word) > verticesCount ? std::stoi(word) : verticesCount;
            file >> word;
            verticesCount = std::stoi(word) > verticesCount ? std::stoi(word) : verticesCount;
            file >> word;
            ++edgesCount;
        }

        file.close();
        return true;
    }

    bool Parser::parse(const std::string& filename, DistanceMatrix& matrix)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            perror("Error opening file");
            return false;
        }

        std::string a, b, cost;

        while (file >> a)
        {
            file >> b;
            file >> cost;
            matrix.dist(std::stoi(a), std::stoi(b)) = std::stoi(cost);
        }

        file.close();
        return true;
    }

    bool Parser::parse(const std::string& filename, EdgesList& list)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            perror("Error opening file");
            return false;
        }

        std::string a, b, weight;
        int i = 0;

        while (file >> a)
        {
            file >> b;
            file >> weight;
            list.list()[3 * i] = std::stoi(a);
            list.list()[3 * i + 1] = std::stoi(b);
            list.list()[3 * i + 2] = std::stoi(weight);
            ++i;
        }

        file.close();
        list.updateStartPositions();
        return true;
    }

    bool Parser::writeToFile(const std::string& filename, DistanceMatrix& matrix)
    {
        std::ofstream out(filename);
        if (!out.is_open())
        {
            perror("Error opening file");
            return false;
        }

        for (int y = 1; y <= matrix.size(); ++y)
        {
            for (int x = 1; x <= matrix.size(); ++x)
            {
                if (matrix.dist(y, x) > 0 && matrix.dist(y, x) < MATRIX_DIST_INF)
                {
                    out << y << " " << x << " " << matrix.dist(y, x) << "\n";
                }
            }
        }

        out.close();
        return true;
    }
}
