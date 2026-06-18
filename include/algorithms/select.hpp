#pragma once 

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

std::pair<std::size_t, std::size_t> partition_around_3way(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r,
    std::size_t pivot_index
);

int select(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r,
    std::size_t i
);

}  // namespace dsa::algorithms