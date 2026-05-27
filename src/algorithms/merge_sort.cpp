#include "algorithms/merge_sort.hpp"

// #include "utils/print_utils.hpp"

#include <vector>
#include <limits>

// #include <print>

namespace dsa::algorithms {

void merge(
    std::vector<int>& values,
    std::size_t p,
    std::size_t q,
    std::size_t r
) {
    const std::size_t n1 = q - p;
    const std::size_t n2 = r - q;

    // std::println("initial: values");
    // dsa::utils::print_vector(values);
    // std::println("initial: p = {}", p);
    // std::println("initial: q = {}", q);
    // std::println("initial: r = {}", r);
    
    // std::println("initial: n1 = {}", n1);
    // std::println("initial: n2 = {}", n2);
    
    std::vector<int> L(n1 + 1);
    std::vector<int> R(n2 + 1);
    
    for (std::size_t i = 0; i < n1; ++i) {
        L[i] = values[p + i];
    }
    
    for (std::size_t j = 0; j < n2; ++j) {
        R[j] = values[q + j];
    }

    int imax = std::numeric_limits<int>::max();
    L[n1] = imax;
    R[n2] = imax;

    // std::println("L:");
    // dsa::utils::print_vector(L);
    // std::println("R:");
    // dsa::utils::print_vector(R);

    std::size_t i = 0;
    std::size_t j = 0;

    for (std::size_t k = p; k < r; ++k) {
        if (L[i] <= R[j]) {
            values[k] = L[i];
            ++i;
        } else {
            values[k] = R[j];
            ++j;
        }
    }
}

void merge_sort(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
) {
    if (r - p > 1) {
        std::size_t q = p + (r - p) / 2;

        // std::println("base: p = {}", p);
        // std::println("base: r = {}", r);
        // std::println("base: q = {}", q);

        merge_sort(values, p, q);
        merge_sort(values, q, r);
        merge(values, p, q, r);
    }
}

}  // namespace dsa::algorithms