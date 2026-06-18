#include <catch2/catch_test_macros.hpp>

#include "algorithms/counting_sort.hpp"

#include <vector>

TEST_CASE("counting_sort sorts values in ascending order") {
    std::vector<int> values{2, 5, 3, 0, 2, 3, 0, 3};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        5
    );

    REQUIRE(sorted == std::vector<int>{0, 0, 2, 2, 3, 3, 3, 5});
}

TEST_CASE("counting_sort handles already sorted values") {
    std::vector<int> values{0, 1, 2, 3, 4, 5};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        5
    );

    REQUIRE(sorted == std::vector<int>{0, 1, 2, 3, 4, 5});
}

TEST_CASE("counting_sort handles reverse sorted values") {
    std::vector<int> values{5, 4, 3, 2, 1, 0};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        5
    );

    REQUIRE(sorted == std::vector<int>{0, 1, 2, 3, 4, 5});
}

TEST_CASE("counting_sort handles duplicate values") {
    std::vector<int> values{4, 1, 4, 2, 4, 1, 0};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        4
    );

    REQUIRE(sorted == std::vector<int>{0, 1, 1, 2, 4, 4, 4});
}

TEST_CASE("counting_sort handles repeated equal values") {
    std::vector<int> values{3, 3, 3, 3};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        3
    );

    REQUIRE(sorted == std::vector<int>{3, 3, 3, 3});
}

TEST_CASE("counting_sort handles key zero only") {
    std::vector<int> values{0, 0, 0};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        0
    );

    REQUIRE(sorted == std::vector<int>{0, 0, 0});
}

TEST_CASE("counting_sort handles one element") {
    std::vector<int> values{7};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        7
    );

    REQUIRE(sorted == std::vector<int>{7});
}

TEST_CASE("counting_sort handles empty vector") {
    std::vector<int> values{};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        0
    );

    REQUIRE(sorted.empty());
}

TEST_CASE("counting_sort does not modify the input vector") {
    std::vector<int> values{2, 5, 3, 0, 2, 3, 0, 3};
    const std::vector<int> original = values;

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        5
    );

    REQUIRE(values == original);
    REQUIRE(sorted == std::vector<int>{0, 0, 2, 2, 3, 3, 3, 5});
}

TEST_CASE("counting_sort can sort a prefix of the vector") {
    std::vector<int> values{4, 1, 3, 2, 99, 100};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        4,
        4
    );

    REQUIRE(sorted == std::vector<int>{1, 2, 3, 4});
    REQUIRE(values == std::vector<int>{4, 1, 3, 2, 99, 100});
}

TEST_CASE("counting_sort works when k is larger than the maximum value") {
    std::vector<int> values{2, 0, 1, 2};

    const std::vector<int> sorted = dsa::algorithms::counting_sort(
        values,
        values.size(),
        10
    );

    REQUIRE(sorted == std::vector<int>{0, 1, 2, 2});
}