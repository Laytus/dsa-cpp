#include <catch2/catch_test_macros.hpp>

#include "algorithms/select.hpp"

#include <cstddef>
#include <stdexcept>
#include <vector>

using dsa::algorithms::select;

TEST_CASE("select returns the minimum element when i is 0", "[select]") {
    std::vector<int> values = {7, 2, 9, 4, 1};

    const int result = select(values, 0, values.size(), 0);

    REQUIRE(result == 1);
}

TEST_CASE("select returns the maximum element when i is size minus one", "[select]") {
    std::vector<int> values = {7, 2, 9, 4, 1};

    const int result = select(values, 0, values.size(), values.size() - 1);

    REQUIRE(result == 9);
}

TEST_CASE("select returns the middle order statistic", "[select]") {
    std::vector<int> values = {7, 2, 9, 4, 1};

    const int result = select(values, 0, values.size(), 2);

    REQUIRE(result == 4);
}

TEST_CASE("select works with one element", "[select]") {
    std::vector<int> values = {42};

    const int result = select(values, 0, values.size(), 0);

    REQUIRE(result == 42);
}

TEST_CASE("select works with two elements", "[select]") {
    SECTION("minimum") {
        std::vector<int> values = {10, 5};

        const int result = select(values, 0, values.size(), 0);

        REQUIRE(result == 5);
    }

    SECTION("maximum") {
        std::vector<int> values = {10, 5};

        const int result = select(values, 0, values.size(), 1);

        REQUIRE(result == 10);
    }
}

TEST_CASE("select works with already sorted input", "[select]") {
    std::vector<int> values = {1, 2, 3, 4, 5, 6};

    REQUIRE(select(values, 0, values.size(), 0) == 1);
    REQUIRE(select(values, 0, values.size(), 2) == 3);
    REQUIRE(select(values, 0, values.size(), 5) == 6);
}

TEST_CASE("select works with reverse sorted input", "[select]") {
    std::vector<int> values = {6, 5, 4, 3, 2, 1};

    REQUIRE(select(values, 0, values.size(), 0) == 1);
    REQUIRE(select(values, 0, values.size(), 2) == 3);
    REQUIRE(select(values, 0, values.size(), 5) == 6);
}

TEST_CASE("select works with negative numbers", "[select]") {
    std::vector<int> values = {-3, -10, 4, 0, -7};

    REQUIRE(select(values, 0, values.size(), 0) == -10);
    REQUIRE(select(values, 0, values.size(), 2) == -3);
    REQUIRE(select(values, 0, values.size(), 4) == 4);
}

TEST_CASE("select works with repeated values", "[select]") {
    const std::vector<int> original = {4, 2, 4, 1, 2, 9};
    const std::vector<int> sorted = {1, 2, 2, 4, 4, 9};

    for (std::size_t i = 0; i < original.size(); ++i) {
        std::vector<int> values = original;

        REQUIRE(select(values, 0, values.size(), i) == sorted[i]);
    }
}

TEST_CASE("select works when all values are equal", "[select]") {
    const std::vector<int> original = {5, 5, 5, 5, 5, 5, 5};

    for (std::size_t i = 0; i < original.size(); ++i) {
        std::vector<int> values = original;

        REQUIRE(select(values, 0, values.size(), i) == 5);
    }
}

TEST_CASE("select works with a larger unsorted input", "[select]") {
    const std::vector<int> original = {
        12, 3, 5, 7, 4,
        19, 26, 1, 15, 9,
        8, 11, 6, 2, 10
    };

    const std::vector<int> sorted = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
        11, 12, 15, 19, 26
    };

    for (std::size_t i = 0; i < original.size(); ++i) {
        std::vector<int> values = original;

        REQUIRE(select(values, 0, values.size(), i) == sorted[i]);
    }
}

TEST_CASE("select works on a subrange", "[select]") {
    const std::vector<int> original = {100, 7, 2, 9, 4, 1, 200};

    SECTION("minimum in subrange") {
        std::vector<int> values = original;

        REQUIRE(select(values, 1, 6, 0) == 1);
    }

    SECTION("middle order statistic in subrange") {
        std::vector<int> values = original;

        REQUIRE(select(values, 1, 6, 2) == 4);
    }

    SECTION("maximum in subrange") {
        std::vector<int> values = original;

        REQUIRE(select(values, 1, 6, 4) == 9);
    }
}

TEST_CASE("select throws when range is empty", "[select]") {
    std::vector<int> values = {1, 2, 3};

    REQUIRE_THROWS_AS(select(values, 0, 0, 0), std::invalid_argument);
    REQUIRE_THROWS_AS(select(values, 2, 2, 0), std::invalid_argument);
}

TEST_CASE("select throws when order statistic index is out of range", "[select]") {
    std::vector<int> values = {1, 2, 3};

    REQUIRE_THROWS_AS(select(values, 0, values.size(), 3), std::out_of_range);
    REQUIRE_THROWS_AS(select(values, 1, values.size(), 2), std::out_of_range);
}