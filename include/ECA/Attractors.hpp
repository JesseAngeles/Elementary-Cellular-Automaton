#include <vector>
#include <set>
#include <cmath>
#include <algorithm>

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

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<bool>>> attractors(std::vector<std::vector<bool>> &splited_vectors)
{
    std::set<std::vector<bool>> set_attractor = getSet(splited_vectors);
    std::vector<std::vector<bool>> vector_attractor(set_attractor.begin(), set_attractor.end());

    int lenght = splited_vectors[0].size();
    std::vector<std::vector<int>> attractors(std::pow(2, lenght), std::vector<int>(std::pow(2, lenght), 0));

    std::vector<bool> current = splited_vectors[0];

    for (int i = 1; i < splited_vectors.size(); i++)
    {
        auto it = std::find(vector_attractor.begin(), vector_attractor.end(), current);
        int from = std::distance(vector_attractor.begin(), it); 

        it = std::find(vector_attractor.begin(), vector_attractor.end(), splited_vectors[i]);
        int to = std::distance(vector_attractor.begin(), it); 

        attractors[from][to]++;

        current = splited_vectors[i];
    }

    return make_pair(attractors, vector_attractor);
}