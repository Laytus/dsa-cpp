#include "algorithms/breadth_first_search.hpp"

#include <optional>
#include <queue>
#include <stdexcept>
#include <vector>
#include <string>

namespace dsa::algorithms {

BFSResult breadth_first_search(
    const dsa::data_structures::AdjacencyListGraph& graph,
    std::size_t source
) {
    const std::size_t n = graph.vertex_count();

    if (source >= n) {
        throw std::out_of_range("source vertex index out of range");
    }

    BFSResult result {
        std::vector<BFSColor>(n, BFSColor::white),
        std::vector<int>(n, -1),
        std::vector<std::optional<std::size_t>>(n, std::nullopt)
    };

    std::queue<std::size_t> queue;

    result.color[source] = BFSColor::gray;
    result.distance[source] = 0;
    result.parent[source] = std::nullopt;

    queue.push(source);

    while (!queue.empty()) {
        const std::size_t u = queue.front();
        queue.pop();

        for (std::size_t v : graph.neighbors(u)) {
            if (result.color[v] == BFSColor::white) {
                result.color[v] = BFSColor::gray;
                result.distance[v] = result.distance[u] + 1;
                result.parent[v] = u;
                queue.push(v);
            }
        }

        result.color[u] = BFSColor::black;
    }

    return result;
}

void build_path(
    const BFSResult& result,
    std::size_t s,
    std::size_t v,
    std::vector<std::size_t>& path
) {
    if (s >= result.parent.size() || v >= result.parent.size()) {
        throw std::out_of_range("vertex index out of range");
    }

    if (s == v) {
        path.push_back(s);
    } else if (result.parent[v] == std::nullopt) {
        throw std::invalid_argument(
            "no path from "
            + std::to_string(s)
            + " to "
            + std::to_string(v)
            + " exists"
        );
    } else {
        build_path(result, s, result.parent[v].value(), path);
        path.push_back(v);
    }
}

}  // namespace dsa::algorithms