#pragma once

#include "data_structures/adjacency_list_graph.hpp"

#include <cstddef>
#include <vector>
#include <optional>

namespace dsa::algorithms {

enum class BFSColor {
    white,
    gray,
    black
};

struct BFSResult {
    std::vector<BFSColor> color;
    std::vector<int> distance;
    std::vector<std::optional<std::size_t>> parent;
};

BFSResult breadth_first_search(
    const dsa::data_structures::AdjacencyListGraph& graph,
    std::size_t source
);

void build_path(
    const BFSResult& result,
    std::size_t s,
    std::size_t v,
    std::vector<std::size_t>& path
);

}  // namespace dsa::algorithms