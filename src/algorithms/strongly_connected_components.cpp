#include "algorithms/strongly_connected_components.hpp"

#include "data_structures/adjacency_list_graph.hpp"

#include <cstddef>
#include <vector>
#include <stdexcept>

namespace dsa::algorithms {

namespace {

void collect_finish_order_dfs(
    const dsa::data_structures::AdjacencyListGraph& graph,
    std::size_t u,
    std::vector<bool>& visited,
    std::vector<std::size_t>& finish_order
) {
    visited[u] = true;

    for (std::size_t v : graph.neighbors(u)) {
        if (!visited[v]) {
            collect_finish_order_dfs(graph, v, visited, finish_order);
        }
    }

    finish_order.push_back(u);
}

void collect_component_dfs(
    const dsa::data_structures::AdjacencyListGraph& graph,
    std::size_t u,
    std::vector<bool>& visited,
    std::vector<std::size_t>& component
) {
    visited[u] = true;
    component.push_back(u);

    for (std::size_t v : graph.neighbors(u)) {
        if (!visited[v]) {
            collect_component_dfs(graph, v, visited, component);
        }
    }
}

}  // namespace

dsa::data_structures::AdjacencyListGraph transpose_graph(
    const dsa::data_structures::AdjacencyListGraph& graph
) {
    dsa::data_structures::AdjacencyListGraph transposed(
        graph.vertex_count(),
        true
    );

    for (std::size_t u = 0; u < graph.vertex_count(); ++u) {
        for (std::size_t v : graph.neighbors(u)) {
            transposed.add_edge(v, u);
        }
    }

    return transposed;
}

std::vector<std::vector<std::size_t>> strongly_connected_components(
    const dsa::data_structures::AdjacencyListGraph& graph
) {
    if (!graph.directed()) {
        throw std::invalid_argument("strongly connected components require a directed graph");
    }

    const std::size_t n = graph.vertex_count();

    // Call DFS(G) to compute finish times u.f for each vertex u
    std::vector<bool> visited(n, false);
    std::vector<std::size_t> finish_order;
    finish_order.reserve(n);

    for (std::size_t u = 0; u < n; ++u) {
        if (!visited[u]) {
            collect_finish_order_dfs(graph, u, visited, finish_order);
        }
    }

    // Create G^T
    const dsa::data_structures::AdjacencyListGraph transposed = transpose_graph(graph);
    
    // Call DFS(G^T), but in the main loop of DFS, consider the vertices
    //      in order of decreasing u.f (as computed in line 1)
    std::vector<bool> transposed_visited(n, false);
    std::vector<std::vector<std::size_t>> components;

    for (std::size_t i = finish_order.size(); i > 0; --i) {
        const std::size_t u = finish_order[i - 1];

        if (!transposed_visited[u]) {
            std::vector<std::size_t> component;
            collect_component_dfs(
                transposed,
                u,
                transposed_visited,
                component
            );

            components.push_back(component);
        }
    }

    // Output the vertices of each tree in the depth-first forest formed 
    //      in line 3 as a separate strongly connected component

    return components;
}

}  // namespace dsa::algorithms