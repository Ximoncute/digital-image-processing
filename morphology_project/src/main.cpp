#include <iostream>
#include "io_utils.h"
#include "morphology.h"

int main() {
    auto image = readCSV("data/input_image.csv");
    auto se = readCSV("data/struct_element.csv");

    writeCSV("data/erosion.csv", erosion(image, se));
    writeCSV("data/dilation.csv", dilation(image, se));
    writeCSV("data/opening.csv", opening(image, se));
    writeCSV("data/closing.csv", closing(image, se));

    std::cout << "Hoàn tất xử lý hình thái học.\n";
    return 0;
}
