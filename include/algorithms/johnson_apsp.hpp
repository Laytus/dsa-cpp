#pragma once

#include "data_structures/weighted_adjacency_list_graph.hpp"
#include "algorithms/all_pair_shortest_paths.hpp"

namespace dsa::algorithms {

WeightMatrix johnson_asps(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph
);

APSPResult johnson_asps_with_predecessor(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph
);

}  // namespace dsa::algorithms