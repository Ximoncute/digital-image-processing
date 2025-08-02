#include "morphology.h"
#include "io_utils.h"
#include <algorithm>

// Hàm erosion (co ảnh lại)
// Với mỗi điểm ảnh, lấy giá trị nhỏ nhất trong vùng phủ bởi phần tử cấu trúc (structuring element)
std::vector<std::vector<int>> erosion(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& se) {
    int H = image.size(), W = image[0].size();        // Kích thước ảnh gốc
    int kH = se.size(), kW = se[0].size();            // Kích thước phần tử cấu trúc
    int padH = kH / 2, padW = kW / 2;                 // Padding: thêm viền để xử lý ảnh biên

    auto padded = padImage(image, padH, padW);        // Thêm viền (padding) cho ảnh
    std::vector<std::vector<int>> result(H, std::vector<int>(W, 0));  // Ảnh kết quả

    // Duyệt qua từng điểm ảnh của ảnh gốc (đã được pad)
    for (int i = padH; i < padH + H; ++i) {
        for (int j = padW; j < padW + W; ++j) {
            int minVal = 255; // Giá trị nhỏ nhất khởi tạo

            // Duyệt qua phần tử cấu trúc
            for (int m = 0; m < kH; ++m) {
                for (int n = 0; n < kW; ++n) {
                    // Nếu phần tử SE tại (m,n) là 1 thì mới tính
                    if (se[m][n] == 1) {
                        int val = padded[i - padH + m][j - padW + n];  // Giá trị điểm ảnh tương ứng
                        minVal = std::min(minVal, val);               // Tìm giá trị nhỏ nhất
                    }
                }
            }

            result[i - padH][j - padW] = minVal;  // Gán kết quả vào ảnh mới
        }
    }

    return result;
}

// Hàm dilation (giãn ảnh)
// Với mỗi điểm ảnh, lấy giá trị lớn nhất trong vùng phủ bởi phần tử cấu trúc
std::vector<std::vector<int>> dilation(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& se) {
    int H = image.size(), W = image[0].size();
    int kH = se.size(), kW = se[0].size();
    int padH = kH / 2, padW = kW / 2;

    auto padded = padImage(image, padH, padW);
    std::vector<std::vector<int>> result(H, std::vector<int>(W, 0));

    for (int i = padH; i < padH + H; ++i) {
        for (int j = padW; j < padW + W; ++j) {
            int maxVal = 0;  // Giá trị lớn nhất khởi tạo

            for (int m = 0; m < kH; ++m) {
                for (int n = 0; n < kW; ++n) {
                    if (se[m][n] == 1) {
                        int val = padded[i - padH + m][j - padW + n];
                        maxVal = std::max(maxVal, val);  // Tìm giá trị lớn nhất
                    }
                }
            }

            result[i - padH][j - padW] = maxVal;
        }
    }

    return result;
}

// Hàm opening = erosion trước, dilation sau
// Dùng để loại bỏ nhiễu nhỏ (hạt sáng nhỏ) mà không làm thay đổi hình dạng chính
std::vector<std::vector<int>> opening(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& se) {
    return dilation(erosion(image, se), se);
}

// Hàm closing = dilation trước, erosion sau
// Dùng để lấp đầy lỗ nhỏ (hạt tối nhỏ) trong ảnh mà không thay đổi hình dạng chính
std::vector<std::vector<int>> closing(const std::vector<std::vector<int>>& image, const std::vector<std::vector<int>>& se) {
    return erosion(dilation(image, se), se);
}
