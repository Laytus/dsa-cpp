#include <catch2/catch_test_macros.hpp>

#include "algorithms/find_maximum_subarray.hpp"

#include <cstddef>
#include <vector>

TEST_CASE("find_maximum_subarray finds the CLRS example maximum subarray") {
    const std::vector<int> values{
        13, -3, -25, 20, -3, -16, -23, 18,
        20, -7, 12, -5, -22, 15, -4, 7
    };

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 0, values.size());

    REQUIRE(low == 7);
    REQUIRE(high == 11);
    REQUIRE(sum == 43);
}

TEST_CASE("find_maximum_subarray works when the best subarray is at the beginning") {
    const std::vector<int> values{8, 4, -10, 2, -3};

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 0, values.size());

    REQUIRE(low == 0);
    REQUIRE(high == 2);
    REQUIRE(sum == 12);
}

TEST_CASE("find_maximum_subarray works when the best subarray is at the end") {
    const std::vector<int> values{-5, -2, 3, 4, 6};

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 0, values.size());

    REQUIRE(low == 2);
    REQUIRE(high == 5);
    REQUIRE(sum == 13);
}

TEST_CASE("find_maximum_subarray works when the best subarray crosses the middle") {
    const std::vector<int> values{-2, 3, 4, -1, 5, -10};

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 0, values.size());

    REQUIRE(low == 1);
    REQUIRE(high == 5);
    REQUIRE(sum == 11);
}

TEST_CASE("find_maximum_subarray returns the largest element for an all-negative vector") {
    const std::vector<int> values{-8, -3, -10, -2, -5};

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 0, values.size());

    REQUIRE(low == 3);
    REQUIRE(high == 4);
    REQUIRE(sum == -2);
}

TEST_CASE("find_maximum_subarray works with a single positive element") {
    const std::vector<int> values{42};

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 0, values.size());

    REQUIRE(low == 0);
    REQUIRE(high == 1);
    REQUIRE(sum == 42);
}

TEST_CASE("find_maximum_subarray works with a single negative element") {
    const std::vector<int> values{-42};

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 0, values.size());

    REQUIRE(low == 0);
    REQUIRE(high == 1);
    REQUIRE(sum == -42);
}

TEST_CASE("find_maximum_subarray works when all elements are positive") {
    const std::vector<int> values{1, 2, 3, 4, 5};

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 0, values.size());

    REQUIRE(low == 0);
    REQUIRE(high == 5);
    REQUIRE(sum == 15);
}

TEST_CASE("find_maximum_subarray works with zeros") {
    const std::vector<int> values{-2, 0, -1, 0, -3};

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 0, values.size());

    REQUIRE(sum == 0);
    REQUIRE(high == low + 1);
}

TEST_CASE("find_maximum_subarray works on a subrange") {
    const std::vector<int> values{100, -50, 4, -1, 2, 1, -100, 200};

    auto [low, high, sum] = dsa::algorithms::find_maximum_subarray(values, 2, 6);

    REQUIRE(low == 2);
    REQUIRE(high == 6);
    REQUIRE(sum == 6);
}