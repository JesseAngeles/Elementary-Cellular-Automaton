#include <iostream>

#include <vector>
#include <algorithm>

#include "ECA/ElementaryCellularAutomaton.hpp"
#include "GUI/Grapher.h"

using namespace std;

vector<bool> getBinary(int &number, const int &vector_size);
void displayVector(const vector<bool> &);

int main()
{
    Grapher gui(1500, 500, "hola", {255, 255, 255});
    gui.mainLoop();
}

int main1()
{
    int number;
    cout << "Numero en decimal: ";
    cin >> number;

    ElementaryCellularAutomaton eca(getBinary(number, 8), 51);
    
    eca.initOne();
    eca.run(50, true);
    // eca.display();

    return 0;
}

vector<bool> getBinary(int &number, const int &vector_size)
{
    // Es cero
    if (!number)
        return vector(vector_size, false);

    vector<bool> binary(vector_size, false);

    int i = 0;
    while (number >= 1)
    {
        binary[i++] = !(number % 2 == 0);
        number /= 2;
    }

    reverse(binary.begin(), binary.end());
    return binary;
}

void displayVector(const vector<bool> &vector)
{
    for (const bool &element : vector)
        cout << element << " ";
    cout << endl;
}