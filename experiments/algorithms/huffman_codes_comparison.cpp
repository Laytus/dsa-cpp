#include "algorithms/huffman_codes.hpp"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

using dsa::algorithms::HuffmanNode;
using dsa::algorithms::HuffmanTree;
using dsa::algorithms::dynamic_alphabetic_huffman;
using dsa::algorithms::greedy_huffman;

struct TestCase {
    std::string name;
    std::vector<std::pair<char, std::size_t>> frequencies;
};

struct TreeStats {
    std::size_t root_frequency;
    std::size_t leaf_count;
    std::size_t weighted_path_length;
    std::size_t height;
};

struct Code {
    char symbol;
    std::size_t freq;
    std::string bits;
};

struct BenchmarkResult {
    std::string name;
    std::size_t weighted_path_length;
    double average_us;
    std::string auxiliary_space;
};

bool is_leaf(const HuffmanNode* node) {
    return node != nullptr && node->left == nullptr && node->right == nullptr;
}

std::size_t sum_frequencies(
    const std::vector<std::pair<char, std::size_t>>& frequencies
) {
    std::size_t total = 0;

    for (const auto& [symbol, freq] : frequencies) {
        total += freq;
    }

    return total;
}

std::size_t count_leaves(const HuffmanNode* node) {
    if (node == nullptr) {
        return 0;
    }

    if (is_leaf(node)) {
        return 1;
    }

    return count_leaves(node->left) + count_leaves(node->right);
}

std::size_t tree_height(const HuffmanNode* node) {
    if (node == nullptr) {
        return 0;
    }

    return 1 + std::max(tree_height(node->left), tree_height(node->right));
}

std::size_t weighted_path_length_impl(
    const HuffmanNode* node,
    std::size_t depth
) {
    if (node == nullptr) {
        return 0;
    }

    if (is_leaf(node)) {
        return node->freq * depth;
    }

    return weighted_path_length_impl(node->left, depth + 1)
        + weighted_path_length_impl(node->right, depth + 1);
}

std::size_t weighted_path_length(const HuffmanNode* root) {
    return weighted_path_length_impl(root, 0);
}

TreeStats compute_stats(const HuffmanTree& tree) {
    if (tree.root == nullptr) {
        return TreeStats{0, 0, 0, 0};
    }

    return TreeStats{
        tree.root->freq,
        count_leaves(tree.root),
        weighted_path_length(tree.root),
        tree_height(tree.root)
    };
}

void collect_codes_impl(
    const HuffmanNode* node,
    std::string current,
    std::vector<Code>& codes
) {
    if (node == nullptr) {
        return;
    }

    if (is_leaf(node)) {
        if (current.empty()) {
            current = "0";
        }

        codes.push_back(Code{node->symbol, node->freq, current});
        return;
    }

    collect_codes_impl(node->left, current + "0", codes);
    collect_codes_impl(node->right, current + "1", codes);
}

std::vector<Code> collect_codes(const HuffmanTree& tree) {
    std::vector<Code> codes;
    collect_codes_impl(tree.root, "", codes);

    std::sort(
        codes.begin(),
        codes.end(),
        [](const Code& lhs, const Code& rhs) {
            return lhs.symbol < rhs.symbol;
        }
    );

    return codes;
}

void print_codes(const std::string& label, const HuffmanTree& tree) {
    const std::vector<Code> codes = collect_codes(tree);

    std::cout << label << " codes:\n";

    if (codes.empty()) {
        std::cout << "  []\n";
        return;
    }

    for (const Code& code : codes) {
        std::cout << "  " << code.symbol
                  << " freq=" << std::setw(4) << code.freq
                  << " code=" << code.bits
                  << '\n';
    }
}

void print_stats(const std::string& label, const TreeStats& stats) {
    std::cout << label << ":\n";
    std::cout << "  root frequency:       " << stats.root_frequency << '\n';
    std::cout << "  leaf count:           " << stats.leaf_count << '\n';
    std::cout << "  weighted path length: " << stats.weighted_path_length << '\n';
    std::cout << "  height:               " << stats.height << '\n';
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

std::string estimated_greedy_auxiliary_space(std::size_t n) {
    const std::size_t queue_bytes = n * sizeof(HuffmanNode*);
    const std::size_t node_storage = ((2 * n) - 1) * sizeof(HuffmanNode);

    return "O(n), approx "
        + format_bytes(queue_bytes + node_storage)
        + " excluding vector overhead";
}

std::string estimated_dynamic_auxiliary_space(std::size_t n) {
    const std::size_t dp_bytes = n * n * sizeof(std::size_t);
    const std::size_t split_bytes = n * n * sizeof(std::size_t);
    const std::size_t prefix_bytes = (n + 1) * sizeof(std::size_t);
    const std::size_t node_storage = ((2 * n) - 1) * sizeof(HuffmanNode);

    return "O(n^2), approx "
        + format_bytes(dp_bytes + split_bytes + prefix_bytes + node_storage)
        + " excluding vector overhead";
}

template <typename Func>
BenchmarkResult benchmark_huffman(
    const std::string& name,
    const std::string& auxiliary_space,
    std::size_t iterations,
    Func huffman
) {
    using Clock = std::chrono::steady_clock;

    std::size_t checksum = 0;
    std::size_t last_cost = 0;

    const auto start = Clock::now();

    for (std::size_t i = 0; i < iterations; ++i) {
        HuffmanTree tree = huffman();
        last_cost = weighted_path_length(tree.root);
        checksum += last_cost;
    }

    const auto end = Clock::now();

    const auto elapsed_us =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    if (checksum == static_cast<std::size_t>(-1)) {
        std::cout << "Impossible checksum: " << checksum << '\n';
    }

    return BenchmarkResult{
        name,
        last_cost,
        static_cast<double>(elapsed_us) / static_cast<double>(iterations),
        auxiliary_space
    };
}

void print_benchmark_result(const BenchmarkResult& result) {
    std::cout << std::left << std::setw(22) << result.name
              << " cost=" << std::setw(8) << result.weighted_path_length
              << " avg_time=" << std::setw(12)
              << std::fixed << std::setprecision(2)
              << result.average_us << " us"
              << " space=" << result.auxiliary_space
              << '\n';
}

void run_correctness_case(const TestCase& test_case) {
    std::cout << "============================================================\n";
    std::cout << test_case.name << '\n';
    std::cout << "============================================================\n";

    const std::size_t expected_total = sum_frequencies(test_case.frequencies);
    const std::size_t expected_leaves = test_case.frequencies.size();

    HuffmanTree greedy_tree = greedy_huffman(test_case.frequencies);
    HuffmanTree dynamic_tree = dynamic_alphabetic_huffman(test_case.frequencies);

    const TreeStats greedy_stats = compute_stats(greedy_tree);
    const TreeStats dynamic_stats = compute_stats(dynamic_tree);

    std::cout << "Expected root frequency: " << expected_total << '\n';
    std::cout << "Expected leaf count:     " << expected_leaves << "\n\n";

    print_stats("Greedy Huffman", greedy_stats);
    std::cout << '\n';
    print_stats("Dynamic alphabetic Huffman", dynamic_stats);

    std::cout << '\n';

    const bool same_root_frequency =
        greedy_stats.root_frequency == expected_total
        && dynamic_stats.root_frequency == expected_total;

    const bool same_leaf_count =
        greedy_stats.leaf_count == expected_leaves
        && dynamic_stats.leaf_count == expected_leaves;

    std::cout << "Checks:\n";
    std::cout << "  Root frequency OK: " << (same_root_frequency ? "YES" : "NO") << '\n';
    std::cout << "  Leaf count OK:     " << (same_leaf_count ? "YES" : "NO") << '\n';

    std::cout << '\n';
    std::cout << "Cost comparison:\n";
    std::cout << "  Greedy cost:             " << greedy_stats.weighted_path_length << '\n';
    std::cout << "  Dynamic alphabetic cost: " << dynamic_stats.weighted_path_length << '\n';

    if (greedy_stats.weighted_path_length == dynamic_stats.weighted_path_length) {
        std::cout << "  Same cost: YES\n";
    } else {
        std::cout << "  Same cost: NO ";
        std::cout << "(expected sometimes, because the DP version is alphabetic)\n";
    }

    std::cout << '\n';
    print_codes("Greedy", greedy_tree);
    std::cout << '\n';
    print_codes("Dynamic alphabetic", dynamic_tree);

    std::cout << '\n';
}

TestCase make_random_frequency_case(
    const std::string& name,
    std::size_t n,
    std::size_t min_freq,
    std::size_t max_freq,
    unsigned int seed
) {
    std::mt19937 generator(seed);

    std::uniform_int_distribution<std::size_t> freq_distribution(
        min_freq,
        max_freq
    );

    std::vector<std::pair<char, std::size_t>> frequencies;
    frequencies.reserve(n);

    for (std::size_t i = 0; i < n; ++i) {
        const char symbol = static_cast<char>('a' + static_cast<int>(i % 26));
        frequencies.emplace_back(symbol, freq_distribution(generator));
    }

    return TestCase{name, frequencies};
}

void run_benchmark_case(
    const TestCase& test_case,
    std::size_t greedy_iterations,
    std::size_t dynamic_iterations
) {
    std::cout << "============================================================\n";
    std::cout << "Benchmark: " << test_case.name
              << " (n = " << test_case.frequencies.size() << ")\n";
    std::cout << "============================================================\n";

    const std::size_t n = test_case.frequencies.size();

    const BenchmarkResult greedy_result = benchmark_huffman(
        "Greedy Huffman",
        estimated_greedy_auxiliary_space(n),
        greedy_iterations,
        [&]() {
            return greedy_huffman(test_case.frequencies);
        }
    );

    const BenchmarkResult dynamic_result = benchmark_huffman(
        "Dynamic alphabetic",
        estimated_dynamic_auxiliary_space(n),
        dynamic_iterations,
        [&]() {
            return dynamic_alphabetic_huffman(test_case.frequencies);
        }
    );

    print_benchmark_result(greedy_result);
    print_benchmark_result(dynamic_result);

    std::cout << '\n';
}

}  // namespace

void run_huffman_codes_comparison() {
    const std::vector<TestCase> correctness_cases{
        {
            "CLRS-style frequency example",
            {
                {'a', 45},
                {'b', 13},
                {'c', 12},
                {'d', 16},
                {'e', 9},
                {'f', 5}
            }
        },
        {
            "Single symbol",
            {
                {'x', 100}
            }
        },
        {
            "Equal frequencies",
            {
                {'a', 10},
                {'b', 10},
                {'c', 10},
                {'d', 10}
            }
        },
        {
            "Increasing frequencies",
            {
                {'a', 1},
                {'b', 2},
                {'c', 4},
                {'d', 8},
                {'e', 16},
                {'f', 32}
            }
        }
    };

    for (const TestCase& test_case : correctness_cases) {
        run_correctness_case(test_case);
    }

    const std::vector<TestCase> benchmark_cases{
        make_random_frequency_case("Random frequencies small", 8, 1, 100, 42),
        make_random_frequency_case("Random frequencies medium", 32, 1, 500, 43),
        make_random_frequency_case("Random frequencies large", 128, 1, 1'000, 44)
    };

    for (const TestCase& benchmark_case : benchmark_cases) {
        run_benchmark_case(
            benchmark_case,
            1'000,
            benchmark_case.frequencies.size() <= 32 ? 100 : 5
        );
    }
}