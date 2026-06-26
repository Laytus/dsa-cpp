#pragma once

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

struct WeightedEdge {
    std::size_t u;
    std::size_t v;
    int weight;
};

std::vector<WeightedEdge> mst_kruskal(
    std::size_t vertex_count,
    std::vector<WeightedEdge> edges
);

std::vector<WeightedEdge> mst_prim(
    std::size_t vertex_count,
    const std::vector<WeightedEdge>& edges,
    std::size_t root
);

}  // namespace dsa::algorithms