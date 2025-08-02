#include "io_utils.h"
#include <fstream>
#include <sstream>

// Hàm đọc file CSV
std::vector<std::vector<int>> readCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::vector<int>> data;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<int> row;

        while (std::getline(ss, value, ',')) {
            row.push_back(std::stoi(value));
        }
        data.push_back(row);
    }
    return data;
}

// Hàm ghi file CSV
void writeCSV(const std::string& filename, const std::vector<std::vector<int>>& data) {
    std::ofstream file(filename);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i != row.size() - 1)
                file << ",";
        }
        file << "\n";
    }
}
