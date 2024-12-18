#ifndef FILE_CONTROLLER_H
#define FILE_CONTROLLER_H

#include <string>
#include <vector>
#include <fstream>

std::vector<char> makeVectorWrittable(const std::vector<bool> &vector);

void saveVector(const std::vector<char> &vector, const std::string &filename);

std::vector<bool> loadVector(const std::string &filename);

void truncateVector(std::vector<bool> &vector);

#endif // FILE_CONTROLLER_H