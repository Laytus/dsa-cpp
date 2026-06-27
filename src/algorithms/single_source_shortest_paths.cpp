#include "algorithms/single_source_shortest_paths.hpp"

#include <cstddef>
#include <vector>
#include <optional>
#include <stdexcept>
#include <limits>

namespace dsa::algorithms {

ShortestPathResult initialize_single_source(
    std::size_t vertex_count,
    std::size_t source
) {
    if (source >= vertex_count) {
        throw std::out_of_range("source vertex index out of range");
    }

    ShortestPathResult result{
        std::vector<int>(vertex_count, std::numeric_limits<int>::max()),
        std::vector<std::optional<std::size_t>>(vertex_count, std::nullopt)
    };

    result.distance[source] = 0;

    return result;
}

bool relax(
    std::size_t u,
    std::size_t v,
    int weight,
    ShortestPathResult& result
) {
    if (result.distance[u] == std::numeric_limits<int>::max()) {
        return false;
    }

    const int candidate = result.distance[u] + weight;

    if (result.distance[v] > candidate) {
        result.distance[v] = candidate;
        result.parent[v] = u;
        
        return true;
    }

    return false;
}

std::vector<std::size_t> build_shortest_path(
    const ShortestPathResult& result,
    std::size_t source,
    std::size_t target
) {
    if (source >= result.distance.size() || target >= result.distance.size()) {
        throw std::out_of_range("no path from source to target exists");
    }
    
    if (result.distance[target] == std::numeric_limits<int>::max()) {
        throw std::out_of_range("no path from source to target exists");
    }

    std::size_t path_length = 1;

    for (std::size_t current = target; current != source;) {
        if (result.parent[current] == std::nullopt) {
            throw std::invalid_argument("no path from source to target exists");
        }

        current = result.parent[current].value();
        ++path_length;
    }

    std::vector<std::size_t> path(path_length);

    std::size_t index = path_length;

    for (std::size_t current = target;;) {
        --index;
        path[index] = current;

        if (current == source) {
            break;
        }

        current = result.parent[current].value();
    }

    return path;
}

}  // namespace dsa::algorithms