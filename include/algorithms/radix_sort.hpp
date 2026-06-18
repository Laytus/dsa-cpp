#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

void radix_sort(
    std::vector<int>& values,
    std::size_t n,
    std::size_t d
);

}  // namespace dsa::algorithms