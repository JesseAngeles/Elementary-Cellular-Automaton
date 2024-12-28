#include "Functions.h"

std::vector<bool> getBinary(int &number, const int &vector_size)
{
    // Es cero
    if (!number)
        return std::vector(vector_size, false);

    std::vector<bool> binary(vector_size, false);

    int i = 0;
    while (number >= 1)
    {
        binary[i++] = !(number % 2 == 0);
        number /= 2;
    }

    std::reverse(binary.begin(), binary.end());
    return binary;
}

std::map<int, std::vector<int>> matrixToMap(std::vector<std::vector<int>> &matrix)
{
    std::map<int, std::vector<int>> map;

    for (const std::vector<int> &vector : matrix)
    {
        map[vector[0]] = std::vector<int>(vector.begin() + 1, vector.end());
    }

    return map;
}

std::vector<std::vector<int>> mapToMatrix(std::map<int, std::vector<int>> &mapped)
{
    std::vector<std::vector<int>> matrix;

    for (const std::pair<const int, std::vector<int>> &pair : mapped)
    {
        std::vector<int> vector;

        vector.push_back(pair.first);
        vector.insert(vector.begin() + 1, pair.second.begin(), pair.second.end());

        matrix.push_back(vector);
    }

    return matrix;
}