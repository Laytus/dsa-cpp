#include <catch2/catch_test_macros.hpp>

#include "algorithms/dag_shortest_paths.hpp"
#include "algorithms/single_source_shortest_paths.hpp"
#include "data_structures/weighted_adjacency_list_graph.hpp"

#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>

using dsa::algorithms::dag_shortest_paths;
using dsa::algorithms::ShortestPathResult;
using dsa::data_structures::WeightedAdjacencyListGraph;

TEST_CASE("dag_shortest_paths computes CLRS example distances") {
    WeightedAdjacencyListGraph graph(6, true);

    graph.add_edge(0, 1, 5);
    graph.add_edge(0, 2, 3);
    graph.add_edge(1, 2, 2);
    graph.add_edge(1, 3, 6);
    graph.add_edge(2, 3, 7);
    graph.add_edge(2, 4, 4);
    graph.add_edge(2, 5, 2);
    graph.add_edge(3, 4, -1);
    graph.add_edge(3, 5, 1);
    graph.add_edge(4, 5, -2);

    const ShortestPathResult result = dag_shortest_paths(graph, 1);

    REQUIRE(result.distance.size() == 6);
    REQUIRE(result.parent.size() == 6);

    REQUIRE(result.distance[0] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[1] == 0);
    REQUIRE(result.distance[2] == 2);
    REQUIRE(result.distance[3] == 6);
    REQUIRE(result.distance[4] == 5);
    REQUIRE(result.distance[5] == 3);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == std::nullopt);
    REQUIRE(result.parent[2] == 1);
    REQUIRE(result.parent[3] == 1);
    REQUIRE(result.parent[4] == 3);
    REQUIRE(result.parent[5] == 4);
}

TEST_CASE("dag_shortest_paths works from source zero") {
    WeightedAdjacencyListGraph graph(6, true);

    graph.add_edge(0, 1, 5);
    graph.add_edge(0, 2, 3);
    graph.add_edge(1, 2, 2);
    graph.add_edge(1, 3, 6);
    graph.add_edge(2, 3, 7);
    graph.add_edge(2, 4, 4);
    graph.add_edge(2, 5, 2);
    graph.add_edge(3, 4, -1);
    graph.add_edge(3, 5, 1);
    graph.add_edge(4, 5, -2);

    const ShortestPathResult result = dag_shortest_paths(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 5);
    REQUIRE(result.distance[2] == 3);
    REQUIRE(result.distance[3] == 10);
    REQUIRE(result.distance[4] == 7);
    REQUIRE(result.distance[5] == 5);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == 0);
    REQUIRE(result.parent[2] == 0);
    REQUIRE(result.parent[3] == 2);
    REQUIRE(result.parent[4] == 2);
    REQUIRE(result.parent[5] == 2);
}

TEST_CASE("dag_shortest_paths supports negative edge weights") {
    WeightedAdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1, 1);
    graph.add_edge(0, 2, 4);
    graph.add_edge(1, 2, -3);
    graph.add_edge(2, 3, 2);

    const ShortestPathResult result = dag_shortest_paths(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 1);
    REQUIRE(result.distance[2] == -2);
    REQUIRE(result.distance[3] == 0);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == 0);
    REQUIRE(result.parent[2] == 1);
    REQUIRE(result.parent[3] == 2);
}

TEST_CASE("dag_shortest_paths leaves unreachable vertices at infinity") {
    WeightedAdjacencyListGraph graph(5, true);

    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, 3);
    graph.add_edge(3, 4, 1);

    const ShortestPathResult result = dag_shortest_paths(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 2);
    REQUIRE(result.distance[2] == 5);
    REQUIRE(result.distance[3] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[4] == std::numeric_limits<int>::max());

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == 0);
    REQUIRE(result.parent[2] == 1);
    REQUIRE(result.parent[3] == std::nullopt);
    REQUIRE(result.parent[4] == std::nullopt);
}

TEST_CASE("dag_shortest_paths works with one vertex") {
    WeightedAdjacencyListGraph graph(1, true);

    const ShortestPathResult result = dag_shortest_paths(graph, 0);

    REQUIRE(result.distance.size() == 1);
    REQUIRE(result.parent.size() == 1);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.parent[0] == std::nullopt);
}

TEST_CASE("dag_shortest_paths works with no edges") {
    WeightedAdjacencyListGraph graph(4, true);

    const ShortestPathResult result = dag_shortest_paths(graph, 2);

    REQUIRE(result.distance[0] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[1] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[2] == 0);
    REQUIRE(result.distance[3] == std::numeric_limits<int>::max());

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == std::nullopt);
    REQUIRE(result.parent[2] == std::nullopt);
    REQUIRE(result.parent[3] == std::nullopt);
}

TEST_CASE("dag_shortest_paths throws when source is out of range") {
    WeightedAdjacencyListGraph graph(3, true);

    REQUIRE_THROWS_AS(dag_shortest_paths(graph, 3), std::out_of_range);
}

TEST_CASE("dag_shortest_paths throws with empty graph") {
    WeightedAdjacencyListGraph graph(0, true);

    REQUIRE_THROWS_AS(dag_shortest_paths(graph, 0), std::out_of_range);
}

TEST_CASE("dag_shortest_paths throws when graph is undirected") {
    WeightedAdjacencyListGraph graph(3, false);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, 2);

    REQUIRE_THROWS_AS(dag_shortest_paths(graph, 0), std::invalid_argument);
}

TEST_CASE("dag_shortest_paths throws when graph has a directed cycle") {
    WeightedAdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, 2);
    graph.add_edge(2, 0, 3);

    REQUIRE_THROWS_AS(dag_shortest_paths(graph, 0), std::invalid_argument);
}

TEST_CASE("dag_shortest_paths handles disconnected DAG components") {
    WeightedAdjacencyListGraph graph(6, true);

    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, 2);
    graph.add_edge(3, 4, 5);
    graph.add_edge(4, 5, 5);

    const ShortestPathResult result = dag_shortest_paths(graph, 3);

    REQUIRE(result.distance[0] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[1] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[2] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[3] == 0);
    REQUIRE(result.distance[4] == 5);
    REQUIRE(result.distance[5] == 10);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == std::nullopt);
    REQUIRE(result.parent[2] == std::nullopt);
    REQUIRE(result.parent[3] == std::nullopt);
    REQUIRE(result.parent[4] == 3);
    REQUIRE(result.parent[5] == 4);
}