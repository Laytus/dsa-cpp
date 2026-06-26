#pragma once

#include <cstddef>
#include <vector>

namespace dsa::data_structures {

class AdjacencyListGraph {
public:
    explicit AdjacencyListGraph(
        std::size_t vertex_count,
        bool directed = false
    );

    void add_edge(std::size_t u, std::size_t v);

    const std::vector<std::size_t>& neighbors(std::size_t u) const;

    std::size_t vertex_count() const;

    bool directed() const;

private:
    void validate_vertex(std::size_t u) const;
    
    std::vector<std::vector<std::size_t>> adj_;
    bool directed_;
};

}  // namespace dsa::data_structures