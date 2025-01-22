#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <unordered_map>

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