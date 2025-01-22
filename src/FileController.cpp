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

std::string vectorToString(const std::vector<bool> &vec)
{
    std::string result;
    for (bool b : vec)
        result += (b ? '1' : '0');
    return result;
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

void saveCSV(const std::vector<std::vector<long double>> &data,
             const std::vector<std::string> &headers,
             const std::string &filename)
{
    // Abrir archivo en modo de escritura
    std::ofstream file(filename);

    // Configuración para mayor precisión en formato científico
    file << std::scientific << std::setprecision(15);

    // Escribir encabezados
    for (const std::string &header : headers)
        file << header << ",";
    file << std::endl;

    // Escribir los elementos del vector en el archivo
    for (const std::vector<long double> &vector : data)
    {
        // Imprimir los primeros tres valores "tal cual"
        for (size_t i = 0; i < vector.size(); ++i)
        {
            if (i < 4) // Los primeros tres valores en formato normal
            {
                file << std::fixed << vector[i];
            }
            else // El resto en formato científico
            {
                file << std::scientific << vector[i];
            }

            // Añadir coma después de cada valor, excepto al final de la fila
            if (i != vector.size() - 1)
                file << ",";
        }
        file << std::endl;
    }

    // Cerrar el archivo
    file.close();
}

void saveIntPairMatrix(const std::vector<std::vector<std::pair<int, int>>> &matrix, const std::string &filename)
{
    std::ofstream outFile(filename);
    if (!outFile.is_open())
    {
        throw std::runtime_error("Error al abrir el archivo para escribir: " + filename);
    }

    for (const auto &row : matrix)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            const auto &pair = row[i];
            outFile << pair.first << ":" << pair.second; // Guardar cada par como "valor:frecuencia"
            if (i != row.size() - 1)
                outFile << ","; // Separar pares con comas
        }
        outFile << "\n"; // Nueva línea al final de cada fila
    }

    outFile.close();
}

void saveTransition(
    const std::vector<std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>>> &data,
    const std::string &filename)
{
    std::ofstream file(filename);

    // Escribir encabezado
    file << "from,to,weight\n";

    // Escribir cada transición
    for (const auto &adjList : data)
    {
        for (const auto &node : adjList)
        {
            std::string from = vectorToString(node.first);
            for (const auto &edge : node.second)
            {
                std::string to = vectorToString(edge.first);
                int weight = edge.second;
                file << from << "," << to << "," << weight << "\n";
            }
        }
        file << "\n";
    }

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

std::vector<std::vector<long double>> readCSV(const std::string &filename)
{
    std::vector<std::vector<long double>> data;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        throw std::runtime_error("Error: No se pudo abrir el archivo " + filename);
    }

    std::string line;
    bool first_line = true;

    while (std::getline(file, line))
    {
        std::stringstream line_stream(line);
        std::string cell;
        std::vector<long double> row;

        // Ignorar la primera línea de encabezados
        if (first_line)
        {
            first_line = false;
            continue;
        }

        // Leer cada celda separada por comas
        while (std::getline(line_stream, cell, ','))
        {
            // Manejar celdas vacías
            if (cell.empty())
            {
                row.push_back(0.0L); // O un valor por defecto
            }
            else
            {
                try
                {
                    row.push_back(std::stold(cell));
                }
                catch (const std::invalid_argument &)
                {
                    throw std::runtime_error("Error: No se pudo convertir el valor '" + cell + "' a long double.");
                }
            }
        }

        if (!row.empty())
        {
            data.push_back(row);
        }
    }

    file.close();
    return data;
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

std::vector<std::vector<std::pair<int, int>>> loadIntPairMatrix(const std::string &filename)
{
    std::ifstream inFile(filename);
    if (!inFile.is_open())
    {
        throw std::runtime_error("Error al abrir el archivo para leer: " + filename);
    }

    std::vector<std::vector<std::pair<int, int>>> matrix;
    std::string line;

    while (std::getline(inFile, line))
    {
        std::vector<std::pair<int, int>> row;
        std::stringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, ','))
        {
            size_t colonPos = cell.find(':');
            if (colonPos != std::string::npos)
            {
                int value = std::stoi(cell.substr(0, colonPos));
                int frequency = std::stoi(cell.substr(colonPos + 1));
                row.emplace_back(value, frequency);
            }
        }
        matrix.push_back(row);
    }

    inFile.close();
    return matrix;
}