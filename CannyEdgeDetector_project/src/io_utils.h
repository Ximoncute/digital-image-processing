#pragma once
#include <vector>
#include <string>

// Đọc ảnh từ file CSV
std::vector<std::vector<int>> readCSV(const std::string& filename);

// Ghi ảnh ra file CSV
void writeCSV(const std::string& filename, const std::vector<std::vector<int>>& data);
