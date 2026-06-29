#include <catch2/catch_test_macros.hpp>

#include "algorithms/all_pair_shortest_paths.hpp"
#include "algorithms/johnson_apsp.hpp"
#include "data_structures/weighted_adjacency_list_graph.hpp"

#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>

using dsa::algorithms::APSPResult;
using dsa::algorithms::WeightMatrix;
using dsa::algorithms::build_all_pairs_shortest_path;
using dsa::algorithms::johnson_asps;
using dsa::algorithms::johnson_asps_with_predecessor;
using dsa::data_structures::WeightedAdjacencyListGraph;

namespace {

constexpr int INF = std::numeric_limits<int>::max();

WeightedAdjacencyListGraph clrs_johnson_graph() {
    WeightedAdjacencyListGraph graph(5, true);

    graph.add_edge(0, 1, 3);
    graph.add_edge(0, 2, 8);
    graph.add_edge(0, 4, -4);

    graph.add_edge(1, 3, 1);
    graph.add_edge(1, 4, 7);

    graph.add_edge(2, 1, 4);

    graph.add_edge(3, 0, 2);
    graph.add_edge(3, 2, -5);

    graph.add_edge(4, 3, 6);

    return graph;
}

WeightMatrix clrs_all_pairs_result() {
    return WeightMatrix{
        {0,   1,   -3,  2,   -4},
        {3,   0,   -4,  1,   -1},
        {7,   4,   0,   5,   3},
        {2,   -1,  -5,  0,   -2},
        {8,   5,   1,   6,   0}
    };
}

}  // namespace

TEST_CASE("johnson_asps computes CLRS all-pairs shortest paths") {
    const WeightedAdjacencyListGraph graph = clrs_johnson_graph();

    const WeightMatrix distance = johnson_asps(graph);

    REQUIRE(distance == clrs_all_pairs_result());
}

TEST_CASE("johnson_asps_with_predecessor computes CLRS distances") {
    const WeightedAdjacencyListGraph graph = clrs_johnson_graph();

    const APSPResult result = johnson_asps_with_predecessor(graph);

    REQUIRE(result.distance == clrs_all_pairs_result());
    REQUIRE(result.predecessor.size() == 5);

    for (const auto& row : result.predecessor) {
        REQUIRE(row.size() == 5);
    }
}

TEST_CASE("johnson_asps_with_predecessor reconstructs a shortest path") {
    const WeightedAdjacencyListGraph graph = clrs_johnson_graph();

    const APSPResult result = johnson_asps_with_predecessor(graph);

    const std::vector<std::size_t> path =
        build_all_pairs_shortest_path(result, 0, 2);

    REQUIRE(result.distance[0][2] == -3);
    REQUIRE(path == std::vector<std::size_t>{0, 4, 3, 2});
}

TEST_CASE("johnson_asps_with_predecessor reconstructs another CLRS shortest path") {
    const WeightedAdjacencyListGraph graph = clrs_johnson_graph();

    const APSPResult result = johnson_asps_with_predecessor(graph);

    const std::vector<std::size_t> path =
        build_all_pairs_shortest_path(result, 3, 1);

    REQUIRE(result.distance[3][1] == -1);
    REQUIRE(path == std::vector<std::size_t>{3, 2, 1});
}

TEST_CASE("johnson_asps works with non-negative directed graph") {
    WeightedAdjacencyListGraph graph(5, true);

    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 2, 3);
    graph.add_edge(1, 2, 1);
    graph.add_edge(1, 3, 2);
    graph.add_edge(2, 1, 4);
    graph.add_edge(2, 3, 8);
    graph.add_edge(2, 4, 2);
    graph.add_edge(3, 4, 7);
    graph.add_edge(4, 3, 9);

    const WeightMatrix distance = johnson_asps(graph);

    const WeightMatrix expected{
        {0,   7,   3,   9,   5},
        {INF, 0,   1,   2,   3},
        {INF, 4,   0,   6,   2},
        {INF, INF, INF, 0,   7},
        {INF, INF, INF, 9,   0}
    };

    REQUIRE(distance == expected);
}

TEST_CASE("johnson_asps leaves unreachable vertices at infinity") {
    WeightedAdjacencyListGraph graph(5, true);

    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, 3);
    graph.add_edge(3, 4, 1);

    const WeightMatrix distance = johnson_asps(graph);

    REQUIRE(distance[0][0] == 0);
    REQUIRE(distance[0][1] == 2);
    REQUIRE(distance[0][2] == 5);
    REQUIRE(distance[0][3] == INF);
    REQUIRE(distance[0][4] == INF);

    REQUIRE(distance[3][0] == INF);
    REQUIRE(distance[3][1] == INF);
    REQUIRE(distance[3][2] == INF);
    REQUIRE(distance[3][3] == 0);
    REQUIRE(distance[3][4] == 1);
}

TEST_CASE("johnson_asps works with one vertex") {
    WeightedAdjacencyListGraph graph(1, true);

    const WeightMatrix distance = johnson_asps(graph);

    REQUIRE(distance == WeightMatrix{{0}});
}

TEST_CASE("johnson_asps works with empty graph") {
    WeightedAdjacencyListGraph graph(0, true);

    const WeightMatrix distance = johnson_asps(graph);

    REQUIRE(distance.empty());
}

TEST_CASE("johnson_asps_with_predecessor works with empty graph") {
    WeightedAdjacencyListGraph graph(0, true);

    const APSPResult result = johnson_asps_with_predecessor(graph);

    REQUIRE(result.distance.empty());
    REQUIRE(result.predecessor.empty());
}

TEST_CASE("johnson_asps supports negative edges without negative cycles") {
    WeightedAdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1, 1);
    graph.add_edge(0, 2, 4);
    graph.add_edge(1, 2, -3);
    graph.add_edge(2, 3, 2);

    const WeightMatrix distance = johnson_asps(graph);

    const WeightMatrix expected{
        {0,   1,   -2,  0},
        {INF, 0,   -3,  -1},
        {INF, INF, 0,   2},
        {INF, INF, INF, 0}
    };

    REQUIRE(distance == expected);
}

TEST_CASE("johnson_asps throws with negative-weight cycle") {
    WeightedAdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, -2);
    graph.add_edge(2, 0, -2);

    REQUIRE_THROWS_AS(johnson_asps(graph), std::invalid_argument);
}

TEST_CASE("johnson_asps_with_predecessor throws with negative-weight cycle") {
    WeightedAdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, -2);
    graph.add_edge(2, 0, -2);

    REQUIRE_THROWS_AS(johnson_asps_with_predecessor(graph), std::invalid_argument);
}

TEST_CASE("johnson_asps_with_predecessor returns source when source equals target") {
    const WeightedAdjacencyListGraph graph = clrs_johnson_graph();

    const APSPResult result = johnson_asps_with_predecessor(graph);

    const std::vector<std::size_t> path =
        build_all_pairs_shortest_path(result, 2, 2);

    REQUIRE(path == std::vector<std::size_t>{2});
}

TEST_CASE("johnson_asps_with_predecessor throws when no path exists") {
    WeightedAdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1, 5);

    const APSPResult result = johnson_asps_with_predecessor(graph);

    REQUIRE_THROWS_AS(
        build_all_pairs_shortest_path(result, 2, 0),
        std::invalid_argument
    );
}