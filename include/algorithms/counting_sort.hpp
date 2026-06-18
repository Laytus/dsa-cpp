#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

std::vector<int> counting_sort(
    std::vector<int>& values,
    std::size_t n,
    std::size_t k
);

void counting_sort_by_digit(
    std::vector<int>& values,
    std::size_t n,
    int exponent
);

}  // namespace dsa::algorithms