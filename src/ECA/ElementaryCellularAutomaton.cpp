#include "ECA/ElementaryCellularAutomaton.hpp"
#include <array>
#include <iostream>
#include <vector>

// Constructor
ElementaryCellularAutomaton::ElementaryCellularAutomaton()
{
    findLastSpace();
    setSpace();
}

<<<<<<< HEAD
// Constructor
=======
// Private functions
void ElementaryCellularAutomaton::findLastSpace()
{
    std::string last_file;
    this->generation_count = 0;
    this->min_generation = std::numeric_limits<int>::max();

    std::regex file_pattern(R"((\d+)\.bin)");
    for (const auto &entry : std::filesystem::directory_iterator(DIRECTORY))
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

                if (number < min_generation)
                    min_generation = number;
            }
        }
    }

    if (min_generation == std::numeric_limits<int>::max())
        min_generation = 1;

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
    size_t byte_count = (space.size() + 7) / 8; // Cada byte contiene hasta 8 bits
    std::vector<char> byte_buffer(byte_count, 0);

    for (size_t i = 0; i < space.size(); ++i)
    {
        if (space[i])
        {
            size_t byte_index = i / 8;
            size_t bit_index = i % 8;
            byte_buffer[byte_index] |= (1 << bit_index); // Asigna el bit en la posición correcta
        }
    }

    return byte_buffer;
}

void ElementaryCellularAutomaton::setSpace()
{
    current_file.seekg(0, std::ios::end);
    size_t file_size = current_file.tellg();
    current_file.seekg(0, std::ios::beg);

    if (file_size == 0)
    {
        std::cerr << "Error: File is empty or not readable.\n";
        return;
    }

    space.clear();
    for (size_t i = 0; i < file_size; ++i)
    {
        unsigned char byte;
        current_file.read(reinterpret_cast<char *>(&byte), sizeof(byte));

        for (size_t j = 0; j < 8; ++j) // Lee cada bit en orden
        {
            bool bit = (byte >> j) & 1;
            space.push_back(bit);
        }
    }

    truncateSpace(); // Ajustar para eliminar ceros sobrantes
}

void ElementaryCellularAutomaton::updateCurrentFile()
{
    std::vector<char> writtable_space = makeVectorWrittable();

    std::string file_name = DIRECTORY + std::string("/") + std::to_string(generation_count) + ".bin";

    if (current_file.is_open())
        current_file.close();

    current_file.open(file_name, std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);
    current_file.write(writtable_space.data(), writtable_space.size());
    current_file.flush(); // Sincronizar los datos con el sistema de archivos
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
>>>>>>> 76844b28817c9e6c1d8a679536dd9ef02f1a8c2b

// Private functions
bool ElementaryCellularAutomaton::apply(const std::array<bool, 3> &parents)
{
    int rule_index = (parents[0] << 2) | (parents[1] << 1) | parents[2];
    return (0b00011110 >> rule_index) & 1;
}

// Public functions
<<<<<<< HEAD

void ElementaryCellularAutomaton::initRandom()
{
    srand(time(NULL));
    for (int i = 0; i < space.size(); i++)
        space[i] = std::rand() % 2;
}

int ElementaryCellularAutomaton::initOne()
{
    space = std::vector(space.size(), false);
    int pos = space.size() / 2;
    space[pos] = true;

    return pos;
}

=======
>>>>>>> 76844b28817c9e6c1d8a679536dd9ef02f1a8c2b
void ElementaryCellularAutomaton::step()
{
    std::vector<bool> new_space(space.size() + 2);

    bool left = false;
    bool center = false;
    bool right = space[0];

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
    setSpace();
}

void ElementaryCellularAutomaton::compressAndClean()
{
    std::vector<int> numbers;

    // Verificar si la carpeta existe
    if (!std::filesystem::exists(DIRECTORY) || !std::filesystem::is_directory(DIRECTORY))
        return;

    // Buscar archivos con formato <numero>.bin
    for (const auto &entry : std::filesystem::directory_iterator(DIRECTORY))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            size_t dot_pos = filename.find('.');

            if (dot_pos != std::string::npos && filename.substr(dot_pos) == ".bin")
            {
                try
                {
                    int number = std::stoi(filename.substr(0, dot_pos));
                    numbers.push_back(number);
                }
                catch (const std::invalid_argument &e)
                {
                    // Ignorar archivos que no comiencen con un número
                }
            }
        }
    }

    if (numbers.empty())
        return;

    // Obtener el mínimo y el máximo
    auto [min_it, max_it] = std::minmax_element(numbers.begin(), numbers.end());
    int min_number = *min_it;
    int max_number = *max_it;

    // Crear el nombre del archivo comprimido
    std::string zip_name = DIRECTORY + std::string("/") + std::to_string(min_number) + "-" + std::to_string(max_number - 1) + ".zip";

    // Crear un archivo de lista para los archivos a comprimir
    std::ofstream file_list("file_list.txt");
    for (const auto &entry : std::filesystem::directory_iterator(DIRECTORY))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            size_t dot_pos = filename.find('.');

            if (dot_pos != std::string::npos && filename.substr(dot_pos) == ".bin")
            {
                try
                {
                    int number = std::stoi(filename.substr(0, dot_pos));
                    // Excluir el archivo con el número más alto
                    if (number != max_number)
                    {
                        file_list << entry.path().string() << "\n";
                    }
                }
                catch (const std::invalid_argument &e)
                {
                    // Ignorar archivos que no comiencen con un número
                }
            }
        }
    }
    file_list.close();

    // Comprimir los archivos seleccionados usando la lista
    std::string command = "zip -r " + zip_name + " -@ < file_list.txt";
    int result = std::system(command.c_str());

    if (result != 0)
    {
        std::cerr << "Error al comprimir los archivos." << std::endl;
        return;
    }

    // Eliminar todos los archivos excepto el último
    for (const auto &entry : std::filesystem::directory_iterator(DIRECTORY))
    {
        if (entry.is_regular_file())
        {
            std::string filename = entry.path().filename().string();
            size_t dot_pos = filename.find('.');

            if (dot_pos != std::string::npos && filename.substr(dot_pos) == ".bin")
            {
                try
                {
                    int number = std::stoi(filename.substr(0, dot_pos));
                    if (number != max_number)
                    {
                        std::filesystem::remove(entry.path());
                    }
                }
                catch (const std::invalid_argument &e)
                {
                    // Ignorar archivos que no comiencen con un número
                }
            }
        }
    }

    // Eliminar el archivo de lista temporal
    std::filesystem::remove("file_list.txt");
}

std::map<int, std::vector<int>> ElementaryCellularAutomaton::primeNumberAnalisis(
    const std::vector<bool> &column, const std::vector<int> &primes)
{
    std::map<int, std::vector<int>> populations;

    // Iterate the prime numbers
    for (const int &prime : primes)
    {
        std::vector<int> frecuencies;
        int count = 0;

        // Iterate de main column
        for (int i = 0; i < column.size(); i++)
        {
            count += column[i];
            if ((i + 1) % prime == 0)
            {
                frecuencies.push_back(count);
                count = 0;
            }
        }
    
        frecuencies.push_back(frecuencies.size() * prime);
        populations[prime] = frecuencies;

    
    }
    return populations;
}

// Getters
std::vector<bool> ElementaryCellularAutomaton::getSpace(int generation)
{
    // Encontrar el archivo
    std::string file = DIRECTORY + std::string("/") + std::to_string(generation) + ".bin";

    // Leer archivo binario o obtener el espacio
    if (current_file.is_open())
        current_file.close();

    current_file.open(file, std::ios::in | std::ios::binary);
    // if (current_file.is_open())

    setSpace();

    return space;
}

// Displays
void ElementaryCellularAutomaton::display()
{
    std::cout << std::endl;
    for (const bool &value : space)
        if (value)
            std::cout << "o"; // "1"
        else
<<<<<<< HEAD
            std::cout << " ";
=======
            std::cout << " "; // "0"
}

void ElementaryCellularAutomaton::displayFile(int generation)
{
    if (generation > generation_count)
    {
        std::cout << "Not created yet";
        return;
    }

    // Encontrar el archivo
    std::string file = DIRECTORY + std::string("/") + std::to_string(generation) + ".bin";

    // Leer archivo binario o obtener el espacio
    if (current_file.is_open())
        current_file.close();

    current_file.open(file, std::ios::in | std::ios::binary);
    // if (current_file.is_open())

    setSpace();
    display();
>>>>>>> 76844b28817c9e6c1d8a679536dd9ef02f1a8c2b
}