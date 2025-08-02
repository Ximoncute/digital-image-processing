#include "canny.h"
#include <cmath>
#include <algorithm>

// Hàm làm mờ ảnh bằng bộ lọc Gaussian 3x3
std::vector<std::vector<int>> gaussianBlur(const std::vector<std::vector<int>>& image) {
    std::vector<std::vector<int>> result = image;
    int kernel[3][3] = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    int rows = image.size();
    int cols = image[0].size();

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            int sum = 0;
            for (int ki = -1; ki <= 1; ++ki)
                for (int kj = -1; kj <= 1; ++kj)
                    sum += image[i + ki][j + kj] * kernel[ki + 1][kj + 1];
            result[i][j] = sum / 16;
        }
    }
    return result;
}

// Hàm tính gradient magnitude và direction sử dụng Sobel
void computeGradient(const std::vector<std::vector<int>>& img,
                     std::vector<std::vector<double>>& magnitude,
                     std::vector<std::vector<double>>& direction) {
    int rows = img.size();
    int cols = img[0].size();

    magnitude.assign(rows, std::vector<double>(cols, 0));
    direction.assign(rows, std::vector<double>(cols, 0));

    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            int sx = 0, sy = 0;
            for (int ki = -1; ki <= 1; ++ki)
                for (int kj = -1; kj <= 1; ++kj) {
                    sx += img[i + ki][j + kj] * Gx[ki + 1][kj + 1];
                    sy += img[i + ki][j + kj] * Gy[ki + 1][kj + 1];
                }
            magnitude[i][j] = std::sqrt(sx * sx + sy * sy);
            direction[i][j] = std::atan2(sy, sx) * 180.0 / M_PI;
            if (direction[i][j] < 0) direction[i][j] += 180;
        }
    }
}

// Ức chế cực đại (giữ điểm mạnh nhất theo hướng gradient)
std::vector<std::vector<int>> nonMaximumSuppression(
    const std::vector<std::vector<double>>& mag,
    const std::vector<std::vector<double>>& dir) {
    
    int rows = mag.size();
    int cols = mag[0].size();
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));

    for (int i = 1; i < rows - 1; ++i) {
        for (int j = 1; j < cols - 1; ++j) {
            double angle = dir[i][j];
            double m = mag[i][j];
            double m1 = 0, m2 = 0;

            // Phân vùng theo hướng
            if ((angle >= 0 && angle < 22.5) || (angle >= 157.5 && angle <= 180)) {
                m1 = mag[i][j - 1];
                m2 = mag[i][j + 1];
            } else if (angle >= 22.5 && angle < 67.5) {
                m1 = mag[i - 1][j + 1];
                m2 = mag[i + 1][j - 1];
            } else if (angle >= 67.5 && angle < 112.5) {
                m1 = mag[i - 1][j];
                m2 = mag[i + 1][j];
            } else if (angle >= 112.5 && angle < 157.5) {
                m1 = mag[i - 1][j - 1];
                m2 = mag[i + 1][j + 1];
            }

            if (m >= m1 && m >= m2)
                result[i][j] = static_cast<int>(m);
            else
                result[i][j] = 0;
        }
    }
    return result;
}

// Ngưỡng kép: phân loại thành strong/weak/none
std::vector<std::vector<int>> doubleThreshold(
    const std::vector<std::vector<int>>& img, int low, int high) {

    int rows = img.size();
    int cols = img[0].size();
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j) {
            int val = img[i][j];
            if (val >= high)
                result[i][j] = 255;  // strong edge
            else if (val >= low)
                result[i][j] = 100;  // weak edge
            else
                result[i][j] = 0;
        }

    return result;
}

// Theo dõi biên dựa trên điểm mạnh và kết nối điểm yếu
std::vector<std::vector<int>> hysteresis(const std::vector<std::vector<int>>& img) {
    int rows = img.size();
    int cols = img[0].size();
    std::vector<std::vector<int>> result = img;

    for (int i = 1; i < rows - 1; ++i)
        for (int j = 1; j < cols - 1; ++j)
            if (result[i][j] == 100) { // weak edge
                bool connected = false;
                for (int di = -1; di <= 1 && !connected; ++di)
                    for (int dj = -1; dj <= 1 && !connected; ++dj)
                        if (result[i + di][j + dj] == 255)
                            connected = true;
                result[i][j] = connected ? 255 : 0;
            }

    return result;
}
