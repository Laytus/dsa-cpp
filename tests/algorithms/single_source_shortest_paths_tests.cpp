#include <catch2/catch_test_macros.hpp>

#include "algorithms/single_source_shortest_paths.hpp"

#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>

using dsa::algorithms::ShortestPathResult;
using dsa::algorithms::build_shortest_path;
using dsa::algorithms::initialize_single_source;
using dsa::algorithms::relax;

TEST_CASE("initialize_single_source initializes distances and parents") {
    const ShortestPathResult result = initialize_single_source(5, 2);

    REQUIRE(result.distance.size() == 5);
    REQUIRE(result.parent.size() == 5);

    REQUIRE(result.distance[0] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[1] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[2] == 0);
    REQUIRE(result.distance[3] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[4] == std::numeric_limits<int>::max());

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == std::nullopt);
    REQUIRE(result.parent[2] == std::nullopt);
    REQUIRE(result.parent[3] == std::nullopt);
    REQUIRE(result.parent[4] == std::nullopt);
}

TEST_CASE("initialize_single_source throws when source is out of range") {
    REQUIRE_THROWS_AS(initialize_single_source(5, 5), std::out_of_range);
}

TEST_CASE("initialize_single_source throws for empty graph") {
    REQUIRE_THROWS_AS(initialize_single_source(0, 0), std::out_of_range);
}

TEST_CASE("relax updates distance and parent when shorter path is found") {
    ShortestPathResult result = initialize_single_source(3, 0);

    const bool updated = relax(0, 1, 7, result);

    REQUIRE(updated);
    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 7);
    REQUIRE(result.parent[1] == 0);
}

TEST_CASE("relax does not update when new path is not shorter") {
    ShortestPathResult result = initialize_single_source(3, 0);

    REQUIRE(relax(0, 1, 5, result));
    REQUIRE_FALSE(relax(0, 1, 8, result));

    REQUIRE(result.distance[1] == 5);
    REQUIRE(result.parent[1] == 0);
}

TEST_CASE("relax updates when new path is shorter") {
    ShortestPathResult result = initialize_single_source(3, 0);

    REQUIRE(relax(0, 1, 10, result));
    REQUIRE(relax(0, 1, 4, result));

    REQUIRE(result.distance[1] == 4);
    REQUIRE(result.parent[1] == 0);
}

TEST_CASE("relax supports negative edge weights") {
    ShortestPathResult result = initialize_single_source(3, 0);

    REQUIRE(relax(0, 1, 5, result));
    REQUIRE(relax(1, 2, -2, result));

    REQUIRE(result.distance[2] == 3);
    REQUIRE(result.parent[2] == 1);
}

TEST_CASE("relax does nothing when source vertex is unreachable") {
    ShortestPathResult result = initialize_single_source(4, 0);

    const bool updated = relax(2, 3, 5, result);

    REQUIRE_FALSE(updated);
    REQUIRE(result.distance[3] == std::numeric_limits<int>::max());
    REQUIRE(result.parent[3] == std::nullopt);
}

TEST_CASE("build_shortest_path returns path from source to target") {
    ShortestPathResult result{
        std::vector<int>{0, 3, 5, 9},
        std::vector<std::optional<std::size_t>>{
            std::nullopt,
            0,
            1,
            2
        }
    };

    const std::vector<std::size_t> path =
        build_shortest_path(result, 0, 3);

    REQUIRE(path == std::vector<std::size_t>{0, 1, 2, 3});
}

TEST_CASE("build_shortest_path works when source equals target") {
    ShortestPathResult result{
        std::vector<int>{0, 4, 9},
        std::vector<std::optional<std::size_t>>{
            std::nullopt,
            0,
            1
        }
    };

    const std::vector<std::size_t> path =
        build_shortest_path(result, 0, 0);

    REQUIRE(path == std::vector<std::size_t>{0});
}

TEST_CASE("build_shortest_path works with direct edge") {
    ShortestPathResult result{
        std::vector<int>{0, 8},
        std::vector<std::optional<std::size_t>>{
            std::nullopt,
            0
        }
    };

    const std::vector<std::size_t> path =
        build_shortest_path(result, 0, 1);

    REQUIRE(path == std::vector<std::size_t>{0, 1});
}

TEST_CASE("build_shortest_path throws when source is out of range") {
    ShortestPathResult result{
        std::vector<int>{0, 1, 2},
        std::vector<std::optional<std::size_t>>{
            std::nullopt,
            0,
            1
        }
    };

    REQUIRE_THROWS_AS(build_shortest_path(result, 3, 2), std::out_of_range);
}

TEST_CASE("build_shortest_path throws when target is out of range") {
    ShortestPathResult result{
        std::vector<int>{0, 1, 2},
        std::vector<std::optional<std::size_t>>{
            std::nullopt,
            0,
            1
        }
    };

    REQUIRE_THROWS_AS(build_shortest_path(result, 0, 3), std::out_of_range);
}

TEST_CASE("build_shortest_path throws when target is unreachable") {
    ShortestPathResult result{
        std::vector<int>{
            0,
            5,
            std::numeric_limits<int>::max()
        },
        std::vector<std::optional<std::size_t>>{
            std::nullopt,
            0,
            std::nullopt
        }
    };

    REQUIRE_THROWS_AS(build_shortest_path(result, 0, 2), std::out_of_range);
}

TEST_CASE("build_shortest_path throws when parent chain is broken") {
    ShortestPathResult result{
        std::vector<int>{0, 5, 9},
        std::vector<std::optional<std::size_t>>{
            std::nullopt,
            std::nullopt,
            1
        }
    };

    REQUIRE_THROWS_AS(build_shortest_path(result, 0, 2), std::invalid_argument);
}