#include <catch2/catch_test_macros.hpp>

#include "algorithms/minimum_spanning_tree.hpp"

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace {

int total_weight(const std::vector<dsa::algorithms::WeightedEdge>& edges) {
    int total = 0;

    for (const dsa::algorithms::WeightedEdge& edge : edges) {
        total += edge.weight;
    }

    return total;
}

bool same_undirected_edge(
    const dsa::algorithms::WeightedEdge& edge,
    std::size_t u,
    std::size_t v,
    int weight
) {
    return edge.weight == weight
        && (
            (edge.u == u && edge.v == v)
            || (edge.u == v && edge.v == u)
        );
}

bool contains_undirected_edge(
    const std::vector<dsa::algorithms::WeightedEdge>& edges,
    std::size_t u,
    std::size_t v,
    int weight
) {
    for (const dsa::algorithms::WeightedEdge& edge : edges) {
        if (same_undirected_edge(edge, u, v, weight)) {
            return true;
        }
    }

    return false;
}

}  // namespace

TEST_CASE("mst_kruskal returns empty MST for graph with zero vertices") {
    const std::vector<dsa::algorithms::WeightedEdge> edges;

    const auto result = dsa::algorithms::mst_kruskal(0, edges);

    REQUIRE(result.empty());
}

TEST_CASE("mst_prim returns empty MST for graph with zero vertices") {
    const std::vector<dsa::algorithms::WeightedEdge> edges;

    const auto result = dsa::algorithms::mst_prim(0, edges, 0);

    REQUIRE(result.empty());
}

TEST_CASE("mst_kruskal works with one vertex and no edges") {
    const std::vector<dsa::algorithms::WeightedEdge> edges;

    const auto result = dsa::algorithms::mst_kruskal(1, edges);

    REQUIRE(result.empty());
}

TEST_CASE("mst_prim works with one vertex and no edges") {
    const std::vector<dsa::algorithms::WeightedEdge> edges;

    const auto result = dsa::algorithms::mst_prim(1, edges, 0);

    REQUIRE(result.empty());
}

TEST_CASE("mst_kruskal computes MST for a simple graph") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    const auto result = dsa::algorithms::mst_kruskal(4, edges);

    REQUIRE(result.size() == 3);
    REQUIRE(total_weight(result) == 19);

    REQUIRE(contains_undirected_edge(result, 2, 3, 4));
    REQUIRE(contains_undirected_edge(result, 0, 3, 5));
    REQUIRE(contains_undirected_edge(result, 0, 1, 10));
}

TEST_CASE("mst_prim computes MST for a simple graph") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    const auto result = dsa::algorithms::mst_prim(4, edges, 0);

    REQUIRE(result.size() == 3);
    REQUIRE(total_weight(result) == 19);

    REQUIRE(contains_undirected_edge(result, 2, 3, 4));
    REQUIRE(contains_undirected_edge(result, 0, 3, 5));
    REQUIRE(contains_undirected_edge(result, 0, 1, 10));
}

TEST_CASE("mst_kruskal computes CLRS example MST total weight") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 4},
        {0, 7, 8},
        {1, 2, 8},
        {1, 7, 11},
        {2, 3, 7},
        {2, 8, 2},
        {2, 5, 4},
        {3, 4, 9},
        {3, 5, 14},
        {4, 5, 10},
        {5, 6, 2},
        {6, 7, 1},
        {6, 8, 6},
        {7, 8, 7}
    };

    const auto result = dsa::algorithms::mst_kruskal(9, edges);

    REQUIRE(result.size() == 8);
    REQUIRE(total_weight(result) == 37);
}

TEST_CASE("mst_prim computes CLRS example MST total weight") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 4},
        {0, 7, 8},
        {1, 2, 8},
        {1, 7, 11},
        {2, 3, 7},
        {2, 8, 2},
        {2, 5, 4},
        {3, 4, 9},
        {3, 5, 14},
        {4, 5, 10},
        {5, 6, 2},
        {6, 7, 1},
        {6, 8, 6},
        {7, 8, 7}
    };

    const auto result = dsa::algorithms::mst_prim(9, edges, 0);

    REQUIRE(result.size() == 8);
    REQUIRE(total_weight(result) == 37);
}

TEST_CASE("mst_kruskal ignores heavier edges that would create cycles") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 1},
        {1, 2, 2},
        {0, 2, 100},
        {2, 3, 3},
        {1, 3, 50}
    };

    const auto result = dsa::algorithms::mst_kruskal(4, edges);

    REQUIRE(result.size() == 3);
    REQUIRE(total_weight(result) == 6);

    REQUIRE(contains_undirected_edge(result, 0, 1, 1));
    REQUIRE(contains_undirected_edge(result, 1, 2, 2));
    REQUIRE(contains_undirected_edge(result, 2, 3, 3));
}

TEST_CASE("mst_prim ignores heavier edges that would create cycles") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 1},
        {1, 2, 2},
        {0, 2, 100},
        {2, 3, 3},
        {1, 3, 50}
    };

    const auto result = dsa::algorithms::mst_prim(4, edges, 0);

    REQUIRE(result.size() == 3);
    REQUIRE(total_weight(result) == 6);

    REQUIRE(contains_undirected_edge(result, 0, 1, 1));
    REQUIRE(contains_undirected_edge(result, 1, 2, 2));
    REQUIRE(contains_undirected_edge(result, 2, 3, 3));
}

TEST_CASE("mst_kruskal works when input edges are already unordered") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 3, 10},
        {0, 1, 1},
        {2, 3, 3},
        {1, 2, 2},
        {0, 2, 50}
    };

    const auto result = dsa::algorithms::mst_kruskal(4, edges);

    REQUIRE(result.size() == 3);
    REQUIRE(total_weight(result) == 6);

    REQUIRE(contains_undirected_edge(result, 0, 1, 1));
    REQUIRE(contains_undirected_edge(result, 1, 2, 2));
    REQUIRE(contains_undirected_edge(result, 2, 3, 3));
}

TEST_CASE("mst_prim works with a root different from zero") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 1},
        {1, 2, 2},
        {2, 3, 3},
        {0, 3, 10},
        {0, 2, 50}
    };

    const auto result = dsa::algorithms::mst_prim(4, edges, 2);

    REQUIRE(result.size() == 3);
    REQUIRE(total_weight(result) == 6);

    REQUIRE(contains_undirected_edge(result, 0, 1, 1));
    REQUIRE(contains_undirected_edge(result, 1, 2, 2));
    REQUIRE(contains_undirected_edge(result, 2, 3, 3));
}

TEST_CASE("mst_kruskal throws when edge has invalid vertex") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 1},
        {1, 4, 2}
    };

    REQUIRE_THROWS_AS(
        dsa::algorithms::mst_kruskal(4, edges),
        std::out_of_range
    );
}

TEST_CASE("mst_prim throws when edge has invalid vertex") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 1},
        {1, 4, 2}
    };

    REQUIRE_THROWS_AS(
        dsa::algorithms::mst_prim(4, edges, 0),
        std::out_of_range
    );
}

TEST_CASE("mst_prim throws when root is out of range") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 1}
    };

    REQUIRE_THROWS_AS(
        dsa::algorithms::mst_prim(2, edges, 2),
        std::invalid_argument
    );
}

TEST_CASE("mst_prim throws with negative edge weight") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, -1}
    };

    REQUIRE_THROWS_AS(
        dsa::algorithms::mst_prim(2, edges, 0),
        std::invalid_argument
    );
}

TEST_CASE("mst_kruskal supports negative edge weights") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, -2},
        {1, 2, 3},
        {0, 2, 10}
    };

    const auto result = dsa::algorithms::mst_kruskal(3, edges);

    REQUIRE(result.size() == 2);
    REQUIRE(total_weight(result) == 1);

    REQUIRE(contains_undirected_edge(result, 0, 1, -2));
    REQUIRE(contains_undirected_edge(result, 1, 2, 3));
}

TEST_CASE("mst_kruskal returns spanning forest for disconnected graph") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 1},
        {2, 3, 2}
    };

    const auto result = dsa::algorithms::mst_kruskal(4, edges);

    REQUIRE(result.size() == 2);
    REQUIRE(total_weight(result) == 3);

    REQUIRE(contains_undirected_edge(result, 0, 1, 1));
    REQUIRE(contains_undirected_edge(result, 2, 3, 2));
}

TEST_CASE("mst_prim returns spanning forest for disconnected graph") {
    const std::vector<dsa::algorithms::WeightedEdge> edges{
        {0, 1, 1},
        {2, 3, 2}
    };

    const auto result = dsa::algorithms::mst_prim(4, edges, 0);

    REQUIRE(result.size() == 2);
    REQUIRE(total_weight(result) == 3);

    REQUIRE(contains_undirected_edge(result, 0, 1, 1));
    REQUIRE(contains_undirected_edge(result, 2, 3, 2));
}