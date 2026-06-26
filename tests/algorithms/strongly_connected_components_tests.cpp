#include <catch2/catch_test_macros.hpp>

#include "algorithms/strongly_connected_components.hpp"
#include "data_structures/adjacency_list_graph.hpp"

#include <stdexcept>
#include <vector>

namespace {

using dsa::algorithms::strongly_connected_components;
using dsa::data_structures::AdjacencyListGraph;

bool contains_vertex(
    const std::vector<std::size_t>& component,
    std::size_t vertex
) {
    for (std::size_t u : component) {
        if (u == vertex) {
            return true;
        }
    }

    return false;
}

bool component_matches(
    const std::vector<std::size_t>& component,
    const std::vector<std::size_t>& expected
) {
    if (component.size() != expected.size()) {
        return false;
    }

    for (std::size_t u : expected) {
        if (!contains_vertex(component, u)) {
            return false;
        }
    }

    return true;
}

bool has_component(
    const std::vector<std::vector<std::size_t>>& components,
    const std::vector<std::size_t>& expected
) {
    for (const std::vector<std::size_t>& component : components) {
        if (component_matches(component, expected)) {
            return true;
        }
    }

    return false;
}

bool appears_once(
    const std::vector<std::vector<std::size_t>>& components,
    std::size_t vertex
) {
    int count = 0;

    for (const std::vector<std::size_t>& component : components) {
        for (std::size_t u : component) {
            if (u == vertex) {
                ++count;
            }
        }
    }

    return count == 1;
}

}  // namespace

TEST_CASE("strongly_connected_components works on an empty directed graph") {
    AdjacencyListGraph graph(0, true);

    const std::vector<std::vector<std::size_t>> components =
        strongly_connected_components(graph);

    REQUIRE(components.empty());
}

TEST_CASE("strongly_connected_components works on a single vertex graph") {
    AdjacencyListGraph graph(1, true);

    const std::vector<std::vector<std::size_t>> components =
        strongly_connected_components(graph);

    REQUIRE(components.size() == 1);
    REQUIRE(has_component(components, std::vector<std::size_t>{0}));
}

TEST_CASE("strongly_connected_components returns singleton components for a DAG") {
    AdjacencyListGraph graph(5, true);

    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);

    const std::vector<std::vector<std::size_t>> components =
        strongly_connected_components(graph);

    REQUIRE(components.size() == 5);

    REQUIRE(has_component(components, std::vector<std::size_t>{0}));
    REQUIRE(has_component(components, std::vector<std::size_t>{1}));
    REQUIRE(has_component(components, std::vector<std::size_t>{2}));
    REQUIRE(has_component(components, std::vector<std::size_t>{3}));
    REQUIRE(has_component(components, std::vector<std::size_t>{4}));
}

TEST_CASE("strongly_connected_components returns one component for a directed cycle") {
    AdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    const std::vector<std::vector<std::size_t>> components =
        strongly_connected_components(graph);

    REQUIRE(components.size() == 1);
    REQUIRE(has_component(components, std::vector<std::size_t>{0, 1, 2}));
}

TEST_CASE("strongly_connected_components handles multiple components") {
    AdjacencyListGraph graph(6, true);

    graph.add_edge(0, 1);
    graph.add_edge(1, 0);

    graph.add_edge(2, 3);
    graph.add_edge(3, 2);

    graph.add_edge(4, 5);
    graph.add_edge(5, 4);

    graph.add_edge(1, 2);
    graph.add_edge(3, 4);

    const std::vector<std::vector<std::size_t>> components =
        strongly_connected_components(graph);

    REQUIRE(components.size() == 3);

    REQUIRE(has_component(components, std::vector<std::size_t>{0, 1}));
    REQUIRE(has_component(components, std::vector<std::size_t>{2, 3}));
    REQUIRE(has_component(components, std::vector<std::size_t>{4, 5}));
}

TEST_CASE("strongly_connected_components handles CLRS-style example") {
    AdjacencyListGraph graph(8, true);

    // 0: a
    // 1: b
    // 2: c
    // 3: d
    // 4: e
    // 5: f
    // 6: g
    // 7: h

    graph.add_edge(0, 1); // a -> b

    graph.add_edge(1, 2); // b -> c
    graph.add_edge(1, 4); // b -> e
    graph.add_edge(1, 5); // b -> f

    graph.add_edge(2, 3); // c -> d
    graph.add_edge(2, 6); // c -> g

    graph.add_edge(3, 2); // d -> c
    graph.add_edge(3, 7); // d -> h

    graph.add_edge(4, 0); // e -> a
    graph.add_edge(4, 5); // e -> f

    graph.add_edge(5, 6); // f -> g

    graph.add_edge(6, 5); // g -> f
    graph.add_edge(6, 7); // g -> h

    graph.add_edge(7, 7); // h -> h

    const std::vector<std::vector<std::size_t>> components =
        strongly_connected_components(graph);

    REQUIRE(components.size() == 4);

    REQUIRE(has_component(components, std::vector<std::size_t>{0, 1, 4}));
    REQUIRE(has_component(components, std::vector<std::size_t>{2, 3}));
    REQUIRE(has_component(components, std::vector<std::size_t>{5, 6}));
    REQUIRE(has_component(components, std::vector<std::size_t>{7}));
}

TEST_CASE("strongly_connected_components handles self-loop as one component") {
    AdjacencyListGraph graph(3, true);

    graph.add_edge(0, 0);
    graph.add_edge(1, 2);

    const std::vector<std::vector<std::size_t>> components =
        strongly_connected_components(graph);

    REQUIRE(components.size() == 3);

    REQUIRE(has_component(components, std::vector<std::size_t>{0}));
    REQUIRE(has_component(components, std::vector<std::size_t>{1}));
    REQUIRE(has_component(components, std::vector<std::size_t>{2}));
}

TEST_CASE("strongly_connected_components returns every vertex exactly once") {
    AdjacencyListGraph graph(7, true);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    graph.add_edge(3, 4);
    graph.add_edge(4, 3);

    graph.add_edge(5, 6);

    const std::vector<std::vector<std::size_t>> components =
        strongly_connected_components(graph);

    for (std::size_t u = 0; u < graph.vertex_count(); ++u) {
        REQUIRE(appears_once(components, u));
    }
}

TEST_CASE("strongly_connected_components throws for undirected graph") {
    AdjacencyListGraph graph(3, false);

    graph.add_edge(0, 1);
    graph.add_edge(1, 2);

    REQUIRE_THROWS_AS(
        strongly_connected_components(graph),
        std::invalid_argument
    );
}