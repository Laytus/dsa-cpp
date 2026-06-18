#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

int randomized_select(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r,
    std::size_t i
);

}  // namespace dsa::algorithms