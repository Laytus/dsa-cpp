#include <catch2/catch_test_macros.hpp>

#include "algorithms/randomized_select.hpp"

#include <cstddef>
#include <vector>

using dsa::algorithms::randomized_select;

TEST_CASE("randomized_select returns the minimum element when i is 0", "[randomized_select]") {
    std::vector<int> values = {7, 2, 9, 4, 1};

    const int result = randomized_select(values, 0, values.size(), 0);

    REQUIRE(result == 1);
}

TEST_CASE("randomized_select returns the maximum element when i is size minus one", "[randomized_select]") {
    std::vector<int> values = {7, 2, 9, 4, 1};

    const int result = randomized_select(values, 0, values.size(), values.size() - 1);

    REQUIRE(result == 9);
}

TEST_CASE("randomized_select returns the middle order statistic", "[randomized_select]") {
    std::vector<int> values = {7, 2, 9, 4, 1};

    const int result = randomized_select(values, 0, values.size(), 2);

    REQUIRE(result == 4);
}

TEST_CASE("randomized_select works with one element", "[randomized_select]") {
    std::vector<int> values = {42};

    const int result = randomized_select(values, 0, values.size(), 0);

    REQUIRE(result == 42);
}

TEST_CASE("randomized_select works with two elements", "[randomized_select]") {
    SECTION("minimum") {
        std::vector<int> values = {10, 5};

        const int result = randomized_select(values, 0, values.size(), 0);

        REQUIRE(result == 5);
    }

    SECTION("maximum") {
        std::vector<int> values = {10, 5};

        const int result = randomized_select(values, 0, values.size(), 1);

        REQUIRE(result == 10);
    }
}

TEST_CASE("randomized_select works with already sorted input", "[randomized_select]") {
    std::vector<int> values = {1, 2, 3, 4, 5, 6};

    REQUIRE(randomized_select(values, 0, values.size(), 0) == 1);
    REQUIRE(randomized_select(values, 0, values.size(), 2) == 3);
    REQUIRE(randomized_select(values, 0, values.size(), 5) == 6);
}

TEST_CASE("randomized_select works with reverse sorted input", "[randomized_select]") {
    std::vector<int> values = {6, 5, 4, 3, 2, 1};

    REQUIRE(randomized_select(values, 0, values.size(), 0) == 1);
    REQUIRE(randomized_select(values, 0, values.size(), 2) == 3);
    REQUIRE(randomized_select(values, 0, values.size(), 5) == 6);
}

TEST_CASE("randomized_select works with negative numbers", "[randomized_select]") {
    std::vector<int> values = {-3, -10, 4, 0, -7};

    REQUIRE(randomized_select(values, 0, values.size(), 0) == -10);
    REQUIRE(randomized_select(values, 0, values.size(), 2) == -3);
    REQUIRE(randomized_select(values, 0, values.size(), 4) == 4);
}

TEST_CASE("randomized_select works with repeated values", "[randomized_select]") {
    std::vector<int> values = {4, 2, 4, 1, 2, 9};

    REQUIRE(randomized_select(values, 0, values.size(), 0) == 1);
    REQUIRE(randomized_select(values, 0, values.size(), 1) == 2);
    REQUIRE(randomized_select(values, 0, values.size(), 2) == 2);
    REQUIRE(randomized_select(values, 0, values.size(), 3) == 4);
    REQUIRE(randomized_select(values, 0, values.size(), 4) == 4);
    REQUIRE(randomized_select(values, 0, values.size(), 5) == 9);
}

TEST_CASE("randomized_select works on a subrange", "[randomized_select]") {
    std::vector<int> values = {100, 7, 2, 9, 4, 1, 200};

    REQUIRE(randomized_select(values, 1, 6, 0) == 1);
    REQUIRE(randomized_select(values, 1, 6, 2) == 4);
    REQUIRE(randomized_select(values, 1, 6, 4) == 9);
}