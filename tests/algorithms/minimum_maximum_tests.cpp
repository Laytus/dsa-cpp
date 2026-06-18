#include <catch2/catch_test_macros.hpp>

#include "algorithms/minimum_maximum.hpp"

#include <stdexcept>
#include <utility>
#include <vector>

using dsa::algorithms::maximum;
using dsa::algorithms::minimum;
using dsa::algorithms::minimum_maximum;

TEST_CASE("minimum returns the smallest element", "[minimum]") {
    SECTION("single element") {
        std::vector<int> values = {42};

        REQUIRE(minimum(values) == 42);
    }

    SECTION("multiple positive integers") {
        std::vector<int> values = {5, 3, 8, 1, 9, 2};

        REQUIRE(minimum(values) == 1);
    }

    SECTION("negative integers") {
        std::vector<int> values = {-3, -10, 4, 0, -7};

        REQUIRE(minimum(values) == -10);
    }

    SECTION("repeated elements") {
        std::vector<int> values = {4, 4, 4, 4};

        REQUIRE(minimum(values) == 4);
    }

    SECTION("double values") {
        std::vector<double> values = {3.5, 1.2, -4.8, 9.1};

        REQUIRE(minimum(values) == -4.8);
    }
}

TEST_CASE("minimum throws when vector is empty", "[minimum]") {
    std::vector<int> values;

    REQUIRE_THROWS_AS(minimum(values), std::invalid_argument);
}

TEST_CASE("maximum returns the largest element", "[maximum]") {
    SECTION("single element") {
        std::vector<int> values = {42};

        REQUIRE(maximum(values) == 42);
    }

    SECTION("multiple positive integers") {
        std::vector<int> values = {5, 3, 8, 1, 9, 2};

        REQUIRE(maximum(values) == 9);
    }

    SECTION("negative integers") {
        std::vector<int> values = {-3, -10, -4, -1, -7};

        REQUIRE(maximum(values) == -1);
    }

    SECTION("repeated elements") {
        std::vector<int> values = {4, 4, 4, 4};

        REQUIRE(maximum(values) == 4);
    }

    SECTION("double values") {
        std::vector<double> values = {3.5, 1.2, -4.8, 9.1};

        REQUIRE(maximum(values) == 9.1);
    }
}

TEST_CASE("maximum throws when vector is empty", "[maximum]") {
    std::vector<int> values;

    REQUIRE_THROWS_AS(maximum(values), std::invalid_argument);
}

TEST_CASE("minimum_maximum returns the smallest and largest elements", "[minimum_maximum]") {
    SECTION("single element") {
        std::vector<int> values = {42};

        REQUIRE(minimum_maximum(values) == std::pair<int, int>{42, 42});
    }

    SECTION("two elements in ascending order") {
        std::vector<int> values = {5, 10};

        REQUIRE(minimum_maximum(values) == std::pair<int, int>{5, 10});
    }

    SECTION("two elements in descending order") {
        std::vector<int> values = {10, 5};

        REQUIRE(minimum_maximum(values) == std::pair<int, int>{5, 10});
    }

    SECTION("odd number of elements") {
        std::vector<int> values = {5, 3, 8, 1, 9};

        REQUIRE(minimum_maximum(values) == std::pair<int, int>{1, 9});
    }

    SECTION("even number of elements") {
        std::vector<int> values = {3, 8, 1, 10};

        REQUIRE(minimum_maximum(values) == std::pair<int, int>{1, 10});
    }

    SECTION("negative integers") {
        std::vector<int> values = {-3, -10, 4, 0, -7};

        REQUIRE(minimum_maximum(values) == std::pair<int, int>{-10, 4});
    }

    SECTION("repeated elements") {
        std::vector<int> values = {4, 4, 4, 4};

        REQUIRE(minimum_maximum(values) == std::pair<int, int>{4, 4});
    }

    SECTION("double values") {
        std::vector<double> values = {3.5, 1.2, -4.8, 9.1};

        REQUIRE(minimum_maximum(values) == std::pair<double, double>{-4.8, 9.1});
    }
}

TEST_CASE("minimum_maximum throws when vector is empty", "[minimum_maximum]") {
    std::vector<int> values;

    REQUIRE_THROWS_AS(minimum_maximum(values), std::invalid_argument);
}