#include <cstddef>
#include <vector>
#include <iostream>

namespace dsa::utils {

template <typename T>
void print_vector(const std::vector<T>& vector) {
    std::cout << "[ ";

    for (std::size_t i = 0; i < vector.size(); ++i) {
        std::cout << vector[i];
        if (i + 1 < vector.size()) {
            std::cout << ", ";
        }
    }

    std::cout << " ]\n";
}

template <typename T>
void print_matrix(const std::vector<std::vector<T>>& matrix) {
    std::cout << "[\n";

    for (const auto& row : matrix) {
        std::cout << " ";
        print_vector(row);
    }

    std::cout << "]\n";
}

}  // namespace dsa::utils