#include <catch2/catch_test_macros.hpp>

#include "data_structures/weighted_adjacency_list_graph.hpp"

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace {

bool contains_adjacent_edge(
    const std::vector<dsa::data_structures::AdjacentWeightedEdge>& neighbors,
    std::size_t vertex,
    int weight
) {
    for (const dsa::data_structures::AdjacentWeightedEdge& edge : neighbors) {
        if (edge.vertex == vertex && edge.weight == weight) {
            return true;
        }
    }

    return false;
}

bool contains_directed_edge(
    const std::vector<dsa::data_structures::WeightedDirectedEdge>& edges,
    std::size_t u,
    std::size_t v,
    int weight
) {
    for (const dsa::data_structures::WeightedDirectedEdge& edge : edges) {
        if (edge.u == u && edge.v == v && edge.weight == weight) {
            return true;
        }
    }

    return false;
}

}  // namespace

TEST_CASE("WeightedAdjacencyListGraph constructor creates directed graph by default") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(5);

    REQUIRE(graph.vertex_count() == 5);
    REQUIRE(graph.directed());

    for (std::size_t u = 0; u < graph.vertex_count(); ++u) {
        REQUIRE(graph.neighbors(u).empty());
    }

    REQUIRE(graph.edges().empty());
}

TEST_CASE("WeightedAdjacencyListGraph constructor creates undirected graph") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(5, false);

    REQUIRE(graph.vertex_count() == 5);
    REQUIRE_FALSE(graph.directed());

    for (std::size_t u = 0; u < graph.vertex_count(); ++u) {
        REQUIRE(graph.neighbors(u).empty());
    }

    REQUIRE(graph.edges().empty());
}

TEST_CASE("WeightedAdjacencyListGraph supports zero vertices") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(0);

    REQUIRE(graph.vertex_count() == 0);
    REQUIRE(graph.edges().empty());
}

TEST_CASE("WeightedAdjacencyListGraph add_edge stores directed edge") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(3);

    graph.add_edge(0, 1, 7);

    REQUIRE(graph.edges().size() == 1);
    REQUIRE(contains_directed_edge(graph.edges(), 0, 1, 7));

    REQUIRE(graph.neighbors(0).size() == 1);
    REQUIRE(contains_adjacent_edge(graph.neighbors(0), 1, 7));

    REQUIRE(graph.neighbors(1).empty());
    REQUIRE(graph.neighbors(2).empty());
}

TEST_CASE("WeightedAdjacencyListGraph add_edge stores multiple directed edges") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(4);

    graph.add_edge(0, 1, 5);
    graph.add_edge(0, 2, 3);
    graph.add_edge(2, 3, 8);

    REQUIRE(graph.edges().size() == 3);

    REQUIRE(contains_directed_edge(graph.edges(), 0, 1, 5));
    REQUIRE(contains_directed_edge(graph.edges(), 0, 2, 3));
    REQUIRE(contains_directed_edge(graph.edges(), 2, 3, 8));

    REQUIRE(graph.neighbors(0).size() == 2);
    REQUIRE(contains_adjacent_edge(graph.neighbors(0), 1, 5));
    REQUIRE(contains_adjacent_edge(graph.neighbors(0), 2, 3));

    REQUIRE(graph.neighbors(1).empty());

    REQUIRE(graph.neighbors(2).size() == 1);
    REQUIRE(contains_adjacent_edge(graph.neighbors(2), 3, 8));

    REQUIRE(graph.neighbors(3).empty());
}

TEST_CASE("WeightedAdjacencyListGraph add_edge stores undirected edge in both directions") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(3, false);

    graph.add_edge(0, 1, 7);

    REQUIRE(graph.edges().size() == 2);
    REQUIRE(contains_directed_edge(graph.edges(), 0, 1, 7));
    REQUIRE(contains_directed_edge(graph.edges(), 1, 0, 7));

    REQUIRE(graph.neighbors(0).size() == 1);
    REQUIRE(graph.neighbors(1).size() == 1);
    REQUIRE(graph.neighbors(2).empty());

    REQUIRE(contains_adjacent_edge(graph.neighbors(0), 1, 7));
    REQUIRE(contains_adjacent_edge(graph.neighbors(1), 0, 7));
}

TEST_CASE("WeightedAdjacencyListGraph add_edge stores multiple undirected edges") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(4, false);

    graph.add_edge(0, 1, 5);
    graph.add_edge(0, 2, 3);
    graph.add_edge(2, 3, 8);

    REQUIRE(graph.edges().size() == 6);

    REQUIRE(contains_directed_edge(graph.edges(), 0, 1, 5));
    REQUIRE(contains_directed_edge(graph.edges(), 1, 0, 5));

    REQUIRE(contains_directed_edge(graph.edges(), 0, 2, 3));
    REQUIRE(contains_directed_edge(graph.edges(), 2, 0, 3));

    REQUIRE(contains_directed_edge(graph.edges(), 2, 3, 8));
    REQUIRE(contains_directed_edge(graph.edges(), 3, 2, 8));

    REQUIRE(graph.neighbors(0).size() == 2);
    REQUIRE(contains_adjacent_edge(graph.neighbors(0), 1, 5));
    REQUIRE(contains_adjacent_edge(graph.neighbors(0), 2, 3));

    REQUIRE(graph.neighbors(1).size() == 1);
    REQUIRE(contains_adjacent_edge(graph.neighbors(1), 0, 5));

    REQUIRE(graph.neighbors(2).size() == 2);
    REQUIRE(contains_adjacent_edge(graph.neighbors(2), 0, 3));
    REQUIRE(contains_adjacent_edge(graph.neighbors(2), 3, 8));

    REQUIRE(graph.neighbors(3).size() == 1);
    REQUIRE(contains_adjacent_edge(graph.neighbors(3), 2, 8));
}

TEST_CASE("WeightedAdjacencyListGraph supports negative edge weights") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(3);

    graph.add_edge(0, 1, -4);
    graph.add_edge(1, 2, 10);

    REQUIRE(graph.edges().size() == 2);

    REQUIRE(contains_directed_edge(graph.edges(), 0, 1, -4));
    REQUIRE(contains_directed_edge(graph.edges(), 1, 2, 10));

    REQUIRE(contains_adjacent_edge(graph.neighbors(0), 1, -4));
    REQUIRE(contains_adjacent_edge(graph.neighbors(1), 2, 10));
}

TEST_CASE("WeightedAdjacencyListGraph supports zero edge weights") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(2);

    graph.add_edge(0, 1, 0);

    REQUIRE(graph.edges().size() == 1);
    REQUIRE(contains_directed_edge(graph.edges(), 0, 1, 0));
    REQUIRE(contains_adjacent_edge(graph.neighbors(0), 1, 0));
}

TEST_CASE("WeightedAdjacencyListGraph supports self loops") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(2);

    graph.add_edge(1, 1, 9);

    REQUIRE(graph.edges().size() == 1);
    REQUIRE(contains_directed_edge(graph.edges(), 1, 1, 9));

    REQUIRE(graph.neighbors(0).empty());
    REQUIRE(graph.neighbors(1).size() == 1);
    REQUIRE(contains_adjacent_edge(graph.neighbors(1), 1, 9));
}

TEST_CASE("WeightedAdjacencyListGraph directed self loop is stored once") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(2);

    graph.add_edge(1, 1, 9);

    REQUIRE(graph.edges().size() == 1);
    REQUIRE(graph.neighbors(1).size() == 1);
}

TEST_CASE("WeightedAdjacencyListGraph undirected self loop is stored twice") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(2, false);

    graph.add_edge(1, 1, 9);

    REQUIRE(graph.edges().size() == 2);
    REQUIRE(graph.neighbors(1).size() == 2);

    REQUIRE(contains_directed_edge(graph.edges(), 1, 1, 9));
    REQUIRE(contains_adjacent_edge(graph.neighbors(1), 1, 9));
}

TEST_CASE("WeightedAdjacencyListGraph add_edge throws when source vertex is invalid") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(3);

    REQUIRE_THROWS_AS(
        graph.add_edge(3, 1, 7),
        std::out_of_range
    );
}

TEST_CASE("WeightedAdjacencyListGraph add_edge throws when target vertex is invalid") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(3);

    REQUIRE_THROWS_AS(
        graph.add_edge(1, 3, 7),
        std::out_of_range
    );
}

TEST_CASE("WeightedAdjacencyListGraph add_edge does not mutate graph when source is invalid") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(3);

    REQUIRE_THROWS_AS(
        graph.add_edge(3, 1, 7),
        std::out_of_range
    );

    REQUIRE(graph.edges().empty());

    for (std::size_t u = 0; u < graph.vertex_count(); ++u) {
        REQUIRE(graph.neighbors(u).empty());
    }
}

TEST_CASE("WeightedAdjacencyListGraph add_edge does not mutate graph when target is invalid") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(3);

    REQUIRE_THROWS_AS(
        graph.add_edge(1, 3, 7),
        std::out_of_range
    );

    REQUIRE(graph.edges().empty());

    for (std::size_t u = 0; u < graph.vertex_count(); ++u) {
        REQUIRE(graph.neighbors(u).empty());
    }
}

TEST_CASE("WeightedAdjacencyListGraph neighbors throws when vertex is invalid") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(3);

    REQUIRE_THROWS_AS(
        graph.neighbors(3),
        std::out_of_range
    );
}

TEST_CASE("WeightedAdjacencyListGraph edges returns all inserted directed edges in insertion order") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(4);

    graph.add_edge(0, 1, 5);
    graph.add_edge(2, 3, 8);
    graph.add_edge(1, 2, -2);

    const auto& edges = graph.edges();

    REQUIRE(edges.size() == 3);

    REQUIRE(edges[0].u == 0);
    REQUIRE(edges[0].v == 1);
    REQUIRE(edges[0].weight == 5);

    REQUIRE(edges[1].u == 2);
    REQUIRE(edges[1].v == 3);
    REQUIRE(edges[1].weight == 8);

    REQUIRE(edges[2].u == 1);
    REQUIRE(edges[2].v == 2);
    REQUIRE(edges[2].weight == -2);
}

TEST_CASE("WeightedAdjacencyListGraph neighbors returns outgoing edges in insertion order") {
    dsa::data_structures::WeightedAdjacencyListGraph graph(4);

    graph.add_edge(0, 1, 5);
    graph.add_edge(0, 2, 3);
    graph.add_edge(0, 3, 9);

    const auto& neighbors = graph.neighbors(0);

    REQUIRE(neighbors.size() == 3);

    REQUIRE(neighbors[0].vertex == 1);
    REQUIRE(neighbors[0].weight == 5);

    REQUIRE(neighbors[1].vertex == 2);
    REQUIRE(neighbors[1].weight == 3);

    REQUIRE(neighbors[2].vertex == 3);
    REQUIRE(neighbors[2].weight == 9);
}