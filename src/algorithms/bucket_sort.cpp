#include "algorithms/bucket_sort.hpp"

// #include "data_structures/linked_list.hpp"
#include "algorithms/insertion_sort.hpp"

#include <vector>
#include <stdexcept>

namespace dsa::algorithms {

namespace {

template <typename T>
std::vector<T> bucketsort_impl(
    std::vector<T>& values,
    T lower_bound,
    T upper_bound,
    const char* error_message
) {
    const std::size_t n = values.size();
    
    if (n == 0) {
        return {};
    }

    // std::vector<dsa::data_structures::LinkedList> buckets(n);
    std::vector<std::vector<T>> buckets(n);

    for (std::size_t i = 0; i < n; ++i) {
        const T value = values[i];

        if (value < lower_bound || value >= upper_bound) {
            throw std::invalid_argument(error_message);
        }

        const auto normalized =
            static_cast<long double>(value - lower_bound) /
            static_cast<long double>(upper_bound - lower_bound);

        const long double scaled_index = static_cast<long double>(n) * normalized;
        const std::size_t index = static_cast<std::size_t>(scaled_index);

        buckets[index].push_back(value);
    }

    for (auto& bucket : buckets) {
        insertion_sort(bucket);
    }

    std::vector<T> output;
    output.reserve(n);

    for (const auto& bucket : buckets) {
        for (T value : bucket) {
            output.push_back(value);
        }
    }

    return output;
}

}  // namespace

std::vector<double> bucketsort(
    std::vector<double>& values
) {
    return bucketsort_impl(
        values,
        0.0,
        1.0,
        "Bucket Sort expects values in [0, 1)"
    );
}

std::vector<int> bucketsort(
    std::vector<int>& values
) {
    return bucketsort_impl(
        values,
        0,
        100,
        "Bucket Sort expects values in [0, 100)"
    );
}

}  // namespace dsa::algorithms