#pragma once

#include "data_structures/adjacency_list_graph.hpp"

#include <cstddef>
#include <vector>
#include <optional>

namespace dsa::algorithms {

enum class DFSColor {
    white,
    gray,
    black
};

struct DFSResult {
    std::vector<DFSColor> color;
    std::vector<int> d;
    std::vector<int> f;
    std::vector<std::optional<std::size_t>> parent;
    bool has_cycle;
};

DFSResult depth_first_search(
    const dsa::data_structures::AdjacencyListGraph& graph
);

// void depth_first_search_visit(
//     const dsa::data_structures::AdjacencyListGraph& graph,
//     int& time,
//     std::size_t u,
//     DFSResult& result
// );

}  // namespace dsa::algorithms