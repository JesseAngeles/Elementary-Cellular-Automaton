#ifndef ELEMENTARY_CELULLAR_AUTOMATON_H
#define ELEMENTARY_CELULLAR_AUTOMATON_H

#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

class ElementaryCellularAutomaton
{
private:
    // Attributes
    std::vector<bool> space;
    int generation_count;

    // Functions
    bool apply(const std::array<bool, 3> &parents);

public:
    // Constructor
    ElementaryCellularAutomaton()
        : generation_count(0), space(1, true) {}

    // Functions
    void step();
    void run(int steps, bool print);

    // Getters

    // Setters

    // Displays
    void display();
};

#endif // ELEMENTARY_CELULLAR_AUTOMATON_H