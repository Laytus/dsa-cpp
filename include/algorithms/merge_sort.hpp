#pragma once

#include <vector>
#include <cstddef>

namespace dsa::algorithms {

void merge(
    std::vector<int>& values,
    std::size_t p,
    std::size_t q,
    std::size_t r
);

void merge_sort(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
);

}  // namespace dsa::algorithms