#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

void quicksort(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
);

std::size_t partition(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
);

void randomized_quicksort(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
);

std::size_t randomized_partition(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
);

}  // namespace dsa::algorithms