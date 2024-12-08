#include "ECA/ElementaryCellularAutomaton.hpp"

// Constructor

// Private functions
bool ElementaryCellularAutomaton::apply(const std::array<bool, 3> &parents)
{
    if (parents[0] && parents[1] && parents[2])
        return rule[0];
    if (parents[0] && parents[1] && !parents[2])
        return rule[1];
    if (parents[0] && !parents[1] && parents[2])
        return rule[2];
    if (parents[0] && !parents[1] && !parents[2])
        return rule[3];
    if (!parents[0] && parents[1] && parents[2])
        return rule[4];
    if (!parents[0] && parents[1] && !parents[2])
        return rule[5];
    if (!parents[0] && !parents[1] && parents[2])
        return rule[6];
    // if (!parents[0] && !parents[1] && !parents[2])
    return rule[7];
}

// Public functions

void ElementaryCellularAutomaton::initRandom()
{
    srand(time(NULL));
    for (int i = 0; i < space.size(); i++)
        space[i] = std::rand() % 2;
}

void ElementaryCellularAutomaton::initOne()
{
    space = std::vector(space.size(), false);
    space[space.size() / 2] = true;
}

void ElementaryCellularAutomaton::step()
{
    std::vector<bool> new_gen(space.size());

    for (int i = 0; i < space.size(); i++)
        new_gen[i] = apply(std::array<bool, 3>{
            space[(i - 1 + space.size()) % space.size()],
            space[i],
            space[(i + 1) % space.size()]});

    space = new_gen;
}

void ElementaryCellularAutomaton::run(int steps, bool print)
{

    for (int i = 0; i < steps; i++)
    {
        if (print)
            display();
        step();
    }

    display();
}

void ElementaryCellularAutomaton::display()
{
    std::cout << std::endl;
    for (const bool &value : space)
        if (value)
            std::cout << "o";
        else
            std::cout << " ";
}