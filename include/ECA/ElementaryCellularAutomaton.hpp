
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
    std::vector<bool> rule;
    std::vector<bool> space;

    // Functions
    bool apply(const std::array<bool, 3> &parents);

public:
    // Constructor
    ElementaryCellularAutomaton(const std::vector<bool> &rule, int space)
        : rule(rule), space(space, false) {};

    // Functions
    void initRandom();
    int initOne();

    void step();
    void run(int steps, bool print = false);

    // Getters
    const std::vector<bool> getRule() const { return rule; }
    const std::vector<bool> getSpace() const { return space; }

    // Setters
    void setRule(const std::vector<bool> &rule) { this->rule = rule; }
    void setSpace(const std::vector<bool> &space) { this->space = space; }
    void switchCell(int pos) { space[pos] = !space[pos]; }

    // Displays
    void display();
};

#endif // ELEMENTARY_CELULLAR_AUTOMATON_H
