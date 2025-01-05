#ifndef STATISTICAL_ANALYSIS_HPP
#define STATISTICAL_ANALYSIS_HPP

#include <vector>
#include <unordered_map>

long double mean(const std::vector<int> &vector)
{
    long double mean = 0.0L;
    for (const int &element : vector)
        mean += element;

    return mean / static_cast<long double>(vector.size());
}

long double median(std::vector<int> data)
{
    size_t size = data.size();
    if (size == 0)
        throw std::invalid_argument("El conjunto de datos está vacío.");

    std::sort(data.begin(), data.end());
    if (size % 2 == 0)
    {
        return (data[size / 2 - 1] + data[size / 2]) / 2.0L;
    }
    else
    {
        return data[size / 2];
    }
}

int mode(const std::vector<int> &data)
{
    if (data.empty())
    {
        throw std::invalid_argument("El conjunto de datos está vacío.");
    }
    std::unordered_map<int, int> frequency;
    for (int num : data)
    {
        frequency[num]++;
    }
    int mode = data[0];
    int max_count = 0;
    for (const auto &pair : frequency)
    {
        if (pair.second > max_count)
        {
            max_count = pair.second;
            mode = pair.first;
        }
    }
    return mode;
}

long double standardDeviation(const std::vector<int> &data, const long double &mean, bool bessel = false)
{
    long double accum = 0.0L;
    std::for_each(data.begin(), data.end(), [&](const double value)
                  { accum += (value - mean) * (value - mean); });
    return std::sqrt(accum / (data.size() - bessel));
}

long double momentAboutMean(const std::vector<int> &data, const int &moment, const long double &mean)
{
    long double accum = 0.0L;
    std::for_each(data.begin(), data.end(), [&](const double value)
                  { accum += std::pow(value - mean, moment); });
    return accum / static_cast<long double>(data.size());
}

#endif // STATISTICAL_ANALYSIS_HPP