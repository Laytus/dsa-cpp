#include <print>
#include <cstddef>

#include "algorithms/dijkstra.hpp"
#include "algorithms/single_source_shortest_paths.hpp"
#include "data_structures/weighted_adjacency_list_graph.hpp"

int main() {
    dsa::data_structures::WeightedAdjacencyListGraph graph(5, true);

    graph.add_edge(0, 1, 10);
    graph.add_edge(0, 2, 3);
    graph.add_edge(1, 2, 1);
    graph.add_edge(1, 3, 2);
    graph.add_edge(2, 1, 4);
    graph.add_edge(2, 3, 8);
    graph.add_edge(2, 4, 2);
    graph.add_edge(3, 4, 7);
    graph.add_edge(4, 3, 9);

    const std::size_t source = 0;
    const std::size_t target = 3;

    const dsa::algorithms::ShortestPathResult result = dsa::algorithms::dijkstra(graph, source);

    if (result.distance[target] == std::numeric_limits<int>::max()) {
        std::println("No path exists from {} to {}", source, target);
        return 0;
    }

    const std::vector<std::size_t> path = dsa::algorithms::build_shortest_path(result, source, target);

    std::println(
        "Shortest distance from {} to {}: {}",
        source, target, result.distance[target]
    );

    std::print("Path: ");
    for (std::size_t i = 0; i < path.size(); ++i) {
        std::print("{}", path[i]);
        if (i + 1 < path.size()) {
            std::print(" -> ");
        }
    }
    
    std::println();
}