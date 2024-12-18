#include <iostream>

#include "ECA/ElementaryCellularAutomaton.hpp"
#include "FileController.hpp"

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

    vector<bool> new_vector = loadVector("data/central.bin");
    
    new_vector.resize(eca.getGenerationCount());

    for (int i = eca.getMinGeneration(); i <= eca.getGenerationCount(); i++)
    {
        vector<bool> space = eca.getSpace(i);
        new_vector[i - 1] = space[space.size()/2];
    }
    
    // Display mid vector
    for (const bool &value : new_vector)
        cout << value << " ";

    cout << "size: " << new_vector.size() << endl;

    saveVector(makeVectorWrittable(new_vector), "data/central");

    new_vector.clear();

    return 0;
}