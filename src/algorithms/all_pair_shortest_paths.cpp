#include "algorithms/all_pair_shortest_paths.hpp"

#include <vector>
#include <limits>
#include <stdexcept>
#include <optional>

namespace dsa::algorithms {

namespace {

constexpr int INF = std::numeric_limits<int>::max();

void validate_square_matrix(const WeightMatrix& matrix) {
    const std::size_t n = matrix.size();

    for (const std::vector<int>& row : matrix) {
        if (row.size() != n) {
            throw std::invalid_argument("matrix must be square");
        }
    }
}

}  // namespace

WeightMatrix extend_shortest_paths(
    const WeightMatrix& L_previous,
    const WeightMatrix& W
) {
    validate_square_matrix(L_previous);
    validate_square_matrix(W);

    const std::size_t n = W.size();

    if (L_previous.size() != n) {
        throw std::invalid_argument("matrices must have the same size");
    }

    WeightMatrix L_current(n, std::vector<int>(n, INF));

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            for (std::size_t k = 0; k < n; ++k) {
                if (L_previous[i][k] == INF || W[k][j] == INF) {
                    continue;
                }

                const int candidate = L_previous[i][k] + W[k][j];

                if (candidate < L_current[i][j]) {
                    L_current[i][j] = candidate;
                }
            }
        }
    }

    return L_current;
}

WeightMatrix slow_APSP(const WeightMatrix& W) {
    validate_square_matrix(W);

    const std::size_t n = W.size();

    WeightMatrix L = W;

    if (n <= 1) {
        return L;
    }

    for (std::size_t m = 2; m < n; ++m) {
        L = extend_shortest_paths(L, W);
    }

    return L;
}

WeightMatrix faster_APSP(const WeightMatrix& W) {
    validate_square_matrix(W);

    const std::size_t n = W.size();

    WeightMatrix L = W;

    if (n <= 1) {
        return L;
    }

    std::size_t r = 1;

    while (r < n - 1) {
        L = extend_shortest_paths(L, L);
        r *= 2;
    }

    return L;
}

WeightMatrix floyd_warshall(const WeightMatrix& W) {
    validate_square_matrix(W);

    const std::size_t n = W.size();

    WeightMatrix D = W;

    for (std::size_t k = 0; k < n; ++k) {
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                if (D[i][k] == INF || D[k][j] == INF) {
                    continue;
                }

                const int candidate = D[i][k] + D[k][j];

                if (candidate < D[i][j]) {
                    D[i][j] = candidate;
                }
            }
        }
    }

    return D;
}

APSPResult floyd_warshall_with_predecessors(const WeightMatrix& W) {
    validate_square_matrix(W);

    const std::size_t n = W.size();

    APSPResult result{
        W,
        PredecessorMatrix(n, std::vector<std::optional<std::size_t>>(n, std::nullopt))
    };

    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = 0; j < n; ++j) {
            if (i != j && W[i][j] != INF) {
                result.predecessor[i][j] = i;
            }
        }
    }

    for (std::size_t k = 0; k < n; ++k) {
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                if (result.distance[i][k] == INF || result.distance[k][j] == INF) {
                    continue;
                }

                const int candidate = result.distance[i][k] + result.distance[k][j];

                if (candidate < result.distance[i][j]) {
                    result.distance[i][j] = candidate;
                    result.predecessor[i][j] = result.predecessor[k][j];
                }
            }
        }
    }

    return result;
}

std::vector<std::size_t> build_all_pairs_shortest_path(
    const APSPResult& result,
    std::size_t source,
    std::size_t target
) {
    const std::size_t n = result.distance.size();

    validate_square_matrix(result.distance);

    if (result.predecessor.size() != n) {
        throw std::invalid_argument("predecessor matrix must have the same size as distance matrix");
    }

    for (const std::vector<std::optional<std::size_t>>& row : result.predecessor) {
        if (row.size() != n) {
            throw std::invalid_argument("predecessor matrix must be square");
        }
    }
    
    if (source >= n || target >= n) {
        throw std::out_of_range("vertex index out of range");
    }

    if (source == target) {
        return std::vector<std::size_t>{source};
    }
    
    if (
        result.distance[source][target] == INF ||
        result.predecessor[source][target] == std::nullopt
    ) {
        throw std::invalid_argument("no path from source to target exists");
    }
    
    std::size_t path_length = 1;
    
    for (std::size_t current = target; current != source;) {
        if (result.predecessor[source][current] == std::nullopt) {
            throw std::invalid_argument("no path from source to target exists");
        }

        current = result.predecessor[source][current].value();
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

        current = result.predecessor[source][current].value();
    }

    return path;
}

BoolMatrix transitive_closure(
    const dsa::data_structures::WeightedAdjacencyListGraph& graph
) {
    if (!graph.directed()) {
        throw std::invalid_argument("transitive closure requires a directed graph");
    }

    const std::size_t n = graph.vertex_count();

    BoolMatrix T(n, std::vector<bool>(n, false));

    for (std::size_t i = 0; i < n; ++i) {
        T[i][i] = true;
    }

    for (const dsa::data_structures::WeightedDirectedEdge& edge : graph.edges()) {
        T[edge.u][edge.v] = true;
    }

    for (std::size_t k = 0; k < n; ++k) {
        for (std::size_t i = 0; i < n; ++i) {
            for (std::size_t j = 0; j < n; ++j) {
                T[i][j] = T[i][j] || (T[i][k] && T[k][j]);
            }
        }
    }

    return T;
}

}  // namespace dsa::algorithms