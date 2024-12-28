#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <map>
#include <vector>
#include <algorithm>

std::vector<bool> getBinary(int &number, const int &vector_size);

std::map<int, std::vector<int>> matrixToMap(std::vector<std::vector<int>> &matrix);
std::vector<std::vector<int>> mapToMatrix(std::map<int, std::vector<int>> &mapped);


#endif // FUNCTIONS_H