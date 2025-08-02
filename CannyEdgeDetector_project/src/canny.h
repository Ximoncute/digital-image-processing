
#pragma once
#include <vector>

// Làm mờ Gaussian
std::vector<std::vector<int>> gaussianBlur(const std::vector<std::vector<int>>& image);

// Tính gradient độ lớn và hướng
void computeGradient(const std::vector<std::vector<int>>& img,
                     std::vector<std::vector<double>>& magnitude,
                     std::vector<std::vector<double>>& direction);

// Ức chế cực đại
std::vector<std::vector<int>> nonMaximumSuppression(
    const std::vector<std::vector<double>>& magnitude,
    const std::vector<std::vector<double>>& direction);

// Ngưỡng kép
std::vector<std::vector<int>> doubleThreshold(const std::vector<std::vector<int>>& img, int low, int high);

// Hysteresis - theo dõi biên
std::vector<std::vector<int>> hysteresis(const std::vector<std::vector<int>>& img);
