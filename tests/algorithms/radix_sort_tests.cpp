#include <catch2/catch_test_macros.hpp>

#include "algorithms/radix_sort.hpp"

#include <stdexcept>
#include <vector>

TEST_CASE("radix_sort sorts CLRS example") {
    std::vector<int> values{329, 457, 657, 839, 436, 720, 355};

    dsa::algorithms::radix_sort(values, values.size(), 3);

    REQUIRE(values == std::vector<int>{329, 355, 436, 457, 657, 720, 839});
}

TEST_CASE("radix_sort sorts values in ascending order") {
    std::vector<int> values{170, 45, 75, 90, 802, 24, 2, 66};

    dsa::algorithms::radix_sort(values, values.size(), 3);

    REQUIRE(values == std::vector<int>{2, 24, 45, 66, 75, 90, 170, 802});
}

TEST_CASE("radix_sort handles already sorted values") {
    std::vector<int> values{1, 2, 3, 4, 5, 6};

    dsa::algorithms::radix_sort(values, values.size(), 1);

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("radix_sort handles reverse sorted values") {
    std::vector<int> values{9, 8, 7, 6, 5, 4, 3, 2, 1};

    dsa::algorithms::radix_sort(values, values.size(), 1);

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
}

TEST_CASE("radix_sort handles duplicate values") {
    std::vector<int> values{12, 5, 12, 3, 5, 99, 3};

    dsa::algorithms::radix_sort(values, values.size(), 2);

    REQUIRE(values == std::vector<int>{3, 3, 5, 5, 12, 12, 99});
}

TEST_CASE("radix_sort handles repeated equal values") {
    std::vector<int> values{42, 42, 42, 42};

    dsa::algorithms::radix_sort(values, values.size(), 2);

    REQUIRE(values == std::vector<int>{42, 42, 42, 42});
}

TEST_CASE("radix_sort handles values with different digit lengths") {
    std::vector<int> values{1, 1000, 10, 100, 0};

    dsa::algorithms::radix_sort(values, values.size(), 4);

    REQUIRE(values == std::vector<int>{0, 1, 10, 100, 1000});
}

TEST_CASE("radix_sort handles zero values") {
    std::vector<int> values{0, 5, 0, 3, 2};

    dsa::algorithms::radix_sort(values, values.size(), 1);

    REQUIRE(values == std::vector<int>{0, 0, 2, 3, 5});
}

TEST_CASE("radix_sort handles one element") {
    std::vector<int> values{123};

    dsa::algorithms::radix_sort(values, values.size(), 3);

    REQUIRE(values == std::vector<int>{123});
}

TEST_CASE("radix_sort handles empty vector") {
    std::vector<int> values{};

    dsa::algorithms::radix_sort(values, values.size(), 0);

    REQUIRE(values.empty());
}

TEST_CASE("radix_sort sorts only the first n values") {
    std::vector<int> values{45, 12, 99, 3, 1000, 2000};

    dsa::algorithms::radix_sort(values, 4, 2);

    REQUIRE(values == std::vector<int>{3, 12, 45, 99, 1000, 2000});
}

TEST_CASE("radix_sort does nothing when d is zero") {
    std::vector<int> values{3, 2, 1};

    dsa::algorithms::radix_sort(values, values.size(), 0);

    REQUIRE(values == std::vector<int>{3, 2, 1});
}

TEST_CASE("radix_sort throws when n is greater than values size") {
    std::vector<int> values{3, 2, 1};

    REQUIRE_THROWS_AS(
        dsa::algorithms::radix_sort(values, values.size() + 1, 1),
        std::invalid_argument
    );
}

TEST_CASE("radix_sort throws when input contains negative values") {
    std::vector<int> values{10, -1, 3};

    REQUIRE_THROWS_AS(
        dsa::algorithms::radix_sort(values, values.size(), 2),
        std::invalid_argument
    );
}