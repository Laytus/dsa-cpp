#pragma once

#include <cstddef>
#include <vector>
#include <optional>

namespace dsa::algorithms {

struct ShortestPathResult {
    std::vector<int> distance;
    std::vector<std::optional<std::size_t>> parent;
};

ShortestPathResult initialize_single_source(
    std::size_t vertex_count,
    std::size_t source
);

bool relax(
    std::size_t u,
    std::size_t v,
    int weight,
    ShortestPathResult& result
);

std::vector<std::size_t> build_shortest_path(
    const ShortestPathResult& result,
    std::size_t source,
    std::size_t target
);

}  // namespace dsa::algorithms