#include <catch2/catch_test_macros.hpp>

#include "algorithms/insertion_sort_array.hpp"

#include <array>

TEST_CASE("insertion_sort sorts an unsorted std::array") {
    std::array<int, 6> values{5, 2, 4, 6, 1, 3};

    dsa::algorithms::insertion_sort(values);

    REQUIRE(values == std::array<int, 6>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("insertion_sort keeps an already sorted std::array unchanged") {
    std::array<int, 5> values{1, 2, 3, 4, 5};

    dsa::algorithms::insertion_sort(values);

    REQUIRE(values == std::array<int, 5>{1, 2, 3, 4, 5});
}

TEST_CASE("insertion_sort sorts a reverse-sorted std::array") {
    std::array<int, 5> values{5, 4, 3, 2, 1};

    dsa::algorithms::insertion_sort(values);

    REQUIRE(values == std::array<int, 5>{1, 2, 3, 4, 5});
}

TEST_CASE("insertion_sort works with duplicate values in std::array") {
    std::array<int, 6> values{3, 1, 2, 3, 1, 2};

    dsa::algorithms::insertion_sort(values);

    REQUIRE(values == std::array<int, 6>{1, 1, 2, 2, 3, 3});
}

TEST_CASE("insertion_sort works with negative values in std::array") {
    std::array<int, 5> values{4, -1, 0, -5, 3};

    dsa::algorithms::insertion_sort(values);

    REQUIRE(values == std::array<int, 5>{-5, -1, 0, 3, 4});
}

TEST_CASE("insertion_sort works with an empty std::array") {
    std::array<int, 0> values{};

    dsa::algorithms::insertion_sort(values);

    REQUIRE(values.empty());
}

TEST_CASE("insertion_sort works with a single-element std::array") {
    std::array<int, 1> values{42};

    dsa::algorithms::insertion_sort(values);

    REQUIRE(values == std::array<int, 1>{42});
}

TEST_CASE("insertion_sort works with another comparable type") {
    std::array<double, 5> values{3.5, -1.2, 0.0, 8.1, 3.5};

    dsa::algorithms::insertion_sort(values);

    REQUIRE(values == std::array<double, 5>{-1.2, 0.0, 3.5, 3.5, 8.1});
}