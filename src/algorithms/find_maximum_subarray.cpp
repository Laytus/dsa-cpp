#include "algorithms/find_maximum_subarray.hpp"

// #include "utils/print_utils.hpp"

#include <limits>
// #include <print>

namespace dsa::algorithms {

std::tuple<std::size_t, std::size_t, int> find_max_crossing_subarray(
    const std::vector<int>& inputs,
    std::size_t low,
    std::size_t mid,
    std::size_t high
) {
    int left_sum = std::numeric_limits<int>::min();
    int sum = 0;
    std::size_t max_left = mid - 1;

    for (std::size_t i = mid; i > low; --i) {
        const std::size_t index = i - 1;
        sum += inputs[index];

        if (sum > left_sum) {
            left_sum = sum;
            max_left = index;
        }
    }
    
    int right_sum = std::numeric_limits<int>::min();
    sum = 0;
    std::size_t max_right = mid;

    for (std::size_t j = mid; j < high; ++j) {
        sum += inputs[j];

        if (sum > right_sum) {
            right_sum = sum;
            max_right = j;
        }
    }

    return {max_left, max_right + 1, left_sum + right_sum};
}

std::tuple<std::size_t, std::size_t, int> find_maximum_subarray(
    const std::vector<int>& inputs,
    std::size_t low,
    std::size_t high
) {
    if (low + 1 == high) {
        return {low, high, inputs[low]};
    } else {
        // std::println("initial: low = {}", low);
        // std::println("initial: high = {}", high);
        // std::println("initial: inputs:");
        // dsa::utils::print_vector(inputs);

        const std::size_t mid = low + (high - low) / 2;

        // std::println("initial: mid = {}", mid);
        // std::println("\n");

        auto [left_low, left_high, left_sum] = find_maximum_subarray(inputs, low, mid);
        auto [right_low, right_high, right_sum] = find_maximum_subarray(inputs, mid, high);
        auto [cross_low, cross_high, cross_sum] = find_max_crossing_subarray(inputs, low, mid, high);

        if (left_sum >= right_sum && left_sum >= cross_sum) {
            return {left_low, left_high, left_sum};
        } else if (right_sum >= left_sum && right_sum >= cross_sum) {
            return {right_low, right_high, right_sum};
        } else {
            return {cross_low, cross_high, cross_sum};
        }
    }
}

}  // namespace dsa::algorithms