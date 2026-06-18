#pragma once

#include <vector>

namespace dsa::algorithms {

template <typename T>
void insertion_sort(std::vector<T>& input) {
    for (std::size_t i = 1; i < input.size(); ++i) {
        const T key = input[i];

        std::size_t j = i;

        while(j > 0 && input[j - 1] > key) {
            input[j] = input[j - 1];
            --j;
        }

        input[j] = key;
    }
}

}  // namespace dsa::algorithms
