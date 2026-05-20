#pragma once

#include <array>
#include <cstddef>

namespace dsa::algorithms {

template <typename T, std::size_t N>
void insertion_sort(std::array<T, N>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        const T key = values[i];

        std::size_t j = i;

        while (j > 0 && values[j - 1] > key) {
            values[j] = values[j - 1];
            --j;
        }

        values[j] = key;
    }
}

}  // namespace dsa::algorithms