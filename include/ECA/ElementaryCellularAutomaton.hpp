#ifndef ELEMENTARY_CELULLAR_AUTOMATON_H
#define ELEMENTARY_CELULLAR_AUTOMATON_H

#include <array>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

#include <fstream>
#include <filesystem>
#include <regex>

class ElementaryCellularAutomaton
{
private:
    // Attributes
    std::vector<bool> space;
    int generation_count;
    std::fstream current_file;

    // Functions
    void findLastSpace();
    std::vector<char> makeVectorWrittable();
    void setSpace();
    void updateCurrentFile();
    void truncateSpace();

    bool apply(const std::array<bool, 3> &parents);

public:
    // Constructor
    ElementaryCellularAutomaton();

    // Functions
    void step();

    // Displays
    void display();
};

#endif // ELEMENTARY_CELULLAR_AUTOMATON_H