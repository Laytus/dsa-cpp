#include "algorithms/radix_sort.hpp"

#include "algorithms/counting_sort.hpp"

namespace dsa::algorithms {

void radix_sort(
    std::vector<int>& values,
    std::size_t n,
    std::size_t d
) {
    if (n > values.size()) {
        throw std::invalid_argument("n cannot be greater than the size of values");
    }

    int exponent = 1;

    for (std::size_t i = 0; i < d; ++i) {
        counting_sort_by_digit(values, n, exponent);
        exponent *= 10;
    }
}

}  // namespace dsa::algorithms
