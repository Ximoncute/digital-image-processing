#pragma once
#include <vector>
#include <string>

std::vector<std::vector<int>> readCSV(const std::string& filename);
void writeCSV(const std::string& filename, const std::vector<std::vector<int>>& data);
std::vector<std::vector<int>> padImage(const std::vector<std::vector<int>>& image, int padH, int padW);
