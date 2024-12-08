#include <iostream>

#include <vector>
#include <algorithm>

#include "ECA/ElementaryCellularAutomaton.hpp"
#include "GUI/Grapher.h"
#include "Functions.h"

using namespace std;

int main()
{
    int rule = 0;
    ElementaryCellularAutomaton eca(getBinary(rule, 8), 100);
    Grapher gui(1500, 500, "Elementary Cellular Automaton", {255, 255, 255}, eca);
    gui.mainLoop();
}

