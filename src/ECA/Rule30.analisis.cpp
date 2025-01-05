#include "ECA/Rule30.hpp"

void Rule30::primeNumberAnalisis(std::map<int, std::vector<int>> &current,
                                 const std::vector<bool> &column,
                                 const std::vector<int> &primes)
{
    // iterate prime numbers
    for (const int &prime : primes)
    {
        std::vector<int> frecuencies;
        int count = 0;
        int position_start = 0;

        // Writted prime
        if (current.find(prime) != current.end())
        {
            frecuencies = current[prime];
            position_start = frecuencies[frecuencies.size() - 1];
            frecuencies.pop_back();
        }

        // Iterate de main column
        for (int i = position_start; i < column.size(); i++)
        {
            count += column[i];
            if ((i + 1) % prime == 0)
            {
                frecuencies.push_back(count);
                count = 0;
            }
        }

        frecuencies.push_back(frecuencies.size() * prime);
        current[prime] = frecuencies;
    }
}
