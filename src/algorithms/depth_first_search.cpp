#include "algorithms/depth_first_search.hpp"

namespace dsa::algorithms {

namespace {

void depth_first_search_visit(
    const dsa::data_structures::AdjacencyListGraph& graph,
    int& time,
    std::size_t u,
    DFSResult& result
) {
    ++time;
    result.d[u] = time;
    result.color[u] = DFSColor::gray;

    for (std::size_t v : graph.neighbors(u)) {
        if (result.color[v] == DFSColor::white) {
            result.parent[v] = u;
            depth_first_search_visit(graph, time, v, result);
        } else if (result.color[v] == DFSColor::gray) {
            const bool is_parent_edge = result.parent[u].has_value() && result.parent[u].value() == v;

            if (graph.directed() || !is_parent_edge) {
                result.has_cycle = true;
            }
        }
    }

    ++time;
    result.f[u] = time;
    result.color[u] = DFSColor::black;
}

}  // namespace

DFSResult depth_first_search(
    const dsa::data_structures::AdjacencyListGraph& graph
) {
    const std::size_t n = graph.vertex_count();

    DFSResult result {
        std::vector<DFSColor>(n, DFSColor::white),
        std::vector<int>(n, -1),
        std::vector<int>(n, -1),
        std::vector<std::optional<std::size_t>>(n, std::nullopt),
        false
    };

    int time = 0;

    for (std::size_t u = 0; u < n; ++u) {
        if (result.color[u] == DFSColor::white) {
            depth_first_search_visit(graph, time, u, result);
        }
    }

    return result;
}

}  // namespace dsa::algorithms