#include <catch2/catch_test_macros.hpp>

#include "algorithms/huffman_codes.hpp"

#include <cstddef>
#include <string>
#include <utility>
#include <vector>

namespace {

bool is_leaf(const dsa::algorithms::HuffmanNode* node) {
    return node != nullptr
        && node->left == nullptr
        && node->right == nullptr;
}

std::size_t weighted_path_length(
    const dsa::algorithms::HuffmanNode* node,
    std::size_t depth = 0
) {
    if (node == nullptr) {
        return 0;
    }

    if (is_leaf(node)) {
        return node->freq * depth;
    }

    return weighted_path_length(node->left, depth + 1)
        + weighted_path_length(node->right, depth + 1);
}

std::size_t leaf_frequency_sum(const dsa::algorithms::HuffmanNode* node) {
    if (node == nullptr) {
        return 0;
    }

    if (is_leaf(node)) {
        return node->freq;
    }

    return leaf_frequency_sum(node->left)
        + leaf_frequency_sum(node->right);
}

std::size_t leaf_count(const dsa::algorithms::HuffmanNode* node) {
    if (node == nullptr) {
        return 0;
    }

    if (is_leaf(node)) {
        return 1;
    }

    return leaf_count(node->left) + leaf_count(node->right);
}

void collect_leaf_symbols_in_order(
    const dsa::algorithms::HuffmanNode* node,
    std::string& symbols
) {
    if (node == nullptr) {
        return;
    }

    if (is_leaf(node)) {
        symbols.push_back(node->symbol);
        return;
    }

    collect_leaf_symbols_in_order(node->left, symbols);
    collect_leaf_symbols_in_order(node->right, symbols);
}

bool internal_frequencies_are_consistent(
    const dsa::algorithms::HuffmanNode* node
) {
    if (node == nullptr || is_leaf(node)) {
        return true;
    }

    if (node->left == nullptr || node->right == nullptr) {
        return false;
    }

    return node->freq == node->left->freq + node->right->freq
        && internal_frequencies_are_consistent(node->left)
        && internal_frequencies_are_consistent(node->right);
}

}  // namespace

TEST_CASE("greedy_huffman returns empty tree for empty input") {
    const std::vector<std::pair<char, std::size_t>> frequencies;

    const auto tree = dsa::algorithms::greedy_huffman(frequencies);

    REQUIRE(tree.root == nullptr);
    REQUIRE(tree.nodes.empty());
}

TEST_CASE("dynamic_alphabetic_huffman returns empty tree for empty input") {
    const std::vector<std::pair<char, std::size_t>> frequencies;

    const auto tree = dsa::algorithms::dynamic_alphabetic_huffman(frequencies);

    REQUIRE(tree.root == nullptr);
    REQUIRE(tree.nodes.empty());
}

TEST_CASE("greedy_huffman works with one symbol") {
    const std::vector<std::pair<char, std::size_t>> frequencies{
        {'a', 42}
    };

    const auto tree = dsa::algorithms::greedy_huffman(frequencies);

    REQUIRE(tree.root != nullptr);
    REQUIRE(tree.nodes.size() == 1);

    REQUIRE(is_leaf(tree.root));
    REQUIRE(tree.root->symbol == 'a');
    REQUIRE(tree.root->freq == 42);
    REQUIRE(weighted_path_length(tree.root) == 0);
}

TEST_CASE("dynamic_alphabetic_huffman works with one symbol") {
    const std::vector<std::pair<char, std::size_t>> frequencies{
        {'a', 42}
    };

    const auto tree = dsa::algorithms::dynamic_alphabetic_huffman(frequencies);

    REQUIRE(tree.root != nullptr);
    REQUIRE(tree.nodes.size() == 1);

    REQUIRE(is_leaf(tree.root));
    REQUIRE(tree.root->symbol == 'a');
    REQUIRE(tree.root->freq == 42);
    REQUIRE(weighted_path_length(tree.root) == 0);
}

TEST_CASE("greedy_huffman builds valid tree for two symbols") {
    const std::vector<std::pair<char, std::size_t>> frequencies{
        {'a', 5},
        {'b', 9}
    };

    const auto tree = dsa::algorithms::greedy_huffman(frequencies);

    REQUIRE(tree.root != nullptr);
    REQUIRE(tree.nodes.size() == 3);

    REQUIRE(!is_leaf(tree.root));
    REQUIRE(tree.root->freq == 14);
    REQUIRE(leaf_count(tree.root) == 2);
    REQUIRE(leaf_frequency_sum(tree.root) == 14);
    REQUIRE(internal_frequencies_are_consistent(tree.root));
    REQUIRE(weighted_path_length(tree.root) == 14);
}

TEST_CASE("dynamic_alphabetic_huffman builds valid tree for two symbols") {
    const std::vector<std::pair<char, std::size_t>> frequencies{
        {'a', 5},
        {'b', 9}
    };

    const auto tree = dsa::algorithms::dynamic_alphabetic_huffman(frequencies);

    REQUIRE(tree.root != nullptr);
    REQUIRE(tree.nodes.size() == 3);

    REQUIRE(!is_leaf(tree.root));
    REQUIRE(tree.root->freq == 14);
    REQUIRE(leaf_count(tree.root) == 2);
    REQUIRE(leaf_frequency_sum(tree.root) == 14);
    REQUIRE(internal_frequencies_are_consistent(tree.root));
    REQUIRE(weighted_path_length(tree.root) == 14);
}

TEST_CASE("greedy_huffman computes CLRS example weighted path length") {
    const std::vector<std::pair<char, std::size_t>> frequencies{
        {'a', 45},
        {'b', 13},
        {'c', 12},
        {'d', 16},
        {'e', 9},
        {'f', 5}
    };

    const auto tree = dsa::algorithms::greedy_huffman(frequencies);

    REQUIRE(tree.root != nullptr);
    REQUIRE(tree.nodes.size() == 11);

    REQUIRE(tree.root->freq == 100);
    REQUIRE(leaf_count(tree.root) == 6);
    REQUIRE(leaf_frequency_sum(tree.root) == 100);
    REQUIRE(internal_frequencies_are_consistent(tree.root));

    REQUIRE(weighted_path_length(tree.root) == 224);
}

TEST_CASE("dynamic_alphabetic_huffman preserves alphabetic leaf order") {
    const std::vector<std::pair<char, std::size_t>> frequencies{
        {'a', 1},
        {'b', 2},
        {'c', 3},
        {'d', 4}
    };

    const auto tree = dsa::algorithms::dynamic_alphabetic_huffman(frequencies);

    REQUIRE(tree.root != nullptr);
    REQUIRE(tree.nodes.size() == 7);

    std::string symbols;
    collect_leaf_symbols_in_order(tree.root, symbols);

    REQUIRE(symbols == "abcd");
}

TEST_CASE("dynamic_alphabetic_huffman computes optimal alphabetic cost for small input") {
    const std::vector<std::pair<char, std::size_t>> frequencies{
        {'a', 1},
        {'b', 2},
        {'c', 3},
        {'d', 4}
    };

    const auto tree = dsa::algorithms::dynamic_alphabetic_huffman(frequencies);

    REQUIRE(tree.root != nullptr);
    REQUIRE(tree.root->freq == 10);
    REQUIRE(leaf_count(tree.root) == 4);
    REQUIRE(leaf_frequency_sum(tree.root) == 10);
    REQUIRE(internal_frequencies_are_consistent(tree.root));

    REQUIRE(weighted_path_length(tree.root) == 19);
}

TEST_CASE("dynamic_alphabetic_huffman keeps all leaves in input order for larger input") {
    const std::vector<std::pair<char, std::size_t>> frequencies{
        {'a', 45},
        {'b', 13},
        {'c', 12},
        {'d', 16},
        {'e', 9},
        {'f', 5}
    };

    const auto tree = dsa::algorithms::dynamic_alphabetic_huffman(frequencies);

    REQUIRE(tree.root != nullptr);
    REQUIRE(tree.nodes.size() == 11);

    std::string symbols;
    collect_leaf_symbols_in_order(tree.root, symbols);

    REQUIRE(symbols == "abcdef");
    REQUIRE(tree.root->freq == 100);
    REQUIRE(leaf_count(tree.root) == 6);
    REQUIRE(leaf_frequency_sum(tree.root) == 100);
    REQUIRE(internal_frequencies_are_consistent(tree.root));
}

TEST_CASE("greedy_huffman and dynamic_alphabetic_huffman can produce different costs") {
    const std::vector<std::pair<char, std::size_t>> frequencies{
        {'a', 45},
        {'b', 13},
        {'c', 12},
        {'d', 16},
        {'e', 9},
        {'f', 5}
    };

    const auto greedy_tree = dsa::algorithms::greedy_huffman(frequencies);
    const auto alphabetic_tree =
        dsa::algorithms::dynamic_alphabetic_huffman(frequencies);

    REQUIRE(greedy_tree.root != nullptr);
    REQUIRE(alphabetic_tree.root != nullptr);

    REQUIRE(weighted_path_length(greedy_tree.root) == 224);
    REQUIRE(weighted_path_length(alphabetic_tree.root) >= 224);
}