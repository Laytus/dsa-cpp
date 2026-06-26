#include "algorithms/activity_selector.hpp"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {

using dsa::algorithms::Activity;
using dsa::algorithms::dynamic_activity_selector;
using dsa::algorithms::greedy_activity_selector;
using dsa::algorithms::recursive_activity_selector;

// Adjust these two functions if your Activity fields have different names.
int activity_start(const Activity& activity) {
    return activity.start;
}

int activity_finish(const Activity& activity) {
    return activity.finish;
}

struct TestCase {
    std::string name;
    std::vector<int> s;
    std::vector<int> f;
};

struct BenchmarkResult {
    std::string name;
    std::size_t selected_count;
    double average_us;
    std::string auxiliary_space;
};

std::vector<int> with_recursive_padding(const std::vector<int>& values) {
    std::vector<int> padded;
    padded.reserve(values.size() + 1);

    padded.push_back(0);
    padded.insert(padded.end(), values.begin(), values.end());

    return padded;
}

bool is_sorted_by_finish_time(const std::vector<int>& f) {
    return std::is_sorted(f.begin(), f.end());
}

bool is_compatible_solution(const std::vector<Activity>& activities) {
    for (std::size_t i = 1; i < activities.size(); ++i) {
        if (activity_start(activities[i]) < activity_finish(activities[i - 1])) {
            return false;
        }
    }

    return true;
}

void print_activities(const std::string& label, const std::vector<Activity>& activities) {
    std::cout << label << " (" << activities.size() << "): ";

    if (activities.empty()) {
        std::cout << "[]\n";
        return;
    }

    std::cout << "[ ";

    for (const Activity& activity : activities) {
        std::cout << "("
                  << activity_start(activity)
                  << ", "
                  << activity_finish(activity)
                  << ") ";
    }

    std::cout << "]\n";
}

std::string format_bytes(std::size_t bytes) {
    constexpr double kib = 1024.0;
    constexpr double mib = 1024.0 * 1024.0;

    std::ostringstream output;
    output << std::fixed << std::setprecision(2);

    if (bytes >= static_cast<std::size_t>(mib)) {
        output << static_cast<double>(bytes) / mib << " MiB";
    } else if (bytes >= static_cast<std::size_t>(kib)) {
        output << static_cast<double>(bytes) / kib << " KiB";
    } else {
        output << bytes << " B";
    }

    return output.str();
}

std::string estimated_recursive_auxiliary_space(std::size_t n) {
    const std::size_t padded_vectors_bytes = 2 * (n + 1) * sizeof(int);
    return "O(n) stack + " + format_bytes(padded_vectors_bytes) + " padding";
}

std::string estimated_greedy_auxiliary_space() {
    return "O(1) excluding output";
}

std::string estimated_dynamic_auxiliary_space(std::size_t n) {
    const std::size_t table_entries = (n + 2) * (n + 2);
    const std::size_t tables_bytes = 2 * table_entries * sizeof(std::size_t);
    const std::size_t padded_vectors_bytes = 2 * (n + 2) * sizeof(int);

    return "O(n^2), approx " + format_bytes(tables_bytes + padded_vectors_bytes);
}

template <typename Func>
BenchmarkResult benchmark_selector(
    const std::string& name,
    const std::string& auxiliary_space,
    std::size_t iterations,
    Func selector
) {
    using Clock = std::chrono::steady_clock;

    std::size_t checksum = 0;
    std::vector<Activity> last_result;

    const auto start = Clock::now();

    for (std::size_t i = 0; i < iterations; ++i) {
        last_result = selector();
        checksum += last_result.size();
    }

    const auto end = Clock::now();
    const auto elapsed_us = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // Prevent the benchmark loop from being trivially optimized away.
    if (checksum == static_cast<std::size_t>(-1)) {
        std::cout << "Impossible checksum: " << checksum << '\n';
    }

    return BenchmarkResult{
        name,
        last_result.size(),
        static_cast<double>(elapsed_us) / static_cast<double>(iterations),
        auxiliary_space
    };
}

void print_benchmark_result(const BenchmarkResult& result) {
    std::cout << std::left << std::setw(12) << result.name
              << " selected=" << std::setw(4) << result.selected_count
              << " avg_time=" << std::setw(12) << std::fixed << std::setprecision(2)
              << result.average_us << " us"
              << " space=" << result.auxiliary_space
              << '\n';
}

void run_test_case(const TestCase& test_case) {
    std::cout << "============================================================\n";
    std::cout << test_case.name << '\n';
    std::cout << "============================================================\n";

    if (test_case.s.size() != test_case.f.size()) {
        std::cout << "Invalid test case: s and f have different sizes.\n\n";
        return;
    }

    if (!is_sorted_by_finish_time(test_case.f)) {
        std::cout << "Warning: activities are not sorted by finish time.\n";
        std::cout << "The greedy and recursive CLRS algorithms assume sorted finish times.\n\n";
    }

    const std::vector<int> padded_s = with_recursive_padding(test_case.s);
    const std::vector<int> padded_f = with_recursive_padding(test_case.f);

    const std::vector<Activity> recursive_result =
        recursive_activity_selector(padded_s, padded_f, 0);

    const std::vector<Activity> greedy_result =
        greedy_activity_selector(test_case.s, test_case.f);

    const std::vector<Activity> dynamic_result =
        dynamic_activity_selector(test_case.s, test_case.f);

    print_activities("Recursive", recursive_result);
    print_activities("Greedy   ", greedy_result);
    print_activities("Dynamic  ", dynamic_result);

    const bool recursive_valid = is_compatible_solution(recursive_result);
    const bool greedy_valid = is_compatible_solution(greedy_result);
    const bool dynamic_valid = is_compatible_solution(dynamic_result);

    std::cout << '\n';
    std::cout << "Validity:\n";
    std::cout << "  Recursive: " << (recursive_valid ? "OK" : "INVALID") << '\n';
    std::cout << "  Greedy:    " << (greedy_valid ? "OK" : "INVALID") << '\n';
    std::cout << "  Dynamic:   " << (dynamic_valid ? "OK" : "INVALID") << '\n';

    const bool same_size =
        recursive_result.size() == greedy_result.size()
        && greedy_result.size() == dynamic_result.size();

    std::cout << '\n';
    std::cout << "Same number of selected activities: "
              << (same_size ? "YES" : "NO")
              << '\n';

    if (!same_size) {
        std::cout << "  Recursive size: " << recursive_result.size() << '\n';
        std::cout << "  Greedy size:    " << greedy_result.size() << '\n';
        std::cout << "  Dynamic size:   " << dynamic_result.size() << '\n';
    }

    std::cout << '\n';
}

TestCase make_random_sorted_case(
    const std::string& name,
    std::size_t n,
    int max_start,
    int max_duration,
    unsigned int seed
) {
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> start_distribution(0, max_start);
    std::uniform_int_distribution<int> duration_distribution(1, max_duration);

    std::vector<std::pair<int, int>> intervals;
    intervals.reserve(n);

    for (std::size_t i = 0; i < n; ++i) {
        const int start = start_distribution(generator);
        const int finish = start + duration_distribution(generator);
        intervals.emplace_back(start, finish);
    }

    std::sort(
        intervals.begin(),
        intervals.end(),
        [](const std::pair<int, int>& lhs, const std::pair<int, int>& rhs) {
            if (lhs.second == rhs.second) {
                return lhs.first < rhs.first;
            }

            return lhs.second < rhs.second;
        }
    );

    std::vector<int> s;
    std::vector<int> f;
    s.reserve(n);
    f.reserve(n);

    for (const auto& [start, finish] : intervals) {
        s.push_back(start);
        f.push_back(finish);
    }

    return TestCase{name, s, f};
}

void run_benchmark_case(
    const TestCase& test_case,
    std::size_t fast_iterations,
    std::size_t dynamic_iterations
) {
    std::cout << "============================================================\n";
    std::cout << "Benchmark: " << test_case.name << " (n = " << test_case.s.size() << ")\n";
    std::cout << "============================================================\n";

    if (test_case.s.size() != test_case.f.size()) {
        std::cout << "Invalid benchmark case: s and f have different sizes.\n\n";
        return;
    }

    const std::vector<int> padded_s = with_recursive_padding(test_case.s);
    const std::vector<int> padded_f = with_recursive_padding(test_case.f);
    const std::size_t n = test_case.s.size();

    const BenchmarkResult recursive_result = benchmark_selector(
        "Recursive",
        estimated_recursive_auxiliary_space(n),
        fast_iterations,
        [&]() {
            return recursive_activity_selector(padded_s, padded_f, 0);
        }
    );

    const BenchmarkResult greedy_result = benchmark_selector(
        "Greedy",
        estimated_greedy_auxiliary_space(),
        fast_iterations,
        [&]() {
            return greedy_activity_selector(test_case.s, test_case.f);
        }
    );

    const BenchmarkResult dynamic_result = benchmark_selector(
        "Dynamic",
        estimated_dynamic_auxiliary_space(n),
        dynamic_iterations,
        [&]() {
            return dynamic_activity_selector(test_case.s, test_case.f);
        }
    );

    print_benchmark_result(recursive_result);
    print_benchmark_result(greedy_result);
    print_benchmark_result(dynamic_result);

    const bool same_size =
        recursive_result.selected_count == greedy_result.selected_count
        && greedy_result.selected_count == dynamic_result.selected_count;

    std::cout << "Same selected count: " << (same_size ? "YES" : "NO") << "\n\n";
}

}  // namespace

void run_activity_selector_comparison() {
    const std::vector<TestCase> test_cases{
        {
            "CLRS example",
            {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12},
            {4, 5, 6, 7, 9, 9, 10, 11, 12, 14, 16}
        },
        {
            "Empty input",
            {},
            {}
        },
        {
            "Single activity",
            {2},
            {5}
        },
        {
            "All activities compatible",
            {1, 3, 5, 7},
            {2, 4, 6, 8}
        },
        {
            "All activities overlap",
            {1, 2, 3, 4},
            {10, 11, 12, 13}
        },
        {
            "Boundary compatibility: start equals previous finish",
            {1, 3, 5, 7},
            {3, 5, 7, 9}
        },
        {
            "Tie in finish times",
            {1, 2, 4, 6},
            {3, 3, 5, 7}
        },
        {
            "Dynamic may choose a different optimal solution",
            {1, 2, 4, 6, 8},
            {3, 5, 7, 9, 10}
        }
    };

    for (const TestCase& test_case : test_cases) {
        run_test_case(test_case);
    }

    const std::vector<TestCase> benchmark_cases{
        make_random_sorted_case("Random sorted small", 20, 100, 20, 42),
        make_random_sorted_case("Random sorted medium", 100, 500, 50, 43),
        make_random_sorted_case("Random sorted large", 500, 2'000, 100, 44)
    };

    for (const TestCase& benchmark_case : benchmark_cases) {
        run_benchmark_case(
            benchmark_case,
            1'000,
            benchmark_case.s.size() <= 100 ? 50 : 3
        );
    }
}

// The dynamic programming formulation solves Activity Selection by considering 
// every compatible activity k between two boundary activities i and j. This 
// yields an O(n^3) algorithm with O(n^2) space.

// However, the problem has the greedy-choice property: selecting the first activity 
// with the earliest finish time is always safe. Therefore, the greedy algorithm 
// achieves the same optimal result in O(n) time and O(1) auxiliary space, assuming 
// activities are sorted by nondecreasing finish time.