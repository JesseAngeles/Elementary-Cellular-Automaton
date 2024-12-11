#include "ECA/ElementaryCellularAutomaton.hpp"
#include <array>
#include <iostream>
#include <vector>

// Private functions
bool ElementaryCellularAutomaton::apply(const std::array<bool, 3> &parents)
{
    // Convertir los padres en un número binario de 3 bits
    int rule_index = (parents[0] << 2) | (parents[1] << 1) | parents[2];

    return (0b00011110 >> rule_index) & 1;
}

// Public functions
void ElementaryCellularAutomaton::step()
{
    // Aumentar el tamaño del espacio (relleno con celdas falsas)
    std::vector<bool> new_space(space.size() + 2);

    // Inicializar las celdas ficticias
    bool left = false;
    bool center = false;
    bool right = space[0];

    // std::cout << "\n";

    // Iterar sobre el espacio original
    for (size_t i = 0; i < new_space.size(); ++i)
    {
        new_space[i] = apply({left, center, right});
        // std::cout << left << "-" << center << "-" << right << "=" << new_space[i] << "\n";
        left = center;
        center = right;
        right = (i + 1 < space.size()) ? space[i + 1] : false;
    }

    // Reasignar espacio
    space = new_space;
}

void ElementaryCellularAutomaton::run(int steps, bool print)
{
    for (int i = 0; i < steps; ++i)
    {
        if (print)
            display();
        step();
    }

    if (print)
        display();
}

void ElementaryCellularAutomaton::display()
{
    std::cout << std::endl;
    for (const bool &value : space)
        if (value)
            std::cout << "o"; // Representa "1"
        else
            std::cout << " "; // Representa "0"
}
