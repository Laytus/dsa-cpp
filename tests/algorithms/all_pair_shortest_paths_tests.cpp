#include <catch2/catch_test_macros.hpp>

#include "algorithms/all_pair_shortest_paths.hpp"
#include "data_structures/weighted_adjacency_list_graph.hpp"

#include <limits>
#include <optional>
#include <stdexcept>
#include <vector>

using dsa::algorithms::APSPResult;
using dsa::algorithms::BoolMatrix;
using dsa::algorithms::WeightMatrix;
using dsa::algorithms::build_all_pairs_shortest_path;
using dsa::algorithms::extend_shortest_paths;
using dsa::algorithms::faster_APSP;
using dsa::algorithms::floyd_warshall;
using dsa::algorithms::floyd_warshall_with_predecessors;
using dsa::algorithms::slow_APSP;
using dsa::algorithms::transitive_closure;
using dsa::data_structures::WeightedAdjacencyListGraph;

namespace {

constexpr int INF = std::numeric_limits<int>::max();

WeightMatrix clrs_weight_matrix() {
    return WeightMatrix{
        {0,   3,   8,   INF, -4},
        {INF, 0,   INF, 1,   7},
        {INF, 4,   0,   INF, INF},
        {2,   INF, -5,  0,   INF},
        {INF, INF, INF, 6,   0}
    };
}

WeightMatrix clrs_all_pairs_result() {
    return WeightMatrix{
        {0,   1,   -3,  2,   -4},
        {3,   0,   -4,  1,   -1},
        {7,   4,   0,   5,   3},
        {2,   -1,  -5,  0,   -2},
        {8,   5,   1,   6,   0}
    };
}

}  // namespace

TEST_CASE("extend_shortest_paths computes L2 from CLRS matrix") {
    const WeightMatrix W = clrs_weight_matrix();

    const WeightMatrix L2 = extend_shortest_paths(W, W);

    const WeightMatrix expected{
        {0,   3,   8,   2,   -4},
        {3,   0,   -4,  1,   7},
        {INF, 4,   0,   5,   11},
        {2,   -1,  -5,  0,   -2},
        {8,   INF, 1,   6,   0}
    };

    REQUIRE(L2 == expected);
}

TEST_CASE("extend_shortest_paths preserves infinity when no composed path exists") {
    const WeightMatrix W{
        {0,   2,   INF},
        {INF, 0,   INF},
        {INF, INF, 0}
    };

    const WeightMatrix L2 = extend_shortest_paths(W, W);

    REQUIRE(L2[0][0] == 0);
    REQUIRE(L2[0][1] == 2);
    REQUIRE(L2[0][2] == INF);
    REQUIRE(L2[1][0] == INF);
    REQUIRE(L2[2][1] == INF);
}

TEST_CASE("extend_shortest_paths throws when first matrix is not square") {
    const WeightMatrix L{
        {0, 1},
        {2}
    };

    const WeightMatrix W{
        {0, 1},
        {2, 0}
    };

    REQUIRE_THROWS_AS(extend_shortest_paths(L, W), std::invalid_argument);
}

TEST_CASE("extend_shortest_paths throws when second matrix is not square") {
    const WeightMatrix L{
        {0, 1},
        {2, 0}
    };

    const WeightMatrix W{
        {0, 1},
        {2}
    };

    REQUIRE_THROWS_AS(extend_shortest_paths(L, W), std::invalid_argument);
}

TEST_CASE("extend_shortest_paths throws when matrices have different sizes") {
    const WeightMatrix L{
        {0, 1},
        {2, 0}
    };

    const WeightMatrix W{
        {0, 1, 2},
        {3, 0, 4},
        {5, 6, 0}
    };

    REQUIRE_THROWS_AS(extend_shortest_paths(L, W), std::invalid_argument);
}

TEST_CASE("slow_APSP computes all-pairs shortest paths on CLRS example") {
    const WeightMatrix W = clrs_weight_matrix();

    const WeightMatrix result = slow_APSP(W);

    REQUIRE(result == clrs_all_pairs_result());
}

TEST_CASE("faster_APSP computes all-pairs shortest paths on CLRS example") {
    const WeightMatrix W = clrs_weight_matrix();

    const WeightMatrix result = faster_APSP(W);

    REQUIRE(result == clrs_all_pairs_result());
}

TEST_CASE("floyd_warshall computes all-pairs shortest paths on CLRS example") {
    const WeightMatrix W = clrs_weight_matrix();

    const WeightMatrix result = floyd_warshall(W);

    REQUIRE(result == clrs_all_pairs_result());
}

TEST_CASE("slow_APSP, faster_APSP, and floyd_warshall agree") {
    const WeightMatrix W = clrs_weight_matrix();

    REQUIRE(slow_APSP(W) == faster_APSP(W));
    REQUIRE(faster_APSP(W) == floyd_warshall(W));
}

TEST_CASE("APSP algorithms work with one vertex") {
    const WeightMatrix W{
        {0}
    };

    REQUIRE(slow_APSP(W) == W);
    REQUIRE(faster_APSP(W) == W);
    REQUIRE(floyd_warshall(W) == W);
}

TEST_CASE("APSP algorithms work with empty matrix") {
    const WeightMatrix W{};

    REQUIRE(slow_APSP(W).empty());
    REQUIRE(faster_APSP(W).empty());
    REQUIRE(floyd_warshall(W).empty());
}

TEST_CASE("APSP algorithms throw when matrix is not square") {
    const WeightMatrix W{
        {0, 1, 2},
        {3, 0}
    };

    REQUIRE_THROWS_AS(slow_APSP(W), std::invalid_argument);
    REQUIRE_THROWS_AS(faster_APSP(W), std::invalid_argument);
    REQUIRE_THROWS_AS(floyd_warshall(W), std::invalid_argument);
    REQUIRE_THROWS_AS(floyd_warshall_with_predecessors(W), std::invalid_argument);
}

TEST_CASE("floyd_warshall_with_predecessors computes distances") {
    const WeightMatrix W = clrs_weight_matrix();

    const APSPResult result = floyd_warshall_with_predecessors(W);

    REQUIRE(result.distance == clrs_all_pairs_result());
    REQUIRE(result.predecessor.size() == W.size());

    for (const auto& row : result.predecessor) {
        REQUIRE(row.size() == W.size());
    }
}

TEST_CASE("floyd_warshall_with_predecessors initializes direct predecessors") {
    const WeightMatrix W{
        {0,   5,   INF},
        {INF, 0,   2},
        {INF, INF, 0}
    };

    const APSPResult result = floyd_warshall_with_predecessors(W);

    REQUIRE(result.predecessor[0][0] == std::nullopt);
    REQUIRE(result.predecessor[0][1] == 0);
    REQUIRE(result.predecessor[1][2] == 1);
    REQUIRE(result.predecessor[0][2] == 1);
}

TEST_CASE("build_all_pairs_shortest_path reconstructs CLRS path from 4 to 2") {
    const WeightMatrix W = clrs_weight_matrix();

    const APSPResult result = floyd_warshall_with_predecessors(W);

    const std::vector<std::size_t> path =
        build_all_pairs_shortest_path(result, 3, 1);

    REQUIRE(result.distance[3][1] == -1);
    REQUIRE(path == std::vector<std::size_t>{3, 2, 1});
}

TEST_CASE("build_all_pairs_shortest_path reconstructs direct path") {
    const WeightMatrix W{
        {0,   4,   INF},
        {INF, 0,   7},
        {INF, INF, 0}
    };

    const APSPResult result = floyd_warshall_with_predecessors(W);

    const std::vector<std::size_t> path =
        build_all_pairs_shortest_path(result, 0, 1);

    REQUIRE(result.distance[0][1] == 4);
    REQUIRE(path == std::vector<std::size_t>{0, 1});
}

TEST_CASE("build_all_pairs_shortest_path reconstructs indirect path") {
    const WeightMatrix W{
        {0,   2,   10},
        {INF, 0,   3},
        {INF, INF, 0}
    };

    const APSPResult result = floyd_warshall_with_predecessors(W);

    const std::vector<std::size_t> path =
        build_all_pairs_shortest_path(result, 0, 2);

    REQUIRE(result.distance[0][2] == 5);
    REQUIRE(path == std::vector<std::size_t>{0, 1, 2});
}

TEST_CASE("build_all_pairs_shortest_path returns source when source equals target") {
    const WeightMatrix W = clrs_weight_matrix();

    const APSPResult result = floyd_warshall_with_predecessors(W);

    const std::vector<std::size_t> path =
        build_all_pairs_shortest_path(result, 2, 2);

    REQUIRE(path == std::vector<std::size_t>{2});
}

TEST_CASE("build_all_pairs_shortest_path throws when source is out of range") {
    const WeightMatrix W = clrs_weight_matrix();

    const APSPResult result = floyd_warshall_with_predecessors(W);

    REQUIRE_THROWS_AS(
        build_all_pairs_shortest_path(result, 5, 1),
        std::out_of_range
    );
}

TEST_CASE("build_all_pairs_shortest_path throws when target is out of range") {
    const WeightMatrix W = clrs_weight_matrix();

    const APSPResult result = floyd_warshall_with_predecessors(W);

    REQUIRE_THROWS_AS(
        build_all_pairs_shortest_path(result, 0, 5),
        std::out_of_range
    );
}

TEST_CASE("build_all_pairs_shortest_path throws when no path exists") {
    const WeightMatrix W{
        {0,   1,   INF},
        {INF, 0,   INF},
        {INF, INF, 0}
    };

    const APSPResult result = floyd_warshall_with_predecessors(W);

    REQUIRE_THROWS_AS(
        build_all_pairs_shortest_path(result, 2, 0),
        std::invalid_argument
    );
}

TEST_CASE("build_all_pairs_shortest_path throws when predecessor matrix has wrong number of rows") {
    APSPResult result{
        WeightMatrix{
            {0, 1},
            {INF, 0}
        },
        dsa::algorithms::PredecessorMatrix{
            {std::nullopt, 0}
        }
    };

    REQUIRE_THROWS_AS(
        build_all_pairs_shortest_path(result, 0, 1),
        std::invalid_argument
    );
}

TEST_CASE("build_all_pairs_shortest_path throws when predecessor matrix is not square") {
    APSPResult result{
        WeightMatrix{
            {0, 1},
            {INF, 0}
        },
        dsa::algorithms::PredecessorMatrix{
            {std::nullopt, 0},
            {std::nullopt}
        }
    };

    REQUIRE_THROWS_AS(
        build_all_pairs_shortest_path(result, 0, 1),
        std::invalid_argument
    );
}

TEST_CASE("transitive_closure computes reachability on directed graph") {
    WeightedAdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 3, 1);

    const BoolMatrix T = transitive_closure(graph);

    const BoolMatrix expected{
        {true,  true,  true,  true},
        {false, true,  true,  true},
        {false, false, true,  true},
        {false, false, false, true}
    };

    REQUIRE(T == expected);
}

TEST_CASE("transitive_closure handles directed cycle") {
    WeightedAdjacencyListGraph graph(4, true);

    graph.add_edge(0, 1, 1);
    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 0, 1);
    graph.add_edge(2, 3, 1);

    const BoolMatrix T = transitive_closure(graph);

    const BoolMatrix expected{
        {true,  true,  true,  true},
        {true,  true,  true,  true},
        {true,  true,  true,  true},
        {false, false, false, true}
    };

    REQUIRE(T == expected);
}

TEST_CASE("transitive_closure ignores edge weights") {
    WeightedAdjacencyListGraph graph(3, true);

    graph.add_edge(0, 1, -10);
    graph.add_edge(1, 2, 50);

    const BoolMatrix T = transitive_closure(graph);

    REQUIRE(T[0][0]);
    REQUIRE(T[0][1]);
    REQUIRE(T[0][2]);
    REQUIRE_FALSE(T[1][0]);
    REQUIRE(T[1][1]);
    REQUIRE(T[1][2]);
    REQUIRE_FALSE(T[2][0]);
    REQUIRE_FALSE(T[2][1]);
    REQUIRE(T[2][2]);
}

TEST_CASE("transitive_closure works with one vertex") {
    WeightedAdjacencyListGraph graph(1, true);

    const BoolMatrix T = transitive_closure(graph);

    REQUIRE(T == BoolMatrix{{true}});
}

TEST_CASE("transitive_closure works with empty graph") {
    WeightedAdjacencyListGraph graph(0, true);

    const BoolMatrix T = transitive_closure(graph);

    REQUIRE(T.empty());
}

TEST_CASE("transitive_closure throws for undirected graph") {
    WeightedAdjacencyListGraph graph(3, false);

    graph.add_edge(0, 1, 1);

    REQUIRE_THROWS_AS(transitive_closure(graph), std::invalid_argument);
}