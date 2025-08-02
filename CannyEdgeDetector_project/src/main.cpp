#include <iostream>
#include "io_utils.h"
#include "canny.h"

int main() {
    // Đọc ảnh đầu vào từ file CSV trong thư mục "data"
    std::vector<std::vector<int>> input = readCSV("../data/input.csv");

    // Làm mờ ảnh bằng Gaussian filter để giảm nhiễu
    auto blurred = gaussianBlur(input);

    // Tính độ lớn và hướng gradient sử dụng toán tử Sobel
    std::vector<std::vector<double>> magnitude, direction;
    computeGradient(blurred, magnitude, direction);

    // Thực hiện ức chế cực đại (non-maximum suppression)
    auto suppressed = nonMaximumSuppression(magnitude, direction);

    // Áp dụng ngưỡng kép để phân loại điểm mạnh/yếu
    auto thresholded = doubleThreshold(suppressed, 50, 100);

    // Theo dõi biên dựa trên liên kết các điểm mạnh/yếu
    auto edges = hysteresis(thresholded);

    // Ghi ảnh đầu ra ra file CSV trong thư mục "data"
    writeCSV("../data/output.csv", edges);

    std::cout <<  "Canny Edge Detection complete. Output saved to: data/output.csv" << std::endl;
    return 0;
}
