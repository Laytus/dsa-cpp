#include "algorithms/counting_sort.hpp"

namespace {

int digit_at(int value, int exponent) {
    return (value / exponent) % 10;
}

}  // namespace

namespace dsa::algorithms {

std::vector<int> counting_sort(
    std::vector<int>& values,
    std::size_t n,
    std::size_t k
) {
    if (n == 0) {
        return {};
    }

    std::vector<int> counts(k + 1, 0);
    std::vector<int> output(n, 0);

    for (std::size_t j = 0; j < n; ++j) {
        ++counts[static_cast<std::size_t>(values[j])];
    }

    for (std::size_t i = 1; i < k + 1; ++i) {
        counts[i] += counts[i - 1];
    }

    for (std::size_t j = n; j > 0; --j) {
        const std::size_t index = j - 1;

        output[static_cast<std::size_t>(counts[static_cast<std::size_t>(values[index])] - 1)] = values[index];
        --counts[static_cast<std::size_t>(values[index])];
    }

    return output;
}

void counting_sort_by_digit(
    std::vector<int>& values,
    std::size_t n,
    int exponent
) {
    constexpr std::size_t base = 10;

    std::vector<int> counts(base, 0);
    std::vector<int> output(n, 0);

    for (std::size_t j = 0; j < n; ++j) {
        if (values[j] < 0) {
            throw std::invalid_argument("nonnegative integers are not supported");
        }

        const int digit = digit_at(values[j], exponent);
        ++counts[static_cast<std::size_t>(digit)];
    }

    for (std::size_t i = 1; i < base; ++i) {
        counts[i] += counts[i - 1];
    }

    for (std::size_t j = n; j > 0; --j) {
        const std::size_t index = j - 1;
        const int digit = digit_at(values[index], exponent);
        const std::size_t digit_index = static_cast<std::size_t>(digit);

        output[static_cast<std::size_t>(counts[digit_index] - 1)] = values[index];
        --counts[digit_index];
    }

    for (std::size_t i = 0; i < n; ++i) {
        values[i] = output[i];
    }
}

}  // namespace dsa::algorithms