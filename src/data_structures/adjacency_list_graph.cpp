#include "data_structures/adjacency_list_graph.hpp"

#include <stdexcept>

namespace dsa::data_structures {

AdjacencyListGraph::AdjacencyListGraph(
    std::size_t vertex_count,
    bool directed
)
    : adj_(vertex_count),
      directed_(directed) {}

void AdjacencyListGraph::add_edge(std::size_t u, std::size_t v) {
    validate_vertex(u);
    validate_vertex(v);

    adj_[u].push_back(v);

    if (!directed_) {
        adj_[v].push_back(u);
    }
}

const std::vector<std::size_t>& AdjacencyListGraph::neighbors(
    std::size_t u
) const {
    validate_vertex(u);
    return adj_[u];
}

std::size_t AdjacencyListGraph::vertex_count() const {
    return adj_.size();
}

bool AdjacencyListGraph::directed() const {
    return directed_;
}

void AdjacencyListGraph::validate_vertex(std::size_t u) const {
    if (u >= adj_.size()) {
        throw std::out_of_range("vertex index out of range");
    }
}

}  // namespace dsa::data_structures