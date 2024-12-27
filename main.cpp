#include <iostream>

#include "ECA/ElementaryCellularAutomaton.hpp"
#include "ECA/Rule30.hpp"

#include "GUI/Grapher.h"

#include "Functions.h"
#include "PrimeGenerator.hpp"
#include "FileController.hpp"

using namespace std;

int mainMenu();
int generationsMenu();
int displayMenu();

void calculateGenerations();
void graphicMode();
void primeAnalisis();


int main()
{
    int option = mainMenu();

    switch (option)
    {
    case 1:
        calculateGenerations();
        break;
    case 2:
        graphicMode();
        break;
    case 3:
        primeAnalisis();
        break;
    }

    return 0;
}

int mainMenu()
{
    int option;
    cout << "1) Generations\n";
    cout << "2) Graphic mode\n";
    cout << "3) Prime analisis\n";

    cin >> option;

    return option;
}

int generationsMenu()
{
    int option;
    cout << "0) Display generation\n";
    cout << "n) Create N generations\n";

    cin >> option;

    return option;
}

int displayMenu()
{
    int option;
    cout << "0) All generated generations\n";
    cout << "n) The N generation\n";

    cin >> option;

    return option;
}

void calculateGenerations()
{
    Rule30 eca;

    int main_option = generationsMenu();
    if (!main_option)
    {
        int display_option = displayMenu();
        if (!display_option)
            // Display all options
            for (int i = 1; i <= eca.getGenerationCount(); i++)
                eca.displayFile(i);
        else
            // Display especific generation
            eca.displayFile(display_option);
    }
    else
    {
        bool display = false;

        cout << "Display (0, 1): ";
        cin >> display;

        if (display)
            for (int i = 0; i < main_option; i++)
            {
                eca.step();
                eca.display();
            }
        else
            for (int i = 0; i < main_option; i++)
                eca.step();
    }

    std::cout << "";

    bool compress;
    std::cout << "\nCompress (0, 1): ";
    cin >> compress;

    if (compress)
        eca.compressAndClean();
}

void graphicMode()
{
    int rule = 0;
    ElementaryCellularAutomaton eca(getBinary(rule, 8), 100);
    Grapher gui(1920, 1080, "Elementary Cellular Automaton", {255, 255, 255}, eca);
    gui.mainLoop();
}

void primeAnalisis()
{
    // Generar numeros primos
    std::vector<bool> column = loadVector("data/central.bin");
    std::vector<int> primes = loadPrimeVector("data/primes.csv");

    // primes.insert(primes.begin(), 1);

    cout << primes.size() * column.size();

    // column.resize(20);
    // primes.resize(8);

    Rule30 eca;

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