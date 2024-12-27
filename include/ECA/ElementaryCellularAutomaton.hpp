#ifndef ELEMENTARY_CELULLAR_AUTOMATON_H
#define ELEMENTARY_CELULLAR_AUTOMATON_H

#include <array>
#include <vector>
#include <map>
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
    int min_generation;
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

    // Prime number analisis
    std::map<int, std::vector<int>> primeNumberAnalisis(const std::vector<bool> &column, const std::vector<int> &prime);

    // Getters
    int getGenerationCount() const { return generation_count; }
    int getMinGeneration() const { return min_generation; }
    std::vector<bool> getSpace(int generation);

    // Displays
    void display();
    void displayFile(int generation);
};

#endif // ELEMENTARY_CELULLAR_AUTOMATON_H