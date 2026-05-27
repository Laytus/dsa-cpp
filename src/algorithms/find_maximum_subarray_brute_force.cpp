#include "algorithms/find_maximum_subarray_brute_force.hpp"

#include <limits>

namespace dsa::algorithms {

std::tuple<std::size_t, std::size_t, int> find_maximum_subarray_brute_force(
    const std::vector<int>& inputs,
    std::size_t low,
    std::size_t high
) {
    int max_sum = std::numeric_limits<int>::min();
    std::size_t best_low = low;
    std::size_t best_high = low + 1;

    for (std::size_t i = low; i < high; ++i) {
        int sum = 0;

        for (std::size_t j = i; j < high; ++j) {
            sum += inputs[j];

            if (sum > max_sum) {
                max_sum = sum;
                best_low = i;
                best_high = j + 1;
            }
        }
    }

    return {best_low, best_high, max_sum};
}

}  // namespace dsa::algorithms