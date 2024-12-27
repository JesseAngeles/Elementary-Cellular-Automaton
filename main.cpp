// #include <iostream>

// #include "ECA/ElementaryCellularAutomaton.hpp"
// #include "GUI/Grapher.h"
// #include "Functions.h"

// using namespace std;

// int main()
// {
//     int rule = 0;
//     ElementaryCellularAutomaton eca(getBinary(rule, 8), 100);
//     Grapher gui(1920, 1080, "Elementary Cellular Automaton", {255, 255, 255}, eca);
//     gui.mainLoop();
// }

// #include "PrimeGenerator.hpp"
// #include "FileController.hpp"

// using namespace std;

// int displayMenu()
// {
//     int option;
//     cout << "0) All generated generations\n";
//     cout << "n) The N generation\n";

//     cin >> option;

//     return option;
// }

// int main()
// {
//     // Generar numeros primos
//     std::vector<bool> column = loadVector("data/central.bin");
//     std::vector<int> primes = loadPrimeVector("data/primes.csv");

//     // primes.insert(primes.begin(), 1);

//     cout << primes.size() * column.size();

//     // column.resize(20);
//     // primes.resize(8);

//     ElementaryCellularAutomaton eca;

//     map<int, vector<int>> populations = eca.primeNumberAnalisis(column, primes);

//     // for (auto c : column)
//     //     cout << c << " ";

//     // cout << "\n"; 

//     // for (auto p : populations)
//     // {
//     //     std::cout << p.first << ": ";
//     //     for (auto c : p.second)
//     //         std::cout << c << " ";
//     //     std::cout << "\n";
//     // }
// }
