#include <catch2/catch_test_macros.hpp>

#include "algorithms/quick_sort.hpp"

#include <vector>

TEST_CASE("partition places pivot in its final sorted position") {
    std::vector<int> values{2, 8, 7, 1, 3, 5, 6, 4};

    const std::size_t pivot_index = dsa::algorithms::partition(
        values,
        0,
        values.size()
    );

    REQUIRE(pivot_index == 3);
    REQUIRE(values[pivot_index] == 4);

    for (std::size_t i = 0; i < pivot_index; ++i) {
        REQUIRE(values[i] <= values[pivot_index]);
    }

    for (std::size_t i = pivot_index + 1; i < values.size(); ++i) {
        REQUIRE(values[i] > values[pivot_index]);
    }
}

TEST_CASE("partition works with already partitioned values") {
    std::vector<int> values{1, 2, 3, 4, 5};

    const std::size_t pivot_index = dsa::algorithms::partition(
        values,
        0,
        values.size()
    );

    REQUIRE(pivot_index == 4);
    REQUIRE(values[pivot_index] == 5);

    for (std::size_t i = 0; i < pivot_index; ++i) {
        REQUIRE(values[i] <= values[pivot_index]);
    }
}

TEST_CASE("partition works when pivot is the smallest value") {
    std::vector<int> values{5, 4, 3, 2, 1};

    const std::size_t pivot_index = dsa::algorithms::partition(
        values,
        0,
        values.size()
    );

    REQUIRE(pivot_index == 0);
    REQUIRE(values[pivot_index] == 1);

    for (std::size_t i = pivot_index + 1; i < values.size(); ++i) {
        REQUIRE(values[i] > values[pivot_index]);
    }
}

TEST_CASE("randomized_partition places pivot in its final sorted position") {
    std::vector<int> values{2, 8, 7, 1, 3, 5, 6, 4};

    const std::size_t pivot_index = dsa::algorithms::randomized_partition(
        values,
        0,
        values.size()
    );

    const int pivot = values[pivot_index];

    for (std::size_t i = 0; i < pivot_index; ++i) {
        REQUIRE(values[i] <= pivot);
    }

    for (std::size_t i = pivot_index + 1; i < values.size(); ++i) {
        REQUIRE(values[i] > pivot);
    }
}

TEST_CASE("randomized_partition works on a selected subrange") {
    std::vector<int> values{100, 9, 3, 7, 1, 5, 200};

    const std::size_t pivot_index = dsa::algorithms::randomized_partition(
        values,
        1,
        6
    );

    const int pivot = values[pivot_index];

    REQUIRE(values[0] == 100);
    REQUIRE(values[6] == 200);
    REQUIRE(pivot_index >= 1);
    REQUIRE(pivot_index < 6);

    for (std::size_t i = 1; i < pivot_index; ++i) {
        REQUIRE(values[i] <= pivot);
    }

    for (std::size_t i = pivot_index + 1; i < 6; ++i) {
        REQUIRE(values[i] > pivot);
    }
}

TEST_CASE("randomized_partition handles repeated equal values") {
    std::vector<int> values{5, 5, 5, 5, 5};

    const std::size_t pivot_index = dsa::algorithms::randomized_partition(
        values,
        0,
        values.size()
    );

    REQUIRE(pivot_index == values.size() - 1);
    REQUIRE(values == std::vector<int>{5, 5, 5, 5, 5});
}

TEST_CASE("quicksort sorts values in ascending order") {
    std::vector<int> values{2, 8, 7, 1, 3, 5, 6, 4};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
}

TEST_CASE("quicksort handles already sorted vector") {
    std::vector<int> values{1, 2, 3, 4, 5, 6};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("quicksort handles reverse sorted vector") {
    std::vector<int> values{6, 5, 4, 3, 2, 1};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("quicksort handles duplicate values") {
    std::vector<int> values{3, 1, 2, 3, 1, 2};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 1, 2, 2, 3, 3});
}

TEST_CASE("quicksort handles negative values") {
    std::vector<int> values{-1, 5, 0, -10, 8, 3};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{-10, -1, 0, 3, 5, 8});
}

TEST_CASE("quicksort handles one element") {
    std::vector<int> values{42};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{42});
}

TEST_CASE("quicksort handles empty vector") {
    std::vector<int> values{};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values.empty());
}

TEST_CASE("quicksort handles two elements already sorted") {
    std::vector<int> values{1, 2};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 2});
}

TEST_CASE("quicksort handles two elements reverse sorted") {
    std::vector<int> values{2, 1};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 2});
}

TEST_CASE("quicksort handles repeated equal values") {
    std::vector<int> values{5, 5, 5, 5, 5};

    dsa::algorithms::quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{5, 5, 5, 5, 5});
}

TEST_CASE("quicksort sorts only the selected subrange") {
    std::vector<int> values{100, 4, 3, 2, 1, 200};

    dsa::algorithms::quicksort(values, 1, 5);

    REQUIRE(values == std::vector<int>{100, 1, 2, 3, 4, 200});
}

TEST_CASE("randomized_quicksort sorts values in ascending order") {
    std::vector<int> values{2, 8, 7, 1, 3, 5, 6, 4};

    dsa::algorithms::randomized_quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8});
}

TEST_CASE("randomized_quicksort handles already sorted vector") {
    std::vector<int> values{1, 2, 3, 4, 5, 6};

    dsa::algorithms::randomized_quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("randomized_quicksort handles reverse sorted vector") {
    std::vector<int> values{6, 5, 4, 3, 2, 1};

    dsa::algorithms::randomized_quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("randomized_quicksort handles duplicate values") {
    std::vector<int> values{3, 1, 2, 3, 1, 2};

    dsa::algorithms::randomized_quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{1, 1, 2, 2, 3, 3});
}

TEST_CASE("randomized_quicksort handles negative values") {
    std::vector<int> values{-1, 5, 0, -10, 8, 3};

    dsa::algorithms::randomized_quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{-10, -1, 0, 3, 5, 8});
}

TEST_CASE("randomized_quicksort handles one element") {
    std::vector<int> values{42};

    dsa::algorithms::randomized_quicksort(values, 0, values.size());

    REQUIRE(values == std::vector<int>{42});
}

TEST_CASE("randomized_quicksort handles empty vector") {
    std::vector<int> values{};

    dsa::algorithms::randomized_quicksort(values, 0, values.size());

    REQUIRE(values.empty());
}

TEST_CASE("randomized_quicksort sorts only the selected subrange") {
    std::vector<int> values{100, 4, 3, 2, 1, 200};

    dsa::algorithms::randomized_quicksort(values, 1, 5);

    REQUIRE(values == std::vector<int>{100, 1, 2, 3, 4, 200});
}