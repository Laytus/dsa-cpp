#include <catch2/catch_test_macros.hpp>

#include "algorithms/bucket_sort.hpp"

#include <stdexcept>
#include <vector>

TEST_CASE("bucketsort double sorts CLRS-style values in range 0 <= x < 1") {
    std::vector<double> values{
        0.78, 0.17, 0.39, 0.26, 0.72,
        0.94, 0.21, 0.12, 0.23, 0.68
    };

    const std::vector<double> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<double>{
        0.12, 0.17, 0.21, 0.23, 0.26,
        0.39, 0.68, 0.72, 0.78, 0.94
    });
}

TEST_CASE("bucketsort double handles already sorted values") {
    std::vector<double> values{0.10, 0.20, 0.30, 0.40, 0.50};

    const std::vector<double> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<double>{0.10, 0.20, 0.30, 0.40, 0.50});
}

TEST_CASE("bucketsort double handles reverse sorted values") {
    std::vector<double> values{0.90, 0.70, 0.50, 0.30, 0.10};

    const std::vector<double> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<double>{0.10, 0.30, 0.50, 0.70, 0.90});
}

TEST_CASE("bucketsort double handles duplicate values") {
    std::vector<double> values{0.42, 0.10, 0.42, 0.30, 0.10};

    const std::vector<double> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<double>{0.10, 0.10, 0.30, 0.42, 0.42});
}

TEST_CASE("bucketsort double handles repeated equal values") {
    std::vector<double> values{0.50, 0.50, 0.50, 0.50};

    const std::vector<double> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<double>{0.50, 0.50, 0.50, 0.50});
}

TEST_CASE("bucketsort double handles values near lower and upper bounds") {
    std::vector<double> values{0.0, 0.999, 0.5, 0.001};

    const std::vector<double> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<double>{0.0, 0.001, 0.5, 0.999});
}

TEST_CASE("bucketsort double handles one element") {
    std::vector<double> values{0.37};

    const std::vector<double> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<double>{0.37});
}

TEST_CASE("bucketsort double handles empty vector") {
    std::vector<double> values{};

    const std::vector<double> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted.empty());
}

TEST_CASE("bucketsort double does not modify the input vector") {
    std::vector<double> values{0.78, 0.17, 0.39, 0.26};
    const std::vector<double> original = values;

    const std::vector<double> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(values == original);
    REQUIRE(sorted == std::vector<double>{0.17, 0.26, 0.39, 0.78});
}

TEST_CASE("bucketsort double throws for negative values") {
    std::vector<double> values{0.10, -0.20, 0.30};

    REQUIRE_THROWS_AS(
        dsa::algorithms::bucketsort(values),
        std::invalid_argument
    );
}

TEST_CASE("bucketsort double throws for value equal to one") {
    std::vector<double> values{0.10, 1.0, 0.30};

    REQUIRE_THROWS_AS(
        dsa::algorithms::bucketsort(values),
        std::invalid_argument
    );
}

TEST_CASE("bucketsort double throws for value greater than one") {
    std::vector<double> values{0.10, 1.25, 0.30};

    REQUIRE_THROWS_AS(
        dsa::algorithms::bucketsort(values),
        std::invalid_argument
    );
}

TEST_CASE("bucketsort int sorts values in range 0 <= x < 100") {
    std::vector<int> values{78, 17, 39, 26, 72, 94, 21, 12, 23, 68};

    const std::vector<int> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<int>{12, 17, 21, 23, 26, 39, 68, 72, 78, 94});
}

TEST_CASE("bucketsort int handles already sorted values") {
    std::vector<int> values{0, 10, 20, 30, 40, 50, 99};

    const std::vector<int> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<int>{0, 10, 20, 30, 40, 50, 99});
}

TEST_CASE("bucketsort int handles reverse sorted values") {
    std::vector<int> values{99, 80, 60, 40, 20, 0};

    const std::vector<int> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<int>{0, 20, 40, 60, 80, 99});
}

TEST_CASE("bucketsort int handles duplicate values") {
    std::vector<int> values{42, 10, 42, 30, 10, 99};

    const std::vector<int> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<int>{10, 10, 30, 42, 42, 99});
}

TEST_CASE("bucketsort int handles repeated equal values") {
    std::vector<int> values{50, 50, 50, 50};

    const std::vector<int> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<int>{50, 50, 50, 50});
}

TEST_CASE("bucketsort int handles lower and upper valid bounds") {
    std::vector<int> values{0, 99, 50, 1};

    const std::vector<int> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<int>{0, 1, 50, 99});
}

TEST_CASE("bucketsort int handles one element") {
    std::vector<int> values{37};

    const std::vector<int> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted == std::vector<int>{37});
}

TEST_CASE("bucketsort int handles empty vector") {
    std::vector<int> values{};

    const std::vector<int> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(sorted.empty());
}

TEST_CASE("bucketsort int does not modify the input vector") {
    std::vector<int> values{78, 17, 39, 26};
    const std::vector<int> original = values;

    const std::vector<int> sorted = dsa::algorithms::bucketsort(values);

    REQUIRE(values == original);
    REQUIRE(sorted == std::vector<int>{17, 26, 39, 78});
}

TEST_CASE("bucketsort int throws for negative values") {
    std::vector<int> values{10, -20, 30};

    REQUIRE_THROWS_AS(
        dsa::algorithms::bucketsort(values),
        std::invalid_argument
    );
}

TEST_CASE("bucketsort int throws for value equal to one hundred") {
    std::vector<int> values{10, 100, 30};

    REQUIRE_THROWS_AS(
        dsa::algorithms::bucketsort(values),
        std::invalid_argument
    );
}

TEST_CASE("bucketsort int throws for value greater than one hundred") {
    std::vector<int> values{10, 125, 30};

    REQUIRE_THROWS_AS(
        dsa::algorithms::bucketsort(values),
        std::invalid_argument
    );
}