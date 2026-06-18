#include "algorithms/select.hpp"

#include "algorithms/merge_sort.hpp"

#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>
#include <vector>

namespace dsa::algorithms {

namespace {

std::size_t choose_pivot_index(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
) {
    const std::size_t n = r - p;

    if (n <= 5) {
        merge_sort(values, p, r);
        return p + n / 2;
    }

    std::size_t median_count = 0;

    for (std::size_t g = p; g < r; g += 5) {
        const std::size_t g_end = std::min(g + 5, r);

        merge_sort(values, g, g_end);

        const std::size_t g_size = g_end - g;
        const std::size_t median_index = g + g_size / 2;

        std::swap(values[p + median_count], values[median_index]);
        ++median_count;
    }

    const std::size_t order = median_count / 2;

    const int pivot_value = select(values, p, p + median_count, order);

    for (std::size_t j = p; j < r; ++j) {
        if (values[j] == pivot_value) {
            return j;
        }
    }

    throw std::logic_error("Pivot value not found");
}

}  // namespace

std::pair<std::size_t, std::size_t> partition_around_3way(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r,
    std::size_t pivot_index
) {
    const int x = values[pivot_index]; // the pivot
    
    // std::swap(values[pivot_index], values[r - 1]);

    std::size_t lt = p;
    std::size_t i = p;
    std::size_t gt = r;

    while (i < gt) {
        if (values[i] < x) {
            std::swap(values[lt], values[i]);
            ++lt;
            ++i;
        } else if (values[i] > x) {
            --gt;
            std::swap(values[i], values[gt]);
        } else {
            ++i;
        }
    }

    return {lt, gt};
}

int select(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r,
    std::size_t i
) {
    if (p >= r) {
        throw std::invalid_argument("Range must contain at least one element");
    }

    const std::size_t n = r - p;

    if (i >= n) {
        throw std::out_of_range("Order statistic index is out of range");
    }

    while (true) {
        const std::size_t size = r - p;

        if (size <= 5) {
            merge_sort(values, p, r);
            return values[p + i];
        }

        const std::size_t pivot_index = choose_pivot_index(values, p, r);
        const auto [lt, gt] = partition_around_3way(values, p, r, pivot_index);

        const std::size_t left_size = lt - p;
        const std::size_t equal_size = gt - lt;

        if (i < left_size) {
            r = lt;
        } else if (i < left_size + equal_size) {
            return values[lt];
        } else {
            i -= left_size + equal_size;
            p = gt;
        }
    }
}

}  // namespace dsa::algorithms