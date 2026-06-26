#include "algorithms/topological_sort.hpp"

#include <stdexcept>

namespace dsa::algorithms {

namespace {

void topological_sort_visit(
    const dsa::data_structures::AdjacencyListGraph& graph,
    std::size_t u,
    std::vector<TSColor>& color,
    std::vector<std::size_t>& order,
    std::size_t& write_position,
    bool& has_cycle
) {
    color[u] = TSColor::gray;

    for (std::size_t v : graph.neighbors(u)) {
        if (color[v] == TSColor::white) {
            topological_sort_visit(
                graph, 
                v, 
                color,
                order,
                write_position,
                has_cycle
            );
        } else if (color[v] == TSColor::gray) {
            has_cycle = true;
        }
    }

    color[u] = TSColor::black;

    --write_position;
    order[write_position] = u;
}

}  // namespace

std::vector<std::size_t> topological_sort(
    const dsa::data_structures::AdjacencyListGraph& graph
) {
    if (!graph.directed()) {
        throw std::invalid_argument("topological sort requires a directed graph");
    }

    const std::size_t n = graph.vertex_count();

    std::vector<TSColor> color(n, TSColor::white);
    std::vector<std::size_t> order(n);

    std::size_t write_position = n;
    bool has_cycle = false;

    for (std::size_t u = 0; u < n; ++u) {
        if (color[u] == TSColor::white) {
            topological_sort_visit(
                graph,
                u,
                color,
                order,
                write_position,
                has_cycle
            );
        }
    }

    if (has_cycle) {
        throw std::invalid_argument("topological sort requires an acyclic graph");
    }

    return order;
}

}  // namespace dsa::algorithms