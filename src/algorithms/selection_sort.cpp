#include "algorithms/selection_sort.hpp"

#include <cstddef>

namespace dsa::algorithms {

void selection_sort(std::vector<int>& input) {
    if (input.size() < 2) {
        return;
    }

    for (std::size_t i = 0; i + 1 < input.size(); ++i) {
        const int key = input[i];
        std::size_t min_index = i;
        // int min_value = key;
        
        for (std::size_t j = i + 1; j < input.size(); ++j) {
            // if (input[j] < min_value) {
            if (input[j] < input[min_index]) {
                min_index = j;
                // min_value = input[j];
            }
        }

        if (min_index != i) {
            // input[i] = min_value;
            input[i] = input[min_index];
            input[min_index] = key;
        }
    }
}

}  // namespace dsa::algorithms