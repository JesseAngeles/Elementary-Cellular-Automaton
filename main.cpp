#include <iostream>

#include "ECA/Rule30.hpp"
#include "ECA/Attractors.hpp"
#include "ECA/StatisticalAnalysis.hpp"
#include "ECA/HistogramAnalysis.hpp"

#include "Functions.h"
#include "PrimeGenerator.hpp"
#include "FileController.hpp"

using namespace std;

int mainMenu();
int generationsMenu();
int displayMenu();

void calculateGenerations();
void mainColumn();

void attractors();

int main()
{
    // int option = mainMenu();
    int option = 3;

    switch (option)
    {
    case 1:
        calculateGenerations();
        break;
    case 2:
        mainColumn();
        break;
    case 3:
        attractors();
        break;
    }

    return 0;
}

int mainMenu()
{
    int option;
    cout << "1) Generations\n";
    cout << "2) Main column size \n";
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

    cout << "";

    bool compress;
    cout << "\nCompress (0, 1): ";
    cin >> compress;

    if (compress)
        eca.compressAndClean();
}

void mainColumn()
{
    Rule30 eca;
    vector<bool> column = loadBoolVector("data/central.bin");
    column.resize(eca.getGenerationCount());

    for (int i = eca.getMinGeneration(); i <= eca.getGenerationCount(); i++)
    {
        vector<bool> space = eca.getSpace(i);
        column[i - 1] = space[space.size() / 2];
    }

    // Display mid vector
    for (const bool &value : column)
        cout << value << " ";

    std::cout << "Size: " << column.size();

    saveBoolVector(column, "data/central");

    column.clear();
}

void attractors()
{
    vector<bool> column = loadBoolVector("data/central.bin");
    if (column.size() % 100 != 0)
        column.resize(column.size() + 100 - column.size() % 100);

    // for(auto b : column)
    //     cout << b;
    // cout << endl;
    cout << column.size() << endl;

    vector<vector<bool>> splited = splitVector(column, 1);
    std::pair<std::vector<std::vector<int>>, std::vector<std::vector<bool>>> data = attractors(splited);
    std::vector<std::vector<int>> attractor = data.first;
    std::vector<std::vector<bool>> names = data.second;

    cout << "\t";
    for (auto name : names)
    {
        for (auto c : name)
            cout << c;
        cout << "\t";
    }
    cout << endl;

    for (int i = 0; i < attractor.size(); i++)
    {
        for (auto c : names[i])
            cout << c;

        cout << "\t";
        for (auto c : attractor[i])
            cout << c << "\t";
        cout << endl;
    }
}