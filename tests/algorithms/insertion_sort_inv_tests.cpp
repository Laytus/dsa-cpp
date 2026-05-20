#include <catch2/catch_test_macros.hpp>

#include "algorithms/insertion_sort_inv.hpp"

#include <vector>

namespace {

bool is_sorted_descending(const std::vector<int>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        if (values[i - 1] < values[i]) {
            return false;
        }
    }

    return true;
}

} // namespace

TEST_CASE("insertion_sort_inv sorts an unsorted vector") {
    std::vector<int> values{5, 2, 4, 6, 1, 3};

    dsa::algorithms::insertion_sort_inv(values);

    REQUIRE(values == std::vector<int>{6, 5, 4, 3, 2, 1});
}

TEST_CASE("insertion_sort_inv keeps an already sorted vector unchanged") {
    std::vector<int> values{5, 4, 3, 2, 1};

    dsa::algorithms::insertion_sort_inv(values);

    REQUIRE(values == std::vector<int>{5, 4, 3, 2, 1});
}

TEST_CASE("insertion_sort_inv sorts a reverse-sorted vector") {
    std::vector<int> values{1, 2, 3, 4, 5};

    dsa::algorithms::insertion_sort_inv(values);

    REQUIRE(values == std::vector<int>{5, 4, 3, 2, 1});
}

TEST_CASE("insertion_sort_inv works with duplicate values") {
    std::vector<int> values{3, 1, 2, 3, 1, 2};

    dsa::algorithms::insertion_sort_inv(values);

    REQUIRE(values == std::vector<int>{3, 3, 2, 2, 1, 1});
}

TEST_CASE("insertion_sort_inv works with negative values") {
    std::vector<int> values{4, -1, 0, -5, 3};

    dsa::algorithms::insertion_sort_inv(values);

    REQUIRE(values == std::vector<int>{4, 3, 0, -1, -5});
}

TEST_CASE("insertion_sort_inv works with an empty vector") {
    std::vector<int> values{};

    dsa::algorithms::insertion_sort_inv(values);

    REQUIRE(values.empty());
}

TEST_CASE("insertion_sort_inv works with a single-element vector") {
    std::vector<int> values{42};

    dsa::algorithms::insertion_sort_inv(values);

    REQUIRE(values == std::vector<int>{42});
}

TEST_CASE("insertion_sort_inv produces sorted output for a larger mixed vector") {
    std::vector<int> values{10, -3, 7, 7, 0, 12, -8, 4, 4, 1};

    dsa::algorithms::insertion_sort_inv(values);

    REQUIRE(is_sorted_descending(values));
    REQUIRE(values == std::vector<int>{12, 10, 7, 7, 4, 4, 1, 0, -3, -8});
}