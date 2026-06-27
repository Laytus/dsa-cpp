#include "algorithms/dijkstra.hpp"

#include "data_structures/weighted_adjacency_list_graph.hpp"
#include "algorithms/single_source_shortest_paths.hpp"

#include "data_structures/min_priority_queue.hpp"

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <limits>

namespace dsa::algorithms {

ShortestPathResult dijkstra(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph,
    std::size_t source
) {
    const std::size_t n = graph.vertex_count();

    for (const dsa::data_structures::WeightedDirectedEdge& edge : graph.edges()) {
        if (edge.weight < 0) {
            throw std::invalid_argument("Dijkstra requires non-negative edge weights");
        }
    }
    
    ShortestPathResult result = initialize_single_source(n, source);
    
    dsa::data_structures::MinPriorityQueue queue(n);
    std::vector<bool> in_queue(n, true);

    std::vector<dsa::data_structures::Node> nodes(n);

    for (std::size_t u = 0; u < n; ++u) {
        nodes[u].key = std::numeric_limits<std::size_t>::max();
        nodes[u].data = static_cast<int>(u);
    }

    nodes[source].key = 0;
    
    for (std::size_t u = 0; u < n; ++u) {
        queue.insert(&nodes[u]);
    }

    while (queue.heap_size() > 0) {
        dsa::data_structures::Node* extracted = queue.extract_min();
        const std::size_t u = static_cast<std::size_t>(extracted->data);

        in_queue[u] = false;
        
        for (const dsa::data_structures::AdjacentWeightedEdge& edge : graph.neighbors(u)) {
            const std::size_t v = edge.vertex;

            if (
                in_queue[v] &&
                relax(u, v, edge.weight, result)
            ) {
                queue.decrease_key(
                    &nodes[v],
                    static_cast<std::size_t>(result.distance[v])
                );
            }
        }
    }

    return result;
}

}  // namespace dsa::algorithms