#include "PrimeGenerator.hpp"

#include <iostream>

std::vector<int> generatePrimesUntil(const int &max)
{
    std::vector<int> primes;
    bool is_prime;

    primes.push_back(2);


    for (int i = 3; i <= max / 2; i+=2)
    {
        is_prime = true;
        for (const int &prime : primes)
            if (i % prime == 0)
            {
                is_prime = false;
                break;
            }

        if (is_prime)
            primes.push_back(i);
    }

    return primes;
}