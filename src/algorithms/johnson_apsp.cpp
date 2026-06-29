#include "algorithms/johnson_apsp.hpp"

#include "data_structures/weighted_adjacency_list_graph.hpp"
#include "algorithms/bellman_ford.hpp"
#include "algorithms/dijkstra.hpp"
#include "algorithms/single_source_shortest_paths.hpp"

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <limits>

namespace dsa::algorithms {

namespace {

constexpr int INF = std::numeric_limits<int>::max();

}  // namespace

WeightMatrix johnson_asps(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph
) {
    const std::size_t n = graph.vertex_count();

    if (n == 0) {
        return WeightMatrix{};
    }

    /*
        Compute G', where G'.V = G.V U {s},
        G'.E = G.E U {(s, v) : v in G.V}, and
        w(s, v) = 0 for all v in G.V
    */
    dsa::data_structures::WeightedAdjacencyListGraph augmented_graph(n + 1, true);

    for (const dsa::data_structures::WeightedDirectedEdge& edge : graph.edges()) {
        augmented_graph.add_edge(edge.u, edge.v, edge.weight);
    }

    const std::size_t super_source = n;

    for (std::size_t v = 0; v < n; ++v) {
        augmented_graph.add_edge(super_source, v, 0);
    }

    // if Bellman-Ford(G', w, s) == false
    ShortestPathResult bellman_ford_result;

    const bool no_negative_cycle = bellman_ford(augmented_graph, super_source, bellman_ford_result);

    if (!no_negative_cycle) {
        throw std::invalid_argument("Johnson APSP requires a graph with no negative-weight cycles");
    }

    /*
        h[v] = distance from super_source to v
        since super_source has zero-weight edges to every vertex,
        every original vertex is reachable
    */
    const std::vector<int>& h = bellman_ford_result.distance;

    /*
        Reweight every original edge:
            w_hat(u, v) = w(u, v) + h(u) - h(v)
        This makes all edge weights non-negative
    */
    dsa::data_structures::WeightedAdjacencyListGraph reweighted_graph(n, true);

    for (const dsa::data_structures::WeightedDirectedEdge& edge : graph.edges()) {
        const int reweighted = edge.weight + h[edge.u] - h[edge.v];

        if (reweighted < 0) {
            throw std::logic_error("Johnson APSP reweighting produced a negative edge");
        }

        reweighted_graph.add_edge(edge.u, edge.v, reweighted);
    }

    /*
        Run Dijkstra from every vertex on the reweighted graph.
    */
    WeightMatrix distance(n, std::vector<int>(n, INF));

    for (std::size_t u = 0; u < n; ++u) {
        const ShortestPathResult dijkstra_result = dijkstra(reweighted_graph, u);

        for (std::size_t v = 0; v < n; ++v) {
            if (dijkstra_result.distance[v] == INF) {
                distance[u][v] = INF;
            } else {
                distance[u][v] = dijkstra_result.distance[v] + h[v] - h[u];
            }
        }
    }

    return distance;
}

APSPResult johnson_asps_with_predecessor(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph
) {
    const std::size_t n = graph.vertex_count();

    if (n == 0) {
        return APSPResult{WeightMatrix{}, PredecessorMatrix{}};
    }

    /*
        Compute G', where G'.V = G.V U {s},
        G'.E = G.E U {(s, v) : v in G.V}, and
        w(s, v) = 0 for all v in G.V
    */
    dsa::data_structures::WeightedAdjacencyListGraph augmented_graph(n + 1, true);

    for (const dsa::data_structures::WeightedDirectedEdge& edge : graph.edges()) {
        augmented_graph.add_edge(edge.u, edge.v, edge.weight);
    }

    const std::size_t super_source = n;

    for (std::size_t v = 0; v < n; ++v) {
        augmented_graph.add_edge(super_source, v, 0);
    }

    // if Bellman-Ford(G', w, s) == false
    ShortestPathResult bellman_ford_result;

    const bool no_negative_cycle = bellman_ford(augmented_graph, super_source, bellman_ford_result);

    if (!no_negative_cycle) {
        throw std::invalid_argument("Johnson APSP requires a graph with no negative-weight cycles");
    }

    /*
        h[v] = distance from super_source to v
        since super_source has zero-weight edges to every vertex,
        every original vertex is reachable
    */
    const std::vector<int>& h = bellman_ford_result.distance;

    /*
        Reweight every original edge:
            w_hat(u, v) = w(u, v) + h(u) - h(v)
        This makes all edge weights non-negative
    */
    dsa::data_structures::WeightedAdjacencyListGraph reweighted_graph(n, true);

    for (const dsa::data_structures::WeightedDirectedEdge& edge : graph.edges()) {
        const int reweighted = edge.weight + h[edge.u] - h[edge.v];

        if (reweighted < 0) {
            throw std::logic_error("Johnson APSP reweighting produced a negative edge");
        }

        reweighted_graph.add_edge(edge.u, edge.v, reweighted);
    }

    /*
        Run Dijkstra from every vertex on the reweighted graph.
    */
    APSPResult result{
        WeightMatrix(n, std::vector<int>(n, INF)),
        PredecessorMatrix(n, std::vector<std::optional<std::size_t>>(n, std::nullopt))
    };

    for (std::size_t u = 0; u < n; ++u) {
        const ShortestPathResult dijkstra_result = dijkstra(reweighted_graph, u);

        for (std::size_t v = 0; v < n; ++v) {
            if (dijkstra_result.distance[v] == INF) {
                result.distance[u][v] = INF;
            } else {
                result.distance[u][v] = dijkstra_result.distance[v] + h[v] - h[u];
                result.predecessor[u][v] = dijkstra_result.parent[v];
            }
        }
    }

    return result;
}

}  // namespace dsa::algorithms