#pragma once

#include <cstddef>
#include <vector>

namespace dsa::data_structures {

struct WeightedDirectedEdge {
    std::size_t u;
    std::size_t v;
    int weight;
};

struct AdjacentWeightedEdge {
    std::size_t vertex;
    int weight;
};

class WeightedAdjacencyListGraph {
public:
    explicit WeightedAdjacencyListGraph(
        std::size_t vertex_count,
        bool directed = true
    );

    void add_edge(std::size_t u, std::size_t v, int weight);

    const std::vector<AdjacentWeightedEdge>& neighbors(std::size_t u) const;
    const std::vector<WeightedDirectedEdge>& edges() const;

    std::size_t vertex_count() const;
    bool directed() const;

private:
    void validate_vertex(std::size_t u) const;
    
    std::vector<std::vector<AdjacentWeightedEdge>> adj_;
    std::vector<WeightedDirectedEdge> edges_;
    bool directed_;
};

}  // namespace dsa::data_structures