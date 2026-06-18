#include "data_structures/disjoint_set_forest.hpp"

#include <catch2/catch_test_macros.hpp>

#include <stdexcept>
#include <type_traits>

namespace {

using dsa::data_structures::DisjointSetForest;
using dsa::data_structures::DSFNode;

bool is_representative(DSFNode* node) {
    return node != nullptr && node->p == node;
}

}  // namespace

TEST_CASE("DisjointSetForest starts empty") {
    DisjointSetForest sets;

    REQUIRE(sets.size() == 0);
}

TEST_CASE("DisjointSetForest make_set creates singleton sets") {
    DisjointSetForest sets;

    DSFNode* a = sets.make_set(10);
    DSFNode* b = sets.make_set(20);
    DSFNode* c = sets.make_set(30);

    REQUIRE(sets.size() == 3);

    REQUIRE(a->key == 10);
    REQUIRE(b->key == 20);
    REQUIRE(c->key == 30);

    REQUIRE(is_representative(a));
    REQUIRE(is_representative(b));
    REQUIRE(is_representative(c));

    REQUIRE(a->rank == 0);
    REQUIRE(b->rank == 0);
    REQUIRE(c->rank == 0);

    REQUIRE(sets.find_set(a) == a);
    REQUIRE(sets.find_set(b) == b);
    REQUIRE(sets.find_set(c) == c);
}

TEST_CASE("DisjointSetForest union_sets connects two singleton sets") {
    DisjointSetForest sets;

    DSFNode* a = sets.make_set(1);
    DSFNode* b = sets.make_set(2);

    REQUIRE_FALSE(sets.connected(a, b));

    sets.union_sets(a, b);

    REQUIRE(sets.connected(a, b));
    REQUIRE(sets.find_set(a) == sets.find_set(b));
    REQUIRE(sets.size() == 2);
}

TEST_CASE("DisjointSetForest union_sets is idempotent for nodes in the same set") {
    DisjointSetForest sets;

    DSFNode* a = sets.make_set(1);
    DSFNode* b = sets.make_set(2);

    sets.union_sets(a, b);

    DSFNode* representative = sets.find_set(a);
    const std::size_t rank = representative->rank;

    sets.union_sets(a, b);
    sets.union_sets(b, a);
    sets.union_sets(a, a);

    REQUIRE(sets.connected(a, b));
    REQUIRE(sets.find_set(a) == representative);
    REQUIRE(sets.find_set(b) == representative);
    REQUIRE(representative->rank == rank);
    REQUIRE(sets.size() == 2);
}

TEST_CASE("DisjointSetForest union by rank updates rank only when ranks are equal") {
    DisjointSetForest sets;

    DSFNode* a = sets.make_set(1);
    DSFNode* b = sets.make_set(2);
    DSFNode* c = sets.make_set(3);

    sets.union_sets(a, b);

    DSFNode* ab_representative = sets.find_set(a);

    REQUIRE(ab_representative == sets.find_set(b));
    REQUIRE(ab_representative->rank == 1);

    sets.union_sets(a, c);

    DSFNode* final_representative = sets.find_set(a);

    REQUIRE(final_representative == ab_representative);
    REQUIRE(sets.find_set(c) == final_representative);
    REQUIRE(final_representative->rank == 1);
}

TEST_CASE("DisjointSetForest creates multiple components correctly") {
    DisjointSetForest sets;

    DSFNode* a = sets.make_set(1);
    DSFNode* b = sets.make_set(2);
    DSFNode* c = sets.make_set(3);
    DSFNode* d = sets.make_set(4);
    DSFNode* e = sets.make_set(5);

    sets.union_sets(a, b);
    sets.union_sets(c, d);

    REQUIRE(sets.connected(a, b));
    REQUIRE(sets.connected(c, d));

    REQUIRE_FALSE(sets.connected(a, c));
    REQUIRE_FALSE(sets.connected(a, e));
    REQUIRE_FALSE(sets.connected(c, e));

    sets.union_sets(b, d);

    REQUIRE(sets.connected(a, c));
    REQUIRE(sets.connected(a, d));
    REQUIRE(sets.connected(b, c));
    REQUIRE(sets.connected(b, d));

    REQUIRE_FALSE(sets.connected(a, e));
}

TEST_CASE("DisjointSetForest find_set applies path compression") {
    DisjointSetForest sets;

    DSFNode* a = sets.make_set(1);
    DSFNode* b = sets.make_set(2);
    DSFNode* c = sets.make_set(3);
    DSFNode* d = sets.make_set(4);

    sets.union_sets(a, b);
    sets.union_sets(c, d);
    sets.union_sets(b, d);

    DSFNode* representative = sets.find_set(d);

    REQUIRE(d->p == representative);
    REQUIRE(sets.find_set(a) == representative);
    REQUIRE(sets.find_set(b) == representative);
    REQUIRE(sets.find_set(c) == representative);
    REQUIRE(sets.find_set(d) == representative);
}

TEST_CASE("DisjointSetForest connected returns true exactly for same representative") {
    DisjointSetForest sets;

    DSFNode* a = sets.make_set(1);
    DSFNode* b = sets.make_set(2);
    DSFNode* c = sets.make_set(3);

    REQUIRE(sets.connected(a, a));
    REQUIRE_FALSE(sets.connected(a, b));
    REQUIRE_FALSE(sets.connected(a, c));

    sets.union_sets(a, b);

    REQUIRE(sets.connected(a, b));
    REQUIRE_FALSE(sets.connected(a, c));
    REQUIRE_FALSE(sets.connected(b, c));

    sets.union_sets(b, c);

    REQUIRE(sets.connected(a, c));
    REQUIRE(sets.connected(b, c));
}

TEST_CASE("DisjointSetForest rejects null nodes") {
    DisjointSetForest sets;

    DSFNode* a = sets.make_set(1);

    REQUIRE_THROWS_AS(sets.find_set(nullptr), std::invalid_argument);
    REQUIRE_THROWS_AS(sets.union_sets(a, nullptr), std::invalid_argument);
    REQUIRE_THROWS_AS(sets.union_sets(nullptr, a), std::invalid_argument);
    REQUIRE_THROWS_AS(sets.connected(a, nullptr), std::invalid_argument);
    REQUIRE_THROWS_AS(sets.connected(nullptr, a), std::invalid_argument);
}

TEST_CASE("DisjointSetForest move constructor transfers ownership") {
    DisjointSetForest original;

    DSFNode* a = original.make_set(1);
    DSFNode* b = original.make_set(2);

    original.union_sets(a, b);

    DisjointSetForest moved(std::move(original));

    REQUIRE(moved.size() == 2);
    REQUIRE(original.size() == 0);

    REQUIRE(moved.connected(a, b));
}

TEST_CASE("DisjointSetForest move assignment transfers ownership") {
    DisjointSetForest original;
    DisjointSetForest moved;

    DSFNode* a = original.make_set(1);
    DSFNode* b = original.make_set(2);

    original.union_sets(a, b);

    moved.make_set(100);
    moved = std::move(original);

    REQUIRE(moved.size() == 2);
    REQUIRE(original.size() == 0);

    REQUIRE(moved.connected(a, b));
}