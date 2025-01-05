#ifndef HISTOGRAM_ANALYSIS_HPP
#define HISTOGRAM_ANALYSIS_HPP

#include <vector>
#include <algorithm>
#include <utility>

std::vector<std::pair<int, int>> generateHistogram(std::vector<int> instance)
{
    // Obtener el valor "primo" (asumido como el primer elemento + 1)
    int prime = instance[0] + 1;

    // Eliminar el primer elemento (primo) y el último valor
    instance = std::vector<int>(instance.begin() + 1, instance.end() - 1);

    // Contar las frecuencias en un mapa (reduce los ceros)
    std::map<int, int> frequencyMap;
    for (const int &value : instance)
        frequencyMap[value]++;

    // Convertir el mapa en un vector de pares
    std::vector<std::pair<int, int>> histogram;
    for (const auto &entry : frequencyMap)
        histogram.emplace_back(entry.first, entry.second);

    // Ordenar por el valor (opcional, ya que std::map garantiza orden)
    std::sort(histogram.begin(), histogram.end());

    // Limpiar el vector original
    instance.clear();

    return histogram;
}

#endif // HISTOGRAM_ANALYSIS_HPP