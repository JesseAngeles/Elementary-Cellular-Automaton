#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

std::vector<char> makeVectorWrittable(const std::vector<bool> &vector);

void saveBoolVector(const std::vector<bool> &vector, const std::string &filename);
void saveIntVector(const std::vector<int> &, const std::string &filename);
void saveIntMatrix(const std::vector<std::vector<int>> &, const std::string &filename);

std::vector<bool> loadBoolVector(const std::string &filename);
std::vector<int> loadIntVector(const std::string &filename);
std::vector<std::vector<int>> loadMatrix(const std::string &filename);


void truncateVector(std::vector<bool> &vector);

#endif // FILE_CONTROLLER_H