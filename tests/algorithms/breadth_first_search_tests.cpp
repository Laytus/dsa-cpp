#include <catch2/catch_test_macros.hpp>

#include "algorithms/breadth_first_search.hpp"
#include "data_structures/adjacency_list_graph.hpp"

#include <optional>
#include <stdexcept>
#include <vector>

namespace {

using dsa::algorithms::BFSColor;
using dsa::algorithms::BFSResult;
using dsa::algorithms::breadth_first_search;
using dsa::algorithms::build_path;
using dsa::data_structures::AdjacencyListGraph;

}  // namespace

TEST_CASE("breadth_first_search works on a single vertex graph") {
    AdjacencyListGraph graph(1, false);

    const BFSResult result = breadth_first_search(graph, 0);

    REQUIRE(result.color.size() == 1);
    REQUIRE(result.distance.size() == 1);
    REQUIRE(result.parent.size() == 1);

    REQUIRE(result.color[0] == BFSColor::black);
    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.parent[0] == std::nullopt);
}

TEST_CASE("breadth_first_search computes distances and parents in an undirected graph") {
    AdjacencyListGraph graph(6, false);

    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(2, 4);
    graph.add_edge(4, 5);

    const BFSResult result = breadth_first_search(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 1);
    REQUIRE(result.distance[2] == 1);
    REQUIRE(result.distance[3] == 2);
    REQUIRE(result.distance[4] == 2);
    REQUIRE(result.distance[5] == 3);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1].has_value());
    REQUIRE(result.parent[2].has_value());
    REQUIRE(result.parent[3].has_value());
    REQUIRE(result.parent[4].has_value());
    REQUIRE(result.parent[5].has_value());

    REQUIRE(result.parent[1].value() == 0);
    REQUIRE(result.parent[2].value() == 0);
    REQUIRE(result.parent[3].value() == 1);
    REQUIRE(result.parent[4].value() == 2);
    REQUIRE(result.parent[5].value() == 4);

    for (BFSColor color : result.color) {
        REQUIRE(color == BFSColor::black);
    }
}

TEST_CASE("breadth_first_search leaves unreachable vertices undiscovered") {
    AdjacencyListGraph graph(6, false);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    graph.add_edge(3, 4);

    const BFSResult result = breadth_first_search(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 1);
    REQUIRE(result.distance[2] == 2);

    REQUIRE(result.color[0] == BFSColor::black);
    REQUIRE(result.color[1] == BFSColor::black);
    REQUIRE(result.color[2] == BFSColor::black);

    REQUIRE(result.distance[3] == -1);
    REQUIRE(result.distance[4] == -1);
    REQUIRE(result.distance[5] == -1);

    REQUIRE(result.color[3] == BFSColor::white);
    REQUIRE(result.color[4] == BFSColor::white);
    REQUIRE(result.color[5] == BFSColor::white);

    REQUIRE(result.parent[3] == std::nullopt);
    REQUIRE(result.parent[4] == std::nullopt);
    REQUIRE(result.parent[5] == std::nullopt);
}

TEST_CASE("breadth_first_search respects edge direction in directed graphs") {
    AdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    const BFSResult from_zero = breadth_first_search(graph, 0);

    REQUIRE(from_zero.distance[0] == 0);
    REQUIRE(from_zero.distance[1] == 1);
    REQUIRE(from_zero.distance[2] == 2);
    REQUIRE(from_zero.distance[3] == -1);

    const BFSResult from_two = breadth_first_search(graph, 2);

    REQUIRE(from_two.distance[2] == 0);
    REQUIRE(from_two.distance[0] == -1);
    REQUIRE(from_two.distance[1] == -1);
    REQUIRE(from_two.distance[3] == -1);
}

TEST_CASE("breadth_first_search throws when source is out of range") {
    AdjacencyListGraph graph(3, false);

    REQUIRE_THROWS_AS(breadth_first_search(graph, 3), std::out_of_range);
}

TEST_CASE("build_path returns the path from source to target") {
    AdjacencyListGraph graph(6, false);

    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(2, 4);
    graph.add_edge(4, 5);

    const BFSResult result = breadth_first_search(graph, 0);

    std::vector<std::size_t> path;
    build_path(result, 0, 5, path);

    const std::vector<std::size_t> expected{0, 2, 4, 5};

    REQUIRE(path == expected);
}

TEST_CASE("build_path returns only the source when source equals target") {
    AdjacencyListGraph graph(3, false);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    const BFSResult result = breadth_first_search(graph, 0);

    std::vector<std::size_t> path;
    build_path(result, 0, 0, path);

    const std::vector<std::size_t> expected{0};

    REQUIRE(path == expected);
}

TEST_CASE("build_path throws if no path exists") {
    AdjacencyListGraph graph(4, false);

    graph.add_edge(0, 1);
    graph.add_edge(2, 3);

    const BFSResult result = breadth_first_search(graph, 0);

    std::vector<std::size_t> path;

    REQUIRE_THROWS_AS(build_path(result, 0, 3, path), std::invalid_argument);
}

TEST_CASE("build_path throws when vertices are out of range") {
    AdjacencyListGraph graph(3, false);

    graph.add_edge(0, 1);

    const BFSResult result = breadth_first_search(graph, 0);

    std::vector<std::size_t> path;

    REQUIRE_THROWS_AS(build_path(result, 0, 3, path), std::out_of_range);
    REQUIRE_THROWS_AS(build_path(result, 3, 0, path), std::out_of_range);
}

TEST_CASE("breadth_first_search works on the five-vertex example graph") {
    AdjacencyListGraph graph(5, false);

    graph.add_edge(0, 1); // 1 -- 2
    graph.add_edge(0, 4); // 1 -- 5
    graph.add_edge(1, 4); // 2 -- 5
    graph.add_edge(1, 3); // 2 -- 4
    graph.add_edge(1, 2); // 2 -- 3
    graph.add_edge(2, 3); // 3 -- 4
    graph.add_edge(3, 4); // 4 -- 5

    const BFSResult result = breadth_first_search(graph, 0);

    REQUIRE(result.distance[0] == 0);
    REQUIRE(result.distance[1] == 1);
    REQUIRE(result.distance[4] == 1);
    REQUIRE(result.distance[2] == 2);
    REQUIRE(result.distance[3] == 2);

    std::vector<std::size_t> path_to_3;
    build_path(result, 0, 2, path_to_3);

    REQUIRE(path_to_3.front() == 0);
    REQUIRE(path_to_3.back() == 2);
    REQUIRE(path_to_3.size() == 3);
}