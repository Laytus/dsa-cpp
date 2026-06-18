#include "algorithms/quick_sort.hpp"

#include <stdexcept>
#include <algorithm>
#include <random>

namespace {

std::size_t random_between(std::size_t low, std::size_t high) {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());

    std::uniform_int_distribution<std::size_t> dist(low, high);

    return dist(gen);
}

}  // namespace

namespace dsa::algorithms {

void quicksort(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
) {
    if (r > p + 1) {
        std::size_t q = partition(values, p, r);
        quicksort(values, p, q);
        quicksort(values, q + 1, r);
    }
}

std::size_t partition(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
) {
    int x = values[r - 1]; // the pivot
    std::size_t i = p;

    for (std::size_t j = p; j < r - 1; ++j) {
        if (values[j] <= x) {
            std::swap(values[i], values[j]);
            ++i;
        }
    }
    std::swap(values[i], values[r - 1]);
    return i;
}

std::size_t randomized_partition(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
) {
    std::size_t i = random_between(p, r - 1);
    std::swap(values[i], values[r - 1]);

    return partition(values, p, r);
}

void randomized_quicksort(
    std::vector<int>& values,
    std::size_t p,
    std::size_t r
) {
    if (r > p + 1) {
        std::size_t q = randomized_partition(values, p, r);
        randomized_quicksort(values, p, q);
        randomized_quicksort(values, q + 1, r);
    }
}

}  // namespace dsa::algorithms