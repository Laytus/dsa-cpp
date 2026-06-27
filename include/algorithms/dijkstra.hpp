#pragma once

#include "data_structures/weighted_adjacency_list_graph.hpp"
#include "algorithms/single_source_shortest_paths.hpp"

#include <cstddef>

namespace dsa::algorithms {

ShortestPathResult dijkstra(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph,
    std::size_t source
);

}  // namespace dsa::algorithms