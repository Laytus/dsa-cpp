#include "algorithms/randomized_select.hpp"

#include "algorithms/quick_sort.hpp"

namespace dsa::algorithms {

int randomized_select(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r,
    std::size_t i
) {
    if (p + 1 == r) {
        return values[p];
    }

    const std::size_t q = randomized_partition(values, p, r);
    const std::size_t k = q - p;

    if (i == k) {
        return values[q];
    } else if (i < k) {
        return randomized_select(values, p, q, i);
    } else {
        return randomized_select(values, q + 1, r, i - k - 1);
    }
}

}  // namespace dsa::algorithms