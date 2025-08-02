#pragma once
#include <vector>

std::vector<std::vector<int>> erosion(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& se);
std::vector<std::vector<int>> dilation(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& se);
std::vector<std::vector<int>> opening(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& se);
std::vector<std::vector<int>> closing(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& se);
