#include "algorithms/find_maximum_subarray.hpp"
#include "algorithms/find_maximum_subarray_brute_force.hpp"

#include <vector>
#include <cstddef>
#include <random>
#include <chrono>
#include <iostream>

namespace {

std::vector<int> generate_random_vector(std::size_t size) {
    std::mt19937 generator(42);
    std::uniform_int_distribution<int> distribution(-100, 100);

    std::vector<int> values(size);

    for (std::size_t i = 0; i < size; ++i) {
        values[i] = distribution(generator);
    }

    return values;
}

template <typename Function>
long long measure_microseconds(Function function, int repetitions) {
    const auto start = std::chrono::steady_clock::now();

    volatile int sink = 0;

    for (int i = 0; i < repetitions; ++i) {
        auto [low, high, sum] = function();
        sink += sum;
    }

    const auto end = std::chrono::steady_clock::now();

    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

}  // namespace

int main() {
    constexpr std::size_t max_n = 500;
    constexpr int repetitions = 1000;

    bool found_crossover = false;
    std::size_t n0 = 0;

    std::cout << "n,brute_force_us,recursive_us\n";

    for (std::size_t n = 1; n <= max_n; ++n) {
        const std::vector<int> values = generate_random_vector(n);

        const auto brute_time = measure_microseconds(
            [&values]() {
                return dsa::algorithms::find_maximum_subarray_brute_force(
                    values,
                    0,
                    values.size()
                );
            },
            repetitions
        );

        const auto recursive_time = measure_microseconds(
            [&values]() {
                return dsa::algorithms::find_maximum_subarray(
                    values,
                    0,
                    values.size()
                );
            },
            repetitions
        );

        std::cout << n << "," << brute_time << "," << recursive_time << "\n";

        if (!found_crossover && recursive_time < brute_time) {
            found_crossover = true;
            n0 = n;
        }
    }

    if (found_crossover) {
        std::cerr << "Crossover point n0 = " << n0 << "\n";
    } else {
        std::cerr << "No crossover found up to max_n.\n";
    }

    return 0;
}