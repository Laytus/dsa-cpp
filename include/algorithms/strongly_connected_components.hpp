#pragma once

#include "data_structures/adjacency_list_graph.hpp"

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

dsa::data_structures::AdjacencyListGraph transpose_graph(
    const dsa::data_structures::AdjacencyListGraph& graph
);

std::vector<std::vector<std::size_t>> strongly_connected_components(
    const dsa::data_structures::AdjacencyListGraph& graph
);

}  // namespace dsa::algorithms