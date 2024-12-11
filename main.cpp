#include <iostream>

#include "ECA/ElementaryCellularAutomaton.hpp"

using namespace std;

int main()
{
    ElementaryCellularAutomaton eca;

    int i = 0;
    do
    {
        eca.step();
        cout << i << "\n";
    } while (++i > 0);
    

    return 0;
}