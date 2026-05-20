#include "algorithms/insertion_sort_inv.hpp"

#include <cstddef>

namespace dsa::algorithms {

void insertion_sort_inv(std::vector<int>& input) {
    for (std::size_t i = 1; i < input.size(); ++i) {
        const int key = input[i];

        std::size_t j = i;

        while(j > 0 && input[j - 1] < key) {
            input[j] = input[j - 1];
            --j;
        }

        input[j] = key;
    }
}

}  // namespace dsa::algorithms
