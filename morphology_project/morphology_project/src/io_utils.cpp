#include "io_utils.h"         // Bao gồm file tiêu đề khai báo các hàm nhập/xuất
#include <fstream>            // Thư viện để thao tác với file
#include <sstream>            // Thư viện để xử lý chuỗi, tách chuỗi

// Hàm đọc dữ liệu từ file CSV và trả về dưới dạng ma trận 2 chiều (vector của vector)
std::vector<std::vector<int>> readCSV(const std::string& filename) {
    std::ifstream file(filename);           // Mở file để đọc
    std::vector<std::vector<int>> data;     // Dữ liệu đầu ra
    std::string line;                       // Biến lưu từng dòng đọc được từ file

    // Đọc từng dòng trong file
    while (std::getline(file, line)) {
        std::stringstream ss(line);         // Chuyển dòng thành stream để tách giá trị
        std::string val;                    // Biến lưu giá trị tạm thời
        std::vector<int> row;               // Một dòng (hàng) của ma trận

        // Tách các giá trị cách nhau bởi dấu phẩy ','
        while (std::getline(ss, val, ',')) {
            row.push_back(std::stoi(val));  // Chuyển chuỗi thành số nguyên và thêm vào hàng
        }

        data.push_back(row);                // Thêm hàng vào dữ liệu
    }

    return data;                            // Trả về ma trận 2 chiều
}

// Hàm ghi dữ liệu ma trận ra file CSV
void writeCSV(const std::string& filename, const std::vector<std::vector<int>>& data) {
    std::ofstream file(filename);           // Mở file để ghi

    // Duyệt từng hàng trong dữ liệu
    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            file << data[i][j];             // Ghi từng phần tử

            // Thêm dấu ',' giữa các phần tử, trừ phần tử cuối dòng
            if (j < data[i].size() - 1)
                file << ",";
        }
        file << "\n";                       // Xuống dòng sau mỗi hàng
    }
}

// Hàm thêm phần đệm (padding) vào ảnh
std::vector<std::vector<int>> padImage(const std::vector<std::vector<int>>& image, int padH, int padW) {
    int H = image.size();                   // Chiều cao của ảnh gốc
    int W = image[0].size();                // Chiều rộng của ảnh gốc

    // Tạo ảnh mới có kích thước lớn hơn với các giá trị ban đầu là 0
    std::vector<std::vector<int>> padded(H + 2 * padH, std::vector<int>(W + 2 * padW, 0));

    // Sao chép ảnh gốc vào giữa ảnh đã đệm
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            padded[i + padH][j + padW] = image[i][j];

    return padded;                          // Trả về ảnh đã thêm phần đệm
}
