#include <iostream>

#include "ECA/ElementaryCellularAutomaton.hpp"
#include "GUI/Grapher.h"

using namespace std;

int mainMenu()
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

int main()
{
    ElementaryCellularAutomaton eca;

    int main_option = mainMenu();
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

    return 0;
}