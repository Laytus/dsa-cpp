#include <catch2/catch_test_macros.hpp>

#include "algorithms/selection_sort.hpp"

namespace {

bool is_sorted_ascending(const std::vector<int>& values) {
    for (std::size_t i = 1; i < values.size(); ++i) {
        if (values[i - 1] > values[i]) {
            return false;
        }
    }

    return true;
}

} // namespace

TEST_CASE("selection_sort sorts an unsorted vector") {
    std::vector<int> values{5, 2, 4, 6, 1, 3};

    dsa::algorithms::selection_sort(values);

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("selection_sort keeps an already sorted vector unchanged") {
    std::vector<int> values{1, 2, 3, 4, 5};

    dsa::algorithms::selection_sort(values);

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("selection_sort sorts a reverse-sorted vector") {
    std::vector<int> values{5, 4, 3, 2, 1};

    dsa::algorithms::selection_sort(values);

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5});
}

TEST_CASE("selection_sort works with duplicate values") {
    std::vector<int> values{3, 1, 2, 3, 1, 2};

    dsa::algorithms::selection_sort(values);

    REQUIRE(values == std::vector<int>{1, 1, 2, 2, 3, 3});
}

TEST_CASE("selection_sort works with negative values") {
    std::vector<int> values{4, -1, 0, -5, 3};

    dsa::algorithms::selection_sort(values);

    REQUIRE(values == std::vector<int>{-5, -1, 0, 3, 4});
}

TEST_CASE("selection_sort works with an empty vector") {
    std::vector<int> values{};

    dsa::algorithms::selection_sort(values);

    REQUIRE(values.empty());
}

TEST_CASE("selection_sort works with a single-element vector") {
    std::vector<int> values{42};

    dsa::algorithms::selection_sort(values);

    REQUIRE(values == std::vector<int>{42});
}

TEST_CASE("selection_sort produces sorted output for a larger mixed vector") {
    std::vector<int> values{10, -3, 7, 7, 0, 12, -8, 4, 4, 1};

    dsa::algorithms::selection_sort(values);

    REQUIRE(is_sorted_ascending(values));
    REQUIRE(values == std::vector<int>{-8, -3, 0, 1, 4, 4, 7, 7, 10, 12});
}