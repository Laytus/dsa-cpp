#include "algorithms/bellman_ford.hpp"

#include "data_structures/weighted_adjacency_list_graph.hpp"
#include "algorithms/single_source_shortest_paths.hpp"

#include <cstddef>
#include <stdexcept>
#include <limits>

namespace dsa::algorithms {

bool bellman_ford(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph,
    const std::size_t source,
    dsa::algorithms::ShortestPathResult& result
) {
    const std::size_t n = graph.vertex_count();

    if (source >= n) {
        throw std::out_of_range("source vertex out of range");
    }

    result = dsa::algorithms::initialize_single_source(n, source);

    for (std::size_t i = 1; i < n; ++i) {
        for (const dsa::data_structures::WeightedDirectedEdge& edge : graph.edges()) {
            relax(edge.u, edge.v, edge.weight, result);
        }
    }
    
    for (const dsa::data_structures::WeightedDirectedEdge& edge : graph.edges()) {
        if (result.distance[edge.u] != std::numeric_limits<int>::max() &&
            result.distance[edge.v] > result.distance[edge.u] + edge.weight) {
            return false;
        }
    }

    return true;
}

}  // namespace dsa::algorithms