#include <catch2/catch_test_macros.hpp>

#include "algorithms/depth_first_search.hpp"
#include "data_structures/adjacency_list_graph.hpp"

#include <optional>
#include <vector>

namespace {

using dsa::algorithms::DFSColor;
using dsa::algorithms::DFSResult;
using dsa::algorithms::depth_first_search;
using dsa::data_structures::AdjacencyListGraph;

bool has_valid_times(const DFSResult& result) {
    for (std::size_t u = 0; u < result.d.size(); ++u) {
        if (result.d[u] <= 0 || result.f[u] <= 0) {
            return false;
        }

        if (result.d[u] >= result.f[u]) {
            return false;
        }
    }

    return true;
}

}  // namespace

TEST_CASE("depth_first_search works on an empty graph") {
    AdjacencyListGraph graph(0, false);

    const DFSResult result = depth_first_search(graph);

    REQUIRE(result.color.empty());
    REQUIRE(result.d.empty());
    REQUIRE(result.f.empty());
    REQUIRE(result.parent.empty());
    REQUIRE_FALSE(result.has_cycle);
}

TEST_CASE("depth_first_search works on a single vertex graph") {
    AdjacencyListGraph graph(1, false);

    const DFSResult result = depth_first_search(graph);

    REQUIRE(result.color.size() == 1);
    REQUIRE(result.d.size() == 1);
    REQUIRE(result.f.size() == 1);
    REQUIRE(result.parent.size() == 1);

    REQUIRE(result.color[0] == DFSColor::black);
    REQUIRE(result.d[0] == 1);
    REQUIRE(result.f[0] == 2);
    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE_FALSE(result.has_cycle);
}

TEST_CASE("depth_first_search visits all vertices in a connected undirected graph") {
    AdjacencyListGraph graph(5, false);

    graph.add_edge(0, 1);
    graph.add_edge(0, 4);
    graph.add_edge(1, 4);
    graph.add_edge(1, 3);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);

    const DFSResult result = depth_first_search(graph);

    REQUIRE(result.color.size() == 5);
    REQUIRE(result.d.size() == 5);
    REQUIRE(result.f.size() == 5);
    REQUIRE(result.parent.size() == 5);

    for (DFSColor color : result.color) {
        REQUIRE(color == DFSColor::black);
    }

    REQUIRE(has_valid_times(result));
    REQUIRE(result.has_cycle);
}

TEST_CASE("depth_first_search visits all vertices in a disconnected graph") {
    AdjacencyListGraph graph(6, false);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    graph.add_edge(3, 4);

    const DFSResult result = depth_first_search(graph);

    REQUIRE(result.color.size() == 6);
    REQUIRE(result.d.size() == 6);
    REQUIRE(result.f.size() == 6);
    REQUIRE(result.parent.size() == 6);

    for (DFSColor color : result.color) {
        REQUIRE(color == DFSColor::black);
    }

    REQUIRE(has_valid_times(result));

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[3] == std::nullopt);
    REQUIRE(result.parent[5] == std::nullopt);

    REQUIRE_FALSE(result.has_cycle);
}

TEST_CASE("depth_first_search detects cycle in an undirected graph") {
    AdjacencyListGraph graph(3, false);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    const DFSResult result = depth_first_search(graph);

    REQUIRE(result.has_cycle);

    for (DFSColor color : result.color) {
        REQUIRE(color == DFSColor::black);
    }

    REQUIRE(has_valid_times(result));
}

TEST_CASE("depth_first_search does not report cycle for an undirected tree") {
    AdjacencyListGraph graph(5, false);

    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(1, 4);

    const DFSResult result = depth_first_search(graph);

    REQUIRE_FALSE(result.has_cycle);

    for (DFSColor color : result.color) {
        REQUIRE(color == DFSColor::black);
    }

    REQUIRE(has_valid_times(result));
}

TEST_CASE("depth_first_search detects cycle in a directed graph") {
    AdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    const DFSResult result = depth_first_search(graph);

    REQUIRE(result.has_cycle);

    for (DFSColor color : result.color) {
        REQUIRE(color == DFSColor::black);
    }

    REQUIRE(has_valid_times(result));
}

TEST_CASE("depth_first_search does not report cycle for a directed acyclic graph") {
    AdjacencyListGraph graph(6, true);

    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);
    graph.add_edge(4, 5);

    const DFSResult result = depth_first_search(graph);

    REQUIRE_FALSE(result.has_cycle);

    for (DFSColor color : result.color) {
        REQUIRE(color == DFSColor::black);
    }

    REQUIRE(has_valid_times(result));
}

TEST_CASE("depth_first_search records parent relationships in a directed graph") {
    AdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    const DFSResult result = depth_first_search(graph);

    REQUIRE(result.parent[0] == std::nullopt);
    REQUIRE(result.parent[1].has_value());
    REQUIRE(result.parent[2].has_value());
    REQUIRE(result.parent[3].has_value());

    REQUIRE(result.parent[1].value() == 0);
    REQUIRE(result.parent[2].value() == 1);
    REQUIRE(result.parent[3].value() == 2);

    REQUIRE_FALSE(result.has_cycle);
}

TEST_CASE("depth_first_search handles self-loop as cycle") {
    AdjacencyListGraph graph(2, true);

    graph.add_edge(0, 0);
    graph.add_edge(0, 1);

    const DFSResult result = depth_first_search(graph);

    REQUIRE(result.has_cycle);

    for (DFSColor color : result.color) {
        REQUIRE(color == DFSColor::black);
    }

    REQUIRE(has_valid_times(result));
}

TEST_CASE("depth_first_search discovery and finish times are unique") {
    AdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(2, 3);

    const DFSResult result = depth_first_search(graph);

    std::vector<bool> seen(2 * graph.vertex_count() + 1, false);

    for (std::size_t u = 0; u < graph.vertex_count(); ++u) {
        REQUIRE(result.d[u] > 0);
        REQUIRE(result.f[u] > 0);
        REQUIRE(result.d[u] < result.f[u]);

        REQUIRE_FALSE(seen[static_cast<std::size_t>(result.d[u])]);
        seen[static_cast<std::size_t>(result.d[u])] = true;

        REQUIRE_FALSE(seen[static_cast<std::size_t>(result.f[u])]);
        seen[static_cast<std::size_t>(result.f[u])] = true;
    }
}