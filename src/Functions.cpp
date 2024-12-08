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


