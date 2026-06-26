#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

template <typename T, typename Compare>
void generic_merge(
    std::vector<T>& values,
    std::size_t p,
    std::size_t q,
    std::size_t r,
    Compare compare
) {
    const std::size_t n1 = q - p;
    const std::size_t n2 = r - q;
    
    std::vector<T> L(n1);
    std::vector<T> R(n2);
    
    for (std::size_t i = 0; i < n1; ++i) {
        L[i] = values[p + i];
    }
    
    for (std::size_t j = 0; j < n2; ++j) {
        R[j] = values[q + j];
    }

    std::size_t i = 0;
    std::size_t j = 0;
    std::size_t k = p;

    while (i < L.size() && j < R.size()) {
        if (!compare(R[j], L[i])) {
            values[k] = L[i];
            ++i;
        } else {
            values[k] = R[j];
            ++j;
        }

        ++k;
    }

    while (i < L.size()) {
        values[k] = L[i];
        ++i;
        ++k;
    }

    while (j < R.size()) {
        values[k] = R[j];
        ++j;
        ++k;
    }
}

template <typename T, typename Compare>
void generic_merge_sort(
    std::vector<T>& values,
    std::size_t p,
    std::size_t r,
    Compare compare
) {
    if (r - p > 1) {
        const std::size_t q = p + (r - p) / 2;

        generic_merge_sort(values, p, q, compare);
        generic_merge_sort(values, q, r, compare);
        generic_merge(values, p, q, r, compare);
    }
}

}  // namespace dsa::algorithms