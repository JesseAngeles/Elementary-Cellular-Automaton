#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <unordered_map>

#define START 13297

std::vector<std::vector<bool>> splitVector(std::vector<bool> &column, const int prime);

std::set<std::vector<bool>> getSet(std::vector<std::vector<bool>> &splited_vectors);

// Obtiene vectores únicos en el orden en que aparecen
std::vector<std::vector<bool>> getUniqueVectors(std::vector<std::vector<bool>> &splited_vectors);

std::vector<std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>>> evolutiveAttractor(
    std::vector<bool> column, int divisor);

std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>> sumMaps(
    const std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>>& map1,
    const std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>>& map2);

// Genera la lista de adyacencia con nodos representados como std::vector<bool>
std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>> attractors(
    std::vector<std::vector<bool>> &splited_vectors);