#include "ECA/ElementaryCellularAutomaton.hpp"
#include <array>
#include <iostream>
#include <vector>

// Constructor
ElementaryCellularAutomaton::ElementaryCellularAutomaton()
// : generation_count(0), space(1, true)
{
    findLastSpace();
    setSpace();
    truncateSpace();

    current_file.close();
}

// Private functions
void ElementaryCellularAutomaton::findLastSpace()
{
    std::string directory = "resources";
    std::string last_file;
    this->generation_count = 0;

    std::regex file_pattern(R"((\d+)\.bin)");
    for (const auto &entry : std::filesystem::directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            std::smatch match;
            std::string filename = entry.path().filename().string();
            if (std::regex_match(filename, match, file_pattern))
            {
                int number = std::stoi(match[1].str());
                if (number > generation_count)
                {
                    generation_count = number;
                    last_file = entry.path().string();
                }
            }
        }
    }

    if (!generation_count)
    {

        // Inicilizar espacio
        generation_count++;
        space = {true};
        std::vector<char> writtable_space = makeVectorWrittable();

        // Inicializar el archivo
        current_file = std::fstream("resources/1.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
        current_file.write(writtable_space.data(), writtable_space.size());
    }
    else
    {
        // Abrir el archivo ya existente
        current_file = std::fstream(last_file, std::ios::in | std::ios::out | std::ios::binary);
    }
}

std::vector<char> ElementaryCellularAutomaton::makeVectorWrittable()
{
    size_t byte_count = (space.size() + 7) / 8;
    std::vector<char> byte_buffer(byte_count, 0);

    for (size_t i = 0; i < space.size(); ++i)
        if (space[i])
            byte_buffer[i / 8] |= (1 << (i % 8));

    return byte_buffer;
}

void ElementaryCellularAutomaton::setSpace()
{
    // Mover al final del archivo para conocer su tamaño
    current_file.seekg(0, std::ios::end);
    size_t file_size = current_file.tellg();

    current_file.seekg(0, std::ios::beg); // Regresar al inicio del archivo

    space.clear();
    // Leer byte por byte
    for (size_t i = 0; i < file_size; ++i)
    {
        unsigned char byte;
        current_file.read(reinterpret_cast<char *>(&byte), sizeof(byte));

        // Convertir cada byte a bits y almacenarlos en el vector
        for (int j = 7; j >= 0; --j)
        {
            bool bit = (byte >> j) & 1;
            space.push_back(bit);
        }
    }

    current_file.close(); // Cerrar el archivo después de leer
}

void ElementaryCellularAutomaton::updateCurrentFile()
{
    std::vector<char> writtable_space = makeVectorWrittable();

    // Inicializar el archivo
    std::string file_name = "resources/" + std::to_string(generation_count) + ".bin";
    current_file = std::fstream(file_name, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    current_file.write(writtable_space.data(), writtable_space.size());
}

void ElementaryCellularAutomaton::truncateSpace()
{
    size_t start = 0;
    while (start < space.size() && !space[start])
    {
        ++start; // Avanzar hasta encontrar el primer 'true'
    }

    // Buscar el último valor 'true'
    size_t end = space.size();
    while (end > start && !space[end - 1])
    {
        --end; // Retroceder hasta encontrar el último 'true'
    }

    // Crear un nuevo vector con los valores entre 'inicio' y 'fin'
    space = std::vector<bool>(space.begin() + start, space.begin() + end);
}

bool ElementaryCellularAutomaton::apply(const std::array<bool, 3> &parents)
{
    int rule_index = (parents[0] << 2) | (parents[1] << 1) | parents[2];
    return (0b00011110 >> rule_index) & 1;
}

// Public functions
void ElementaryCellularAutomaton::step()
{
    std::vector<bool> new_space(space.size() + 2);

    bool left = false;
    bool center = false;
    bool right = space[0];

    // Iterar sobre el espacio original
    for (size_t i = 0; i < new_space.size(); ++i)
    {
        new_space[i] = apply({left, center, right});
        left = center;
        center = right;
        right = (i + 1 < space.size()) ? space[i + 1] : false;
    }

    space = new_space;
    generation_count++;
    updateCurrentFile();
}

void ElementaryCellularAutomaton::display()
{
    std::cout << std::endl;
    for (const bool &value : space)
        if (value)
            std::cout << "o"; // "1"
        else
            std::cout << " "; // "0"
}
