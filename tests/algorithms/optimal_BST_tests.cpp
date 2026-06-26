#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "algorithms/optimal_BST.hpp"

using dsa::algorithms::build_optimal_BST;
using dsa::algorithms::optimal_BST;

TEST_CASE("optimal_BST computes CLRS example cost") {
    const std::vector<double> p{0.15, 0.10, 0.05, 0.10, 0.20};
    const std::vector<double> q{0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

    const auto result = optimal_BST(p, q);

    REQUIRE(result.e[0][5] == Catch::Approx(2.75));
}

TEST_CASE("optimal_BST computes expected root table values") {
    const std::vector<double> p{0.15, 0.10, 0.05, 0.10, 0.20};
    const std::vector<double> q{0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

    const auto result = optimal_BST(p, q);

    REQUIRE(result.root[0][4] == 1);
    REQUIRE(result.root[0][0] == 0);
    REQUIRE(result.root[2][4] == 4);
}

TEST_CASE("build_optimal_BST builds CLRS example root") {
    const std::vector<double> p{0.15, 0.10, 0.05, 0.10, 0.20};
    const std::vector<double> q{0.05, 0.10, 0.05, 0.05, 0.05, 0.10};

    const auto result = optimal_BST(p, q);
    const auto tree = build_optimal_BST(result.root, 0, p.size() - 1);

    REQUIRE(tree != nullptr);
    REQUIRE(tree->key_index == 1);
    REQUIRE(tree->left != nullptr);
    REQUIRE(tree->left->key_index == 0);
    REQUIRE(tree->right != nullptr);
    REQUIRE(tree->right->key_index == 4);
}

TEST_CASE("optimal_BST throws when q has invalid size") {
    const std::vector<double> p{0.15, 0.10};
    const std::vector<double> q{0.05, 0.10};

    REQUIRE_THROWS_AS(optimal_BST(p, q), std::invalid_argument);
}

TEST_CASE("optimal_BST works with one key") {
    const std::vector<double> p{0.50};
    const std::vector<double> q{0.25, 0.25};

    const auto result = optimal_BST(p, q);

    REQUIRE(result.e[0][1] == Catch::Approx(1.5));
    REQUIRE(result.root[0][0] == 0);

    const auto tree = build_optimal_BST(result.root, 0, 0);

    REQUIRE(tree != nullptr);
    REQUIRE(tree->key_index == 0);
    REQUIRE(tree->left == nullptr);
    REQUIRE(tree->right == nullptr);
}

TEST_CASE("build_optimal_BST returns nullptr for empty interval") {
    dsa::algorithms::MatrixSize_t root{};

    const auto tree = build_optimal_BST(root, 1, 0);

    REQUIRE(tree == nullptr);
}