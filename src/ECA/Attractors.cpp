#include "./ECA/Attractors.hpp"

std::vector<std::vector<bool>> splitVector(std::vector<bool> &column, const int prime)
{
    std::vector<std::vector<bool>> splited_vectors(column.size() / prime);

    for (int i = 0; i + prime <= column.size(); i += prime)
        splited_vectors[i / prime] = std::vector(column.begin() + i, column.begin() + i + prime);

    return splited_vectors;
}

std::set<std::vector<bool>> getSet(std::vector<std::vector<bool>> &splited_vectors)
{
    std::set<std::vector<bool>> set_attractor;
    int lenght = splited_vectors[0].size();

    int i = 0;
    do
        set_attractor.insert(splited_vectors[i++]);
    while (set_attractor.size() < std::pow(2, lenght));

    return set_attractor;
}

// Obtiene vectores únicos en el orden en que aparecen
std::vector<std::vector<bool>> getUniqueVectors(std::vector<std::vector<bool>> &splited_vectors)
{
    std::vector<std::vector<bool>> unique_vectors;
    std::unordered_map<std::vector<bool>, int> seen;

    for (const auto &vec : splited_vectors)
    {
        if (seen.find(vec) == seen.end()) // Solo agregar si no ha sido visto antes
        {
            seen[vec] = unique_vectors.size();
            unique_vectors.push_back(vec);
        }
    }
    return unique_vectors;
}

std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>> sumMaps(
    const std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>> &map1,
    const std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>> &map2)
{
    // Inicia el resultado con los elementos de map1
    std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>> result = map1;

    // Itera sobre las claves de map2
    for (const auto &[key, value] : map2)
    {
        if (result.find(key) != result.end())
        {
            // La clave ya existe en el resultado, combinar valores
            auto &resultValues = result[key];
            for (const auto &pair : value)
            {
                // Busca si el vector<bool> ya existe en el resultado
                auto it = std::find_if(
                    resultValues.begin(),
                    resultValues.end(),
                    [&pair](const std::pair<std::vector<bool>, int> &existingPair)
                    {
                        return existingPair.first == pair.first;
                    });

                if (it != resultValues.end())
                {
                    // Si ya existe, suma el valor entero
                    it->second += pair.second;
                }
                else
                {
                    // Si no existe, agrégalo
                    resultValues.push_back(pair);
                }
            }
        }
        else
        {
            // La clave no existe en el resultado, simplemente copia los valores
            result[key] = value;
        }
    }

    return result;
}

// Genera la lista de adyacencia con nodos representados como std::vector<bool>
std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>> attractors(std::vector<std::vector<bool>> &splited_vectors)
{
    std::vector<std::vector<bool>> vector_attractor = getUniqueVectors(splited_vectors);
    std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>> adjacencyList;

    std::vector<bool> current = splited_vectors[0];

    for (size_t i = 1; i < splited_vectors.size(); i++)
    {
        std::vector<bool> from = current;
        std::vector<bool> to = splited_vectors[i];

        // Verificar si la conexión ya existe y aumentar el peso
        bool found = false;
        for (auto &edge : adjacencyList[from])
        {
            if (edge.first == to)
            {
                edge.second++;
                found = true;
                break;
            }
        }
        if (!found)
            adjacencyList[from].emplace_back(to, 1);

        current = splited_vectors[i];
    }

    return adjacencyList;
}

#include <iostream>

std::vector<std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>>> evolutiveAttractor(
    std::vector<bool> column, int divisor)
{
    // Dividir el vector en subvectores
    std::vector<std::vector<bool>> splited = splitVector(column, divisor);

    // Obtener las matrices de frecuencias transicionales
    std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>> matrix;

    // Almacenarlas en un vector
    std::vector<std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>>> evolutive;

    int increment = std::pow(std::pow(2, divisor), 2);

    int i = START - START % divisor;
    std::vector<std::vector<bool>> sub_splited = std::vector(splited.begin(), splited.begin() + i);
    evolutive.push_back(attractors(sub_splited));

    while (i < column.size())
    {
        sub_splited = std::vector(splited.begin() + i - 1, splited.begin() + i + increment);
        evolutive.push_back(sumMaps(evolutive[evolutive.size() - 1], attractors(sub_splited)));
    
        i += increment;
    }

    return evolutive;
}
