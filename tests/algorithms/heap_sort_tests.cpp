#include <catch2/catch_test_macros.hpp>

#include "algorithms/heap_sort.hpp"

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace {

bool is_max_heap_vector(const std::vector<int>& values) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        const std::size_t left = 2 * i + 1;
        const std::size_t right = 2 * i + 2;

        if (left < values.size() && values[i] < values[left]) {
            return false;
        }

        if (right < values.size() && values[i] < values[right]) {
            return false;
        }
    }

    return true;
}

bool is_max_heap_vector_until(
    const std::vector<int>& values,
    std::size_t heap_size
) {
    for (std::size_t i = 0; i < heap_size; ++i) {
        const std::size_t left = 2 * i + 1;
        const std::size_t right = 2 * i + 2;

        if (left < heap_size && values[i] < values[left]) {
            return false;
        }

        if (right < heap_size && values[i] < values[right]) {
            return false;
        }
    }

    return true;
}

bool is_min_heap_vector(const std::vector<int>& values) {
    for (std::size_t i = 0; i < values.size(); ++i) {
        const std::size_t left = 2 * i + 1;
        const std::size_t right = 2 * i + 2;

        if (left < values.size() && values[i] > values[left]) {
            return false;
        }

        if (right < values.size() && values[i] > values[right]) {
            return false;
        }
    }

    return true;
}

bool is_min_heap_vector_until(
    const std::vector<int>& values,
    std::size_t heap_size
) {
    for (std::size_t i = 0; i < heap_size; ++i) {
        const std::size_t left = 2 * i + 1;
        const std::size_t right = 2 * i + 2;

        if (left < heap_size && values[i] > values[left]) {
            return false;
        }

        if (right < heap_size && values[i] > values[right]) {
            return false;
        }
    }

    return true;
}

}  // namespace

TEST_CASE("heap_sort parent computes parent index with zero-based indexing") {
    REQUIRE(dsa::algorithms::parent(1) == 0);
    REQUIRE(dsa::algorithms::parent(2) == 0);
    REQUIRE(dsa::algorithms::parent(3) == 1);
    REQUIRE(dsa::algorithms::parent(4) == 1);
    REQUIRE(dsa::algorithms::parent(5) == 2);
    REQUIRE(dsa::algorithms::parent(6) == 2);
}

TEST_CASE("heap_sort children compute child indices with zero-based indexing") {
    REQUIRE(dsa::algorithms::left_child(0) == 1);
    REQUIRE(dsa::algorithms::right_child(0) == 2);

    REQUIRE(dsa::algorithms::left_child(1) == 3);
    REQUIRE(dsa::algorithms::right_child(1) == 4);

    REQUIRE(dsa::algorithms::left_child(2) == 5);
    REQUIRE(dsa::algorithms::right_child(2) == 6);
}

TEST_CASE("max_heapify restores max heap property at root") {
    std::vector<int> values{4, 14, 10, 2, 8, 9, 3};

    dsa::algorithms::max_heapify(values, values.size(), 0);

    REQUIRE(is_max_heap_vector(values));
    REQUIRE(values[0] == 14);
}

TEST_CASE("max_heapify only affects active heap range") {
    std::vector<int> values{1, 10, 9, 4, 5, 8, 7, 100, 200};

    dsa::algorithms::max_heapify(values, 7, 0);

    REQUIRE(is_max_heap_vector_until(values, 7));

    REQUIRE(values[7] == 100);
    REQUIRE(values[8] == 200);
}

TEST_CASE("min_heapify restores min heap property at root") {
    std::vector<int> values{14, 4, 10, 5, 8, 11, 12};

    dsa::algorithms::min_heapify(values, values.size(), 0);

    REQUIRE(is_min_heap_vector(values));
    REQUIRE(values[0] == 4);
}

TEST_CASE("min_heapify only affects active heap range") {
    std::vector<int> values{10, 1, 2, 4, 5, 8, 7, -100, -200};

    dsa::algorithms::min_heapify(values, 7, 0);

    REQUIRE(is_min_heap_vector_until(values, 7));

    REQUIRE(values[7] == -100);
    REQUIRE(values[8] == -200);
}

TEST_CASE("build_max_heap produces a valid max heap") {
    std::vector<int> values{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    dsa::algorithms::build_max_heap(values);

    REQUIRE(is_max_heap_vector(values));
    REQUIRE(values[0] == 16);
}

TEST_CASE("build_max_heap handles an already valid max heap") {
    std::vector<int> values{100, 50, 90, 20, 40, 80, 70};

    dsa::algorithms::build_max_heap(values);

    REQUIRE(is_max_heap_vector(values));
    REQUIRE(values[0] == 100);
}

TEST_CASE("build_max_heap handles duplicate values") {
    std::vector<int> values{5, 1, 5, 3, 5, 2, 5};

    dsa::algorithms::build_max_heap(values);

    REQUIRE(is_max_heap_vector(values));
    REQUIRE(values[0] == 5);
}

TEST_CASE("build_max_heap handles one element") {
    std::vector<int> values{42};

    dsa::algorithms::build_max_heap(values);

    REQUIRE(values == std::vector<int>{42});
    REQUIRE(is_max_heap_vector(values));
}

TEST_CASE("build_max_heap handles empty vector") {
    std::vector<int> values{};

    dsa::algorithms::build_max_heap(values);

    REQUIRE(values.empty());
}

TEST_CASE("build_min_heap produces a valid min heap") {
    std::vector<int> values{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    dsa::algorithms::build_min_heap(values);

    REQUIRE(is_min_heap_vector(values));
    REQUIRE(values[0] == 1);
}

TEST_CASE("build_min_heap handles an already valid min heap") {
    std::vector<int> values{1, 20, 3, 50, 40, 9, 10};

    dsa::algorithms::build_min_heap(values);

    REQUIRE(is_min_heap_vector(values));
    REQUIRE(values[0] == 1);
}

TEST_CASE("build_min_heap handles duplicate values") {
    std::vector<int> values{5, 1, 5, 3, 5, 2, 5};

    dsa::algorithms::build_min_heap(values);

    REQUIRE(is_min_heap_vector(values));
    REQUIRE(values[0] == 1);
}

TEST_CASE("build_min_heap handles one element") {
    std::vector<int> values{42};

    dsa::algorithms::build_min_heap(values);

    REQUIRE(values == std::vector<int>{42});
    REQUIRE(is_min_heap_vector(values));
}

TEST_CASE("build_min_heap handles empty vector") {
    std::vector<int> values{};

    dsa::algorithms::build_min_heap(values);

    REQUIRE(values.empty());
}

TEST_CASE("heapsort sorts values in ascending order") {
    std::vector<int> values{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    dsa::algorithms::heapsort(values);

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 7, 8, 9, 10, 14, 16});
}

TEST_CASE("heapsort handles already sorted vector") {
    std::vector<int> values{1, 2, 3, 4, 5, 6};

    dsa::algorithms::heapsort(values);

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("heapsort handles reverse sorted vector") {
    std::vector<int> values{6, 5, 4, 3, 2, 1};

    dsa::algorithms::heapsort(values);

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 5, 6});
}

TEST_CASE("heapsort handles duplicate values") {
    std::vector<int> values{3, 1, 2, 3, 1, 2};

    dsa::algorithms::heapsort(values);

    REQUIRE(values == std::vector<int>{1, 1, 2, 2, 3, 3});
}

TEST_CASE("heapsort handles negative values") {
    std::vector<int> values{-1, 5, 0, -10, 8, 3};

    dsa::algorithms::heapsort(values);

    REQUIRE(values == std::vector<int>{-10, -1, 0, 3, 5, 8});
}

TEST_CASE("heapsort handles one element") {
    std::vector<int> values{42};

    dsa::algorithms::heapsort(values);

    REQUIRE(values == std::vector<int>{42});
}

TEST_CASE("heapsort handles empty vector") {
    std::vector<int> values{};

    dsa::algorithms::heapsort(values);

    REQUIRE(values.empty());
}

TEST_CASE("heapsort with max heap sorts values in ascending order") {
    std::vector<int> values{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    dsa::algorithms::heapsort(values, dsa::algorithms::HeapType::max_heap);

    REQUIRE(values == std::vector<int>{1, 2, 3, 4, 7, 8, 9, 10, 14, 16});
}

TEST_CASE("heapsort with min heap sorts values in descending order") {
    std::vector<int> values{4, 1, 3, 2, 16, 9, 10, 14, 8, 7};

    dsa::algorithms::heapsort(values, dsa::algorithms::HeapType::min_heap);

    REQUIRE(values == std::vector<int>{16, 14, 10, 9, 8, 7, 4, 3, 2, 1});
}

TEST_CASE("heapsort with min heap handles already sorted vector") {
    std::vector<int> values{1, 2, 3, 4, 5, 6};

    dsa::algorithms::heapsort(values, dsa::algorithms::HeapType::min_heap);

    REQUIRE(values == std::vector<int>{6, 5, 4, 3, 2, 1});
}

TEST_CASE("heapsort with min heap handles reverse sorted vector") {
    std::vector<int> values{6, 5, 4, 3, 2, 1};

    dsa::algorithms::heapsort(values, dsa::algorithms::HeapType::min_heap);

    REQUIRE(values == std::vector<int>{6, 5, 4, 3, 2, 1});
}

TEST_CASE("heapsort with min heap handles duplicate values") {
    std::vector<int> values{3, 1, 2, 3, 1, 2};

    dsa::algorithms::heapsort(values, dsa::algorithms::HeapType::min_heap);

    REQUIRE(values == std::vector<int>{3, 3, 2, 2, 1, 1});
}

TEST_CASE("heapsort with min heap handles negative values") {
    std::vector<int> values{-1, 5, 0, -10, 8, 3};

    dsa::algorithms::heapsort(values, dsa::algorithms::HeapType::min_heap);

    REQUIRE(values == std::vector<int>{8, 5, 3, 0, -1, -10});
}