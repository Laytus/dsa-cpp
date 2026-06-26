#pragma once

#include "data_structures/adjacency_list_graph.hpp"

#include <cstddef>
#include <vector>

namespace dsa::algorithms {

enum class TSColor {
    white,
    gray,
    black
};

std::vector<std::size_t> topological_sort(
    const dsa::data_structures::AdjacencyListGraph& graph
);

}  // namespace dsa::algorithms