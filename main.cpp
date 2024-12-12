#include <iostream>

#include "ECA/ElementaryCellularAutomaton.hpp"

using namespace std;

int main()
{
    ElementaryCellularAutomaton eca;

    int max;
    bool display;

    cout << "Generations to create: ";
    cin >> max;

    cout << "Display (0, 1): ";
    cin >> display;

    if (display)
        for (int i = 0; i < max; i++)
        {
            eca.step();
            eca.display();
        }
    else
        for (int i = 0; i < max; i++)
            eca.step();

    return 0;
}