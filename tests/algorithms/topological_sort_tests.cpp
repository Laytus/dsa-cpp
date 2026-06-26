#include <catch2/catch_test_macros.hpp>

#include "algorithms/topological_sort.hpp"
#include "data_structures/adjacency_list_graph.hpp"

#include <stdexcept>
#include <vector>

namespace {

using dsa::algorithms::topological_sort;
using dsa::data_structures::AdjacencyListGraph;

bool appears_before(
    const std::vector<std::size_t>& order,
    std::size_t u,
    std::size_t v
) {
    std::size_t u_position = order.size();
    std::size_t v_position = order.size();

    for (std::size_t i = 0; i < order.size(); ++i) {
        if (order[i] == u) {
            u_position = i;
        }

        if (order[i] == v) {
            v_position = i;
        }
    }

    return u_position < v_position;
}

bool is_valid_topological_order(
    const AdjacencyListGraph& graph,
    const std::vector<std::size_t>& order
) {
    if (order.size() != graph.vertex_count()) {
        return false;
    }

    std::vector<bool> seen(graph.vertex_count(), false);

    for (std::size_t u : order) {
        if (u >= graph.vertex_count()) {
            return false;
        }

        if (seen[u]) {
            return false;
        }

        seen[u] = true;
    }

    for (std::size_t u = 0; u < graph.vertex_count(); ++u) {
        for (std::size_t v : graph.neighbors(u)) {
            if (!appears_before(order, u, v)) {
                return false;
            }
        }
    }

    return true;
}

}  // namespace

TEST_CASE("topological_sort works on an empty directed graph") {
    AdjacencyListGraph graph(0, true);

    const std::vector<std::size_t> order = topological_sort(graph);

    REQUIRE(order.empty());
}

TEST_CASE("topological_sort works on a single vertex directed graph") {
    AdjacencyListGraph graph(1, true);

    const std::vector<std::size_t> order = topological_sort(graph);

    const std::vector<std::size_t> expected{0};

    REQUIRE(order == expected);
}

TEST_CASE("topological_sort works on a simple chain DAG") {
    AdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    const std::vector<std::size_t> order = topological_sort(graph);

    const std::vector<std::size_t> expected{0, 1, 2, 3};

    REQUIRE(order == expected);
    REQUIRE(is_valid_topological_order(graph, order));
}

TEST_CASE("topological_sort works on a branching DAG") {
    AdjacencyListGraph graph(6, true);

    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);
    graph.add_edge(3, 5);

    const std::vector<std::size_t> order = topological_sort(graph);

    REQUIRE(is_valid_topological_order(graph, order));

    REQUIRE(appears_before(order, 0, 1));
    REQUIRE(appears_before(order, 0, 2));
    REQUIRE(appears_before(order, 1, 3));
    REQUIRE(appears_before(order, 2, 3));
    REQUIRE(appears_before(order, 3, 4));
    REQUIRE(appears_before(order, 3, 5));
}

TEST_CASE("topological_sort works on disconnected DAG") {
    AdjacencyListGraph graph(6, true);

    graph.add_edge(0, 1);
    graph.add_edge(2, 3);
    graph.add_edge(4, 5);

    const std::vector<std::size_t> order = topological_sort(graph);

    REQUIRE(is_valid_topological_order(graph, order));

    REQUIRE(appears_before(order, 0, 1));
    REQUIRE(appears_before(order, 2, 3));
    REQUIRE(appears_before(order, 4, 5));
}

TEST_CASE("topological_sort works on CLRS-style clothing example") {
    AdjacencyListGraph graph(9, true);

    // 0: undershorts
    // 1: pants
    // 2: belt
    // 3: shirt
    // 4: tie
    // 5: jacket
    // 6: socks
    // 7: shoes
    // 8: watch

    graph.add_edge(0, 1); // undershorts -> pants
    graph.add_edge(0, 7); // undershorts -> shoes
    graph.add_edge(1, 2); // pants -> belt
    graph.add_edge(1, 7); // pants -> shoes
    graph.add_edge(2, 5); // belt -> jacket
    graph.add_edge(3, 2); // shirt -> belt
    graph.add_edge(3, 4); // shirt -> tie
    graph.add_edge(4, 5); // tie -> jacket
    graph.add_edge(6, 7); // socks -> shoes

    const std::vector<std::size_t> order = topological_sort(graph);

    REQUIRE(is_valid_topological_order(graph, order));

    REQUIRE(appears_before(order, 0, 1));
    REQUIRE(appears_before(order, 0, 7));
    REQUIRE(appears_before(order, 1, 2));
    REQUIRE(appears_before(order, 1, 7));
    REQUIRE(appears_before(order, 2, 5));
    REQUIRE(appears_before(order, 3, 2));
    REQUIRE(appears_before(order, 3, 4));
    REQUIRE(appears_before(order, 4, 5));
    REQUIRE(appears_before(order, 6, 7));
}

TEST_CASE("topological_sort throws for undirected graph") {
    AdjacencyListGraph graph(3, false);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    REQUIRE_THROWS_AS(topological_sort(graph), std::invalid_argument);
}

TEST_CASE("topological_sort throws for directed graph with cycle") {
    AdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    REQUIRE_THROWS_AS(topological_sort(graph), std::invalid_argument);
}

TEST_CASE("topological_sort throws for directed graph with self-loop") {
    AdjacencyListGraph graph(2, true);

    graph.add_edge(0, 0);
    graph.add_edge(0, 1);

    REQUIRE_THROWS_AS(topological_sort(graph), std::invalid_argument);
}

TEST_CASE("topological_sort returns every vertex exactly once") {
    AdjacencyListGraph graph(5, true);

    graph.add_edge(0, 2);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);
    graph.add_edge(2, 4);

    const std::vector<std::size_t> order = topological_sort(graph);

    REQUIRE(order.size() == graph.vertex_count());

    std::vector<bool> seen(graph.vertex_count(), false);

    for (std::size_t u : order) {
        REQUIRE(u < graph.vertex_count());
        REQUIRE_FALSE(seen[u]);
        seen[u] = true;
    }

    for (bool was_seen : seen) {
        REQUIRE(was_seen);
    }
}