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

void saveBoolVector(const std::vector<bool> &vector, const std::string &filename)
{
    std::vector<char> writtable_vector = makeVectorWrittable(vector);

    std::string file_name = filename + ".bin";

    std::fstream current_file;
    current_file.open(file_name, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    current_file.write(writtable_vector.data(), writtable_vector.size());
    current_file.flush();
}

void saveIntVector(const std::vector<int> &vector, const std::string &filename)
{
    // Abrir archivo en modo de escritura
    std::ofstream file(filename);

    // Escribir los elementos del vector en el archivo
    for (const int &prime : vector)
        file << prime << ",";

    // Cerrar el archivo
    file.close();
}

void saveIntMatrix(const std::vector<std::vector<int>> &matrix, const std::string &filename)
{
    // Abrir archivo en modo de escritura
    std::ofstream file(filename);

    // Escribir los elementos del vector en el archivo
    for (const std::vector<int> &vector : matrix)
    {
        for (const int &prime : vector)
            file << prime << ",";
        file << std::endl;
    }

    // Cerrar el archivo
    file.close();
}

std::vector<bool> loadBoolVector(const std::string &filename)
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

std::vector<int> loadIntVector(const std::string &filename)
{
    std::vector<int> primes;
    std::ifstream file(filename);

    // Verificar si el archivo se abrió correctamente
    if (!file.is_open())
        return primes;

    std::string line;
    // Leer la línea completa del archivo
    if (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string number;

        // Separar los números por comas
        while (std::getline(ss, number, ','))
        {
            primes.push_back(std::stoi(number)); // Convertir a entero y agregar al vector
        }
    }

    file.close();
    return primes;
}

std::vector<std::vector<int>> loadMatrix(const std::string &filename)
{
    std::vector<std::vector<int>> prime_analisis;
    std::ifstream file(filename);

    std::string line;

    // Verificar si el archivo se abrió correctamente
    if (!file.is_open())
        return prime_analisis;

    while (std::getline(file, line))
    {
        std::vector<int> primes;

        std::stringstream ss(line);
        std::string number;

        // Separar los números por comas
        while (std::getline(ss, number, ','))
        {
            primes.push_back(std::stoi(number)); // Convertir a entero y agregar al vector
        }

        prime_analisis.push_back(primes);
    }

    file.close();
    return prime_analisis;
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
