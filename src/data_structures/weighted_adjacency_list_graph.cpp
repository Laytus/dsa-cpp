#include "data_structures/weighted_adjacency_list_graph.hpp"

#include <stdexcept>

namespace dsa::data_structures {

WeightedAdjacencyListGraph::WeightedAdjacencyListGraph(
    std::size_t vertex_count,
    bool directed
)
    : adj_(vertex_count),
      directed_(directed) {}

void WeightedAdjacencyListGraph::add_edge(
    std::size_t u,
    std::size_t v,
    int weight
) {
    validate_vertex(u);
    validate_vertex(v);

    adj_[u].push_back(AdjacentWeightedEdge{v, weight});
    edges_.push_back(WeightedDirectedEdge{u, v, weight});
    
    if (!directed_) {
        adj_[v].push_back(AdjacentWeightedEdge{u, weight});
        edges_.push_back(WeightedDirectedEdge{v, u, weight});
    }
}

const std::vector<AdjacentWeightedEdge>& WeightedAdjacencyListGraph::neighbors(
    std::size_t u
) const {
    validate_vertex(u);
    return adj_[u];
}

const std::vector<WeightedDirectedEdge>& WeightedAdjacencyListGraph::edges() const {
    return edges_;
}

std::size_t WeightedAdjacencyListGraph::vertex_count() const {
    return adj_.size();
}

bool WeightedAdjacencyListGraph::directed() const {
    return directed_;
}

void WeightedAdjacencyListGraph::validate_vertex(std::size_t u) const {
    if (u >= adj_.size()) {
        throw std::out_of_range("vertex index out of range");
    }
}

}  // namespace dsa::data_structures