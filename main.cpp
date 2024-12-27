#include <iostream>

#include "ECA/ElementaryCellularAutomaton.hpp"
#include "PrimeGenerator.hpp"
#include "FileController.hpp"

using namespace std;

int displayMenu()
{
    int option;
    cout << "0) All generated generations\n";
    cout << "n) The N generation\n";

    cin >> option;

    return option;
}

int main()
{
    // Generar numeros primos
    std::vector<bool> column = loadVector("data/central.bin");
    std::vector<int> primes = loadPrimeVector("data/primes.csv");

    // primes.insert(primes.begin(), 1);

    cout << primes.size() * column.size();

    // column.resize(20);
    // primes.resize(8);

    ElementaryCellularAutomaton eca;

    map<int, vector<int>> populations = eca.primeNumberAnalisis(column, primes);

    // for (auto c : column)
    //     cout << c << " ";

    // cout << "\n"; 

    // for (auto p : populations)
    // {
    //     std::cout << p.first << ": ";
    //     for (auto c : p.second)
    //         std::cout << c << " ";
    //     std::cout << "\n";
    // }
}