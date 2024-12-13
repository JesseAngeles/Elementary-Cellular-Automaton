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
#include <cstdlib>

#define DIRECTORY "resources"

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
    void compressAndClean();

    // Getters
    int getGenerationCount() const { return generation_count; }

    // Displays
    void display();
    void displayFile(int generation);
};

#endif // ELEMENTARY_CELULLAR_AUTOMATON_H