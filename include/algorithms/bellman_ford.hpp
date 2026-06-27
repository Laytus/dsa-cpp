#pragma once

#include "data_structures/weighted_adjacency_list_graph.hpp"
#include "algorithms/single_source_shortest_paths.hpp"

#include <cstddef>

namespace dsa::algorithms {

bool bellman_ford(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph,
    const std::size_t source,
    dsa::algorithms::ShortestPathResult& result
);

}  // namespace dsa::algorithms