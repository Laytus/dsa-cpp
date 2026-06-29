#pragma once

#include "data_structures/weighted_adjacency_list_graph.hpp"

#include <cstddef>
#include <vector>
#include <optional>

namespace dsa::algorithms {

using WeightMatrix = std::vector<std::vector<int>>;
using PredecessorMatrix = std::vector<std::vector<std::optional<std::size_t>>>;
using BoolMatrix = std::vector<std::vector<bool>>;

struct APSPResult {
    WeightMatrix distance;
    PredecessorMatrix predecessor;
};

WeightMatrix extend_shortest_paths(
    const WeightMatrix& L_previous,
    const WeightMatrix& W
);

WeightMatrix slow_APSP(const WeightMatrix& W);

WeightMatrix faster_APSP(const WeightMatrix& W);

WeightMatrix floyd_warshall(const WeightMatrix& W);

APSPResult floyd_warshall_with_predecessors(const WeightMatrix& W);

std::vector<std::size_t> build_all_pairs_shortest_path(
    const APSPResult& result,
    std::size_t source,
    std::size_t target
);

BoolMatrix transitive_closure(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph
);

}  // namespace dsa::algorithms