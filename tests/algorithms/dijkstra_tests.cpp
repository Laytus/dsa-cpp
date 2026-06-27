#include <catch2/catch_test_macros.hpp>

#include "algorithms/dijkstra.hpp"
#include "algorithms/single_source_shortest_paths.hpp"
#include "data_structures/weighted_adjacency_list_graph.hpp"

#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>

using dsa::algorithms::build_shortest_path;
using dsa::algorithms::dijkstra;
using dsa::algorithms::ShortestPathResult;
using dsa::data_structures::WeightedAdjacencyListGraph;

TEST_CASE("dijkstra computes shortest paths on a directed graph") {
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

    const ShortestPathResult result = dijkstra(graph, 0);

    REQUIRE(result.distance.size() == 5);
    REQUIRE(result.parent.size() == 5);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 7);
    REQUIRE(result.distance[2] == 3);
    REQUIRE(result.distance[3] == 9);
    REQUIRE(result.distance[4] == 5);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == 2);
    REQUIRE(result.parent[2] == 0);
    REQUIRE(result.parent[3] == 1);
    REQUIRE(result.parent[4] == 2);
}

TEST_CASE("dijkstra reconstructs shortest path using parents") {
    WeightedAdjacencyListGraph graph(5, true);

    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 2, 3);
    graph.add_edge(1, 3, 2);
    graph.add_edge(2, 1, 4);
    graph.add_edge(2, 4, 2);
    graph.add_edge(4, 3, 9);

    const ShortestPathResult result = dijkstra(graph, 0);

    const std::vector<std::size_t> path =
        build_shortest_path(result, 0, 3);

    REQUIRE(result.distance[3] == 9);
    REQUIRE(path == std::vector<std::size_t>{0, 2, 1, 3});
}

TEST_CASE("dijkstra works with source different from zero") {
    WeightedAdjacencyListGraph graph(5, true);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 3, 1);
    graph.add_edge(3, 4, 1);
    graph.add_edge(1, 4, 10);

    const ShortestPathResult result = dijkstra(graph, 1);

    REQUIRE(result.distance[0] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[1] == 0);
    REQUIRE(result.distance[2] == 1);
    REQUIRE(result.distance[3] == 2);
    REQUIRE(result.distance[4] == 3);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == std::nullopt);
    REQUIRE(result.parent[2] == 1);
    REQUIRE(result.parent[3] == 2);
    REQUIRE(result.parent[4] == 3);
}

TEST_CASE("dijkstra leaves unreachable vertices at infinity") {
    WeightedAdjacencyListGraph graph(6, true);

    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, 3);
    graph.add_edge(3, 4, 1);
    graph.add_edge(4, 5, 1);

    const ShortestPathResult result = dijkstra(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 2);
    REQUIRE(result.distance[2] == 5);
    REQUIRE(result.distance[3] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[4] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[5] == std::numeric_limits<int>::max());

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == 0);
    REQUIRE(result.parent[2] == 1);
    REQUIRE(result.parent[3] == std::nullopt);
    REQUIRE(result.parent[4] == std::nullopt);
    REQUIRE(result.parent[5] == std::nullopt);
}

TEST_CASE("dijkstra works on graph with one vertex") {
    WeightedAdjacencyListGraph graph(1, true);

    const ShortestPathResult result = dijkstra(graph, 0);

    REQUIRE(result.distance.size() == 1);
    REQUIRE(result.parent.size() == 1);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.parent[0] == std::nullopt);
}

TEST_CASE("dijkstra works on graph with no edges") {
    WeightedAdjacencyListGraph graph(4, true);

    const ShortestPathResult result = dijkstra(graph, 2);

    REQUIRE(result.distance[0] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[1] == std::numeric_limits<int>::max());
    REQUIRE(result.distance[2] == 0);
    REQUIRE(result.distance[3] == std::numeric_limits<int>::max());

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == std::nullopt);
    REQUIRE(result.parent[2] == std::nullopt);
    REQUIRE(result.parent[3] == std::nullopt);
}

TEST_CASE("dijkstra supports zero weight edges") {
    WeightedAdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1, 0);
    graph.add_edge(1, 2, 0);
    graph.add_edge(2, 3, 5);
    graph.add_edge(0, 3, 10);

    const ShortestPathResult result = dijkstra(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 0);
    REQUIRE(result.distance[2] == 0);
    REQUIRE(result.distance[3] == 5);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == 0);
    REQUIRE(result.parent[2] == 1);
    REQUIRE(result.parent[3] == 2);
}

TEST_CASE("dijkstra works on undirected graph with non-negative weights") {
    WeightedAdjacencyListGraph graph(5, false);

    graph.add_edge(0, 1, 4);
    graph.add_edge(0, 2, 1);
    graph.add_edge(2, 1, 2);
    graph.add_edge(1, 3, 1);
    graph.add_edge(2, 3, 5);
    graph.add_edge(3, 4, 3);

    const ShortestPathResult result = dijkstra(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 3);
    REQUIRE(result.distance[2] == 1);
    REQUIRE(result.distance[3] == 4);
    REQUIRE(result.distance[4] == 7);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == 2);
    REQUIRE(result.parent[2] == 0);
    REQUIRE(result.parent[3] == 1);
    REQUIRE(result.parent[4] == 3);
}

TEST_CASE("dijkstra throws when source is out of range") {
    WeightedAdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, 2);

    REQUIRE_THROWS_AS(dijkstra(graph, 3), std::out_of_range);
}

TEST_CASE("dijkstra throws on empty graph") {
    WeightedAdjacencyListGraph graph(0, true);

    REQUIRE_THROWS_AS(dijkstra(graph, 0), std::out_of_range);
}

TEST_CASE("dijkstra throws when graph has negative edge weight") {
    WeightedAdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, -5);

    REQUIRE_THROWS_AS(dijkstra(graph, 0), std::invalid_argument);
}

TEST_CASE("dijkstra chooses shorter indirect path") {
    WeightedAdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1, 100);
    graph.add_edge(0, 2, 1);
    graph.add_edge(2, 1, 1);
    graph.add_edge(1, 3, 1);
    graph.add_edge(2, 3, 10);

    const ShortestPathResult result = dijkstra(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 2);
    REQUIRE(result.distance[2] == 1);
    REQUIRE(result.distance[3] == 3);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1] == 2);
    REQUIRE(result.parent[2] == 0);
    REQUIRE(result.parent[3] == 1);
}