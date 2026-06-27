#include <catch2/catch_test_macros.hpp>

#include "algorithms/bellman_ford.hpp"
#include "data_structures/weighted_adjacency_list_graph.hpp"

#include <limits>
#include <optional>
#include <stdexcept>

TEST_CASE("bellman_ford computes CLRS example shortest paths") {
    // CLRS example:
    //
    // vertices:
    // s = 0
    // t = 1
    // x = 2
    // y = 3
    // z = 4

    dsa::data_structures::WeightedAdjacencyListGraph graph(5);

    graph.add_edge(0, 1, 6);   // s -> t
    graph.add_edge(0, 3, 7);   // s -> y
    graph.add_edge(1, 2, 5);   // t -> x
    graph.add_edge(1, 3, 8);   // t -> y
    graph.add_edge(1, 4, -4);  // t -> z
    graph.add_edge(2, 1, -2);  // x -> t
    graph.add_edge(3, 2, -3);  // y -> x
    graph.add_edge(3, 4, 9);   // y -> z
    graph.add_edge(4, 0, 2);   // z -> s
    graph.add_edge(4, 2, 7);   // z -> x

    dsa::algorithms::ShortestPathResult result;

    const bool has_no_negative_cycle =
        dsa::algorithms::bellman_ford(graph, 0, result);

    REQUIRE(has_no_negative_cycle);

    REQUIRE(result.distance.size() == 5);
    REQUIRE(result.parent.size() == 5);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 2);
    REQUIRE(result.distance[2] == 4);
    REQUIRE(result.distance[3] == 7);
    REQUIRE(result.distance[4] == -2);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1].has_value());
    REQUIRE(result.parent[1].value() == 2);

    REQUIRE(result.parent[2].has_value());
    REQUIRE(result.parent[2].value() == 3);

    REQUIRE(result.parent[3].has_value());
    REQUIRE(result.parent[3].value() == 0);

    REQUIRE(result.parent[4].has_value());
    REQUIRE(result.parent[4].value() == 1);
}

TEST_CASE("bellman_ford works with positive edge weights") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(5);

    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 2, 3);
    graph.add_edge(2, 1, 4);
    graph.add_edge(1, 3, 2);
    graph.add_edge(2, 3, 8);
    graph.add_edge(3, 4, 7);

    dsa::algorithms::ShortestPathResult result;

    const bool has_no_negative_cycle =
        dsa::algorithms::bellman_ford(graph, 0, result);

    REQUIRE(has_no_negative_cycle);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 7);
    REQUIRE(result.distance[2] == 3);
    REQUIRE(result.distance[3] == 9);
    REQUIRE(result.distance[4] == 16);

    REQUIRE(result.parent[0] == std::nullopt);

    REQUIRE(result.parent[1].has_value());
    REQUIRE(result.parent[1].value() == 2);

    REQUIRE(result.parent[2].has_value());
    REQUIRE(result.parent[2].value() == 0);

    REQUIRE(result.parent[3].has_value());
    REQUIRE(result.parent[3].value() == 1);

    REQUIRE(result.parent[4].has_value());
    REQUIRE(result.parent[4].value() == 3);
}

TEST_CASE("bellman_ford supports negative edges without negative cycles") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(4);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, -2);
    graph.add_edge(2, 3, 3);
    graph.add_edge(0, 3, 10);

    dsa::algorithms::ShortestPathResult result;

    const bool has_no_negative_cycle =
        dsa::algorithms::bellman_ford(graph, 0, result);

    REQUIRE(has_no_negative_cycle);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 1);
    REQUIRE(result.distance[2] == -1);
    REQUIRE(result.distance[3] == 2);

    REQUIRE(result.parent[1].has_value());
    REQUIRE(result.parent[1].value() == 0);

    REQUIRE(result.parent[2].has_value());
    REQUIRE(result.parent[2].value() == 1);

    REQUIRE(result.parent[3].has_value());
    REQUIRE(result.parent[3].value() == 2);
}

TEST_CASE("bellman_ford returns false when a reachable negative cycle exists") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(4);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, -1);
    graph.add_edge(2, 3, -1);
    graph.add_edge(3, 1, -1);

    dsa::algorithms::ShortestPathResult result;

    const bool has_no_negative_cycle =
        dsa::algorithms::bellman_ford(graph, 0, result);

    REQUIRE_FALSE(has_no_negative_cycle);
}

TEST_CASE("bellman_ford ignores unreachable negative cycles") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(5);

    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, 3);

    // Unreachable negative cycle from source 0:
    graph.add_edge(3, 4, -10);
    graph.add_edge(4, 3, 1);

    dsa::algorithms::ShortestPathResult result;

    const bool has_no_negative_cycle =
        dsa::algorithms::bellman_ford(graph, 0, result);

    REQUIRE(has_no_negative_cycle);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 2);
    REQUIRE(result.distance[2] == 5);

    REQUIRE(result.distance[3] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[4] == std::numeric_limits<int>::max());

    REQUIRE(result.parent[3] == std::nullopt);
    REQUIRE(result.parent[4] == std::nullopt);
}

TEST_CASE("bellman_ford leaves unreachable vertices at infinity") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(5);

    graph.add_edge(0, 1, 4);
    graph.add_edge(1, 2, 5);
    graph.add_edge(3, 4, 1);

    dsa::algorithms::ShortestPathResult result;

    const bool has_no_negative_cycle =
        dsa::algorithms::bellman_ford(graph, 0, result);

    REQUIRE(has_no_negative_cycle);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 4);
    REQUIRE(result.distance[2] == 9);
    REQUIRE(result.distance[3] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[4] == std::numeric_limits<int>::max());

    REQUIRE(result.parent[0] == std::nullopt);

    REQUIRE(result.parent[1].has_value());
    REQUIRE(result.parent[1].value() == 0);

    REQUIRE(result.parent[2].has_value());
    REQUIRE(result.parent[2].value() == 1);

    REQUIRE(result.parent[3] == std::nullopt);
    REQUIRE(result.parent[4] == std::nullopt);
}

TEST_CASE("bellman_ford works with one vertex") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(1);

    dsa::algorithms::ShortestPathResult result;

    const bool has_no_negative_cycle =
        dsa::algorithms::bellman_ford(graph, 0, result);

    REQUIRE(has_no_negative_cycle);

    REQUIRE(result.distance.size() == 1);
    REQUIRE(result.parent.size() == 1);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.parent[0] == std::nullopt);
}

TEST_CASE("bellman_ford works with graph with no edges") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(4);

    dsa::algorithms::ShortestPathResult result;

    const bool has_no_negative_cycle =
        dsa::algorithms::bellman_ford(graph, 2, result);

    REQUIRE(has_no_negative_cycle);

    REQUIRE(result.distance[0] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[1] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[2] == 0);
    REQUIRE(result.distance[3] == std::numeric_limits<int>::max());

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == std::nullopt);
    REQUIRE(result.parent[2] == std::nullopt);
    REQUIRE(result.parent[3] == std::nullopt);
}

TEST_CASE("bellman_ford throws when source is out of range") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(3);

    dsa::algorithms::ShortestPathResult result;

    REQUIRE_THROWS_AS(
        dsa::algorithms::bellman_ford(graph, 3, result),
        std::out_of_range
    );
}

TEST_CASE("bellman_ford throws when graph has zero vertices") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(0);

    dsa::algorithms::ShortestPathResult result;

    REQUIRE_THROWS_AS(
        dsa::algorithms::bellman_ford(graph, 0, result),
        std::out_of_range
    );
}