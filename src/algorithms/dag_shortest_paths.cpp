#include "algorithms/dag_shortest_paths.hpp"

#include "data_structures/adjacency_list_graph.hpp"
#include "algorithms/topological_sort.hpp"

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace dsa::algorithms {

ShortestPathResult dag_shortest_paths(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph,
    std::size_t source
) {
    const std::size_t n = graph.vertex_count();

    if (source >= n) {
        throw std::out_of_range("source vertex index out of range");
    }

    if (!graph.directed()) {
        throw std::invalid_argument("DAG shortest paths requires a directed graph");
    }

    // Topological sort the vertices of G 
    dsa::data_structures::AdjacencyListGraph unweighted_graph(n, true);

    for (const dsa::data_structures::WeightedDirectedEdge& edge : graph.edges()) {
        unweighted_graph.add_edge(edge.u, edge.v);
    }

    const std::vector<std::size_t> order = dsa::algorithms::topological_sort(unweighted_graph);

    // Initialize single source
    ShortestPathResult result = initialize_single_source(n, source);

    // Relax each vertex in topologically sorted order
    for (std::size_t u : order) {
        for (const dsa::data_structures::AdjacentWeightedEdge& edge : graph.neighbors(u)) {
            relax(u, edge.vertex, edge.weight, result);
        }
    }

    return result;
}

}  // namespace dsa::algorithms