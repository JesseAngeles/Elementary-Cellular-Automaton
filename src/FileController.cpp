#include "FileController.hpp"

std::vector<char> makeVectorWrittable(const std::vector<bool> &vector)
{
    size_t byte_count = (vector.size() + 7) / 8; // Cada byte contiene hasta 8 bits
    std::vector<char> byte_buffer(byte_count, 0);

    for (size_t i = 0; i < vector.size(); ++i)
    {
        if (vector[i])
        {
            size_t byte_index = i / 8;
            size_t bit_index = i % 8;
            byte_buffer[byte_index] |= (1 << bit_index); // Asigna el bit en la posición correcta
        }
    }

    return byte_buffer;
}

void saveVector(const std::vector<char> &vector, const std::string &filename)
{
    std::string file_name = filename + ".bin";

    std::fstream current_file;
    current_file.open(file_name, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    current_file.write(vector.data(), vector.size());
    current_file.flush();
}

std::vector<bool> loadVector(const std::string &filename)
{
    std::ifstream file;
    std::vector<bool> space;

    file.open(filename, std::ios::in | std::ios::binary);

    if (!file.is_open())
    {
        space.clear();
        return space;
        
    }
        
    file.seekg(0, std::ios::end);
    size_t file_size = file.tellg();
    file.seekg(0, std::ios::beg);

    if (file_size == 0)
        return space;

    for (size_t i = 0; i < file_size; ++i)
    {
        unsigned char byte;
        file.read(reinterpret_cast<char *>(&byte), sizeof(byte));

        for (size_t j = 0; j < 8; ++j) // Lee cada bit en orden
        {
            bool bit = (byte >> j) & 1;
            space.push_back(bit);
        }
    }

    truncateVector(space);

    return space;
}

void truncateVector(std::vector<bool> &vector)
{
    size_t start = 0;
    while (start < vector.size() && !vector[start])
    {
        ++start; // Avanzar hasta encontrar el primer 'true'
    }

    // Buscar el último valor 'true'
    size_t end = vector.size();
    while (end > start && !vector[end - 1])
    {
        --end; // Retroceder hasta encontrar el último 'true'
    }

    // Crear un nuevo vector con los valores entre 'inicio' y 'fin'
    vector = std::vector<bool>(vector.begin() + start, vector.begin() + end);
}
