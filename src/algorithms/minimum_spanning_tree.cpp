#include "algorithms/minimum_spanning_tree.hpp"

#include "data_structures/disjoint_set_forest.hpp"
#include "data_structures/min_priority_queue.hpp"
#include "algorithms/generic_merge_sort.hpp"

#include <cstddef>
#include <vector>
#include <stdexcept>
#include <limits>

namespace dsa::algorithms {

namespace {

// // PROVISIONAL
// void sort_edges_by_weight(std::vector<WeightedEdge>& edges) {
//     for (std::size_t j = 1; j < edges.size(); ++j) {
//         const WeightedEdge key = edges[j];
//         std::size_t i = j;

//         while (i > 0 && edges[i - 1].weight > key.weight) {
//             edges[i] = edges[i - 1];
//             --i;
//         }

//         edges[i] = key;
//     }
// }

struct AdjacentEdge{
    std::size_t vertex;
    int weight;
};

}  // namespace

std::vector<WeightedEdge> mst_kruskal(
    std::size_t vertex_count,
    std::vector<WeightedEdge> edges
) {
    std::vector<WeightedEdge> A;

    if (vertex_count == 0) {
        return A;
    }

    dsa::data_structures::DisjointSetForest forest;

    std::vector<dsa::data_structures::DSFNode*> nodes(vertex_count);

    for (std::size_t v = 0; v < vertex_count; ++v) {
        nodes[v] = forest.make_set(static_cast<int>(v));
    }

    // sort_edges_by_weight(edges);
    dsa::algorithms::generic_merge_sort(
        edges,
        0,
        edges.size(),
        [](const WeightedEdge& a, const WeightedEdge& b) {
            return a.weight < b.weight;
        }
    );

    for (const WeightedEdge& edge : edges) {
        const auto u = edge.u;
        const auto v = edge.v;

        if (u >= vertex_count || v >= vertex_count) {
            throw std::out_of_range("edge vertex index out of range");
        }

        if (forest.find_set(nodes[u]) != forest.find_set(nodes[v])) {
            A.push_back(edge);
            forest.union_sets(nodes[u], nodes[v]);

            if (A.size() == vertex_count - 1) {
                break;
            }
        }
    }

    return A;
}

std::vector<WeightedEdge> mst_prim(
    std::size_t vertex_count,
    const std::vector<WeightedEdge>& edges,
    std::size_t root
) {
    std::vector<WeightedEdge> A;

    if (vertex_count == 0) {
        return A;
    }

    if (root >= vertex_count) {
        throw std::invalid_argument("root vertex index out of range");
    }
    
    std::vector<std::vector<AdjacentEdge>> adj(vertex_count);

    for (const WeightedEdge& edge : edges) {
        const auto u = edge.u;
        const auto v = edge.v;

        if (u >= vertex_count || v >= vertex_count) {
            throw std::out_of_range("edge vertex index out of range");
        }

        if (edge.weight < 0) {
            throw std::invalid_argument("mst_prim requires non-negative edge weights with the current priority queue");
        }

        adj[u].push_back(AdjacentEdge{v, edge.weight});
        adj[v].push_back(AdjacentEdge{u, edge.weight});
    }

    std::vector<dsa::data_structures::Node> nodes(vertex_count);
    std::vector<bool> in_queue(vertex_count, true);
    std::vector<std::size_t> parent(vertex_count, vertex_count);

    for (std::size_t u = 0; u < vertex_count; ++u) {
        nodes[u].key = std::numeric_limits<std::size_t>::max();
        nodes[u].data = static_cast<int>(u);
    }
    
    nodes[root].key = 0;
    
    dsa::data_structures::MinPriorityQueue queue(vertex_count);
    
    for (std::size_t u = 0; u < vertex_count; ++u) {
        queue.insert(&nodes[u]);
    }

    while (queue.heap_size() > 0) {
        dsa::data_structures::Node* extracted = queue.extract_min();
        const std::size_t u = static_cast<std::size_t>(extracted->data);

        in_queue[u] = false;

        if (parent[u] != vertex_count) {
            A.push_back(WeightedEdge{
                parent[u],
                u,
                static_cast<int>(nodes[u].key)
            });
        }

        for (const AdjacentEdge& edge : adj[u]) {
            const std::size_t v = edge.vertex;
            const std::size_t weight = static_cast<std::size_t>(edge.weight);

            if (in_queue[v] && weight < nodes[v].key) {
                parent[v] = u;
                queue.decrease_key(&nodes[v], weight);
            }
        }
    }

    return A;
}

}  // namespace dsa::algorithms