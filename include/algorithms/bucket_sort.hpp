#pragma once

#include "data_structures/linked_list.hpp"
#include "algorithms/insertion_sort_array.hpp"

#include <vector>

namespace dsa::algorithms {

std::vector<double> bucketsort(
    std::vector<double>& values
);

std::vector<int> bucketsort(
    std::vector<int>& values
);

}  // namespace dsa::algorithms