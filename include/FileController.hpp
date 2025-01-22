#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unordered_map>

std::vector<char> makeVectorWrittable(const std::vector<bool> &vector);
std::string vectorToString(const std::vector<bool> &vec);

void saveBoolVector(const std::vector<bool> &vector, const std::string &filename);
void saveIntVector(const std::vector<int> &vector, const std::string &filename);
void saveIntMatrix(const std::vector<std::vector<int>> &matrix, const std::string &filename);
void saveCSV(const std::vector<std::vector<long double>> &matrix,
             const std::vector<std::string> &headers,
             const std::string &filename);
void saveIntPairMatrix(const std::vector<std::vector<std::pair<int, int>>> &matrix, const std::string &filaname);
void saveTransition(
    const std::vector<std::unordered_map<std::vector<bool>, std::vector<std::pair<std::vector<bool>, int>>>> &data,
    const std::string &filename);

std::vector<bool> loadBoolVector(const std::string &filename);
std::vector<int> loadIntVector(const std::string &filename);
std::vector<std::vector<int>> loadMatrix(const std::string &filename);
std::vector<std::vector<long double>> readCSV(const std::string &filename);
std::vector<std::vector<std::pair<int, int>>> loadIntPairMatrix(const std::string &filename);


void truncateVector(std::vector<bool> &vector);

#endif // FILE_CONTROLLER_H