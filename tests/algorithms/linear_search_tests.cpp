#include <catch2/catch_test_macros.hpp>

#include "algorithms/linear_search.hpp"

#include <optional>
#include <vector>

TEST_CASE("linear_search finds a value at the beginning") {
    std::vector<int> values{10, 20, 30, 40};

    const auto result = dsa::algorithms::linear_search(values, 10);

    REQUIRE(result == std::optional<std::size_t>{0});
}

TEST_CASE("linear_search finds a value in the middle") {
    std::vector<int> values{10, 20, 30, 40};

    const auto result = dsa::algorithms::linear_search(values, 30);

    REQUIRE(result == std::optional<std::size_t>{2});
}

TEST_CASE("linear_search finds a value at the end") {
    std::vector<int> values{10, 20, 30, 40};

    const auto result = dsa::algorithms::linear_search(values, 40);

    REQUIRE(result == std::optional<std::size_t>{3});
}

TEST_CASE("linear_search returns nullopt when the value does not exist") {
    std::vector<int> values{10, 20, 30, 40};

    const auto result = dsa::algorithms::linear_search(values, 99);

    REQUIRE(result == std::nullopt);
}

TEST_CASE("linear_search returns nullopt for an empty vector") {
    std::vector<int> values{};

    const auto result = dsa::algorithms::linear_search(values, 10);

    REQUIRE(result == std::nullopt);
}

TEST_CASE("linear_search works with negative values") {
    std::vector<int> values{-5, -2, 0, 3, 8};

    const auto result = dsa::algorithms::linear_search(values, -2);

    REQUIRE(result == std::optional<std::size_t>{1});
}

TEST_CASE("linear_search returns the first matching index when duplicates exist") {
    std::vector<int> values{4, 7, 2, 7, 9};

    const auto result = dsa::algorithms::linear_search(values, 7);

    REQUIRE(result == std::optional<std::size_t>{1});
}

TEST_CASE("linear_search works with a single-element vector when value exists") {
    std::vector<int> values{42};

    const auto result = dsa::algorithms::linear_search(values, 42);

    REQUIRE(result == std::optional<std::size_t>{0});
}

TEST_CASE("linear_search works with a single-element vector when value does not exist") {
    std::vector<int> values{42};

    const auto result = dsa::algorithms::linear_search(values, 7);

    REQUIRE(result == std::nullopt);
}