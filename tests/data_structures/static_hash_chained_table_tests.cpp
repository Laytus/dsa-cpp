#include <catch2/catch_test_macros.hpp>

#include "data_structures/static_hash_chained_table.hpp"

#include <stdexcept>
#include <utility>

using dsa::data_structures::HashFunctionType;

TEST_CASE("StaticHashChainedTable constructor creates an empty table") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    REQUIRE(table.chained_hash_search(0) == nullptr);
    REQUIRE(table.chained_hash_search(1) == nullptr);
    REQUIRE(table.chained_hash_search(2) == nullptr);
    REQUIRE(table.chained_hash_search(3) == nullptr);
    REQUIRE(table.chained_hash_search(4) == nullptr);
}

TEST_CASE("StaticHashChainedTable constructor throws when capacity is zero") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::StaticHashChainedTable(0, HashFunctionType::Division),
        std::invalid_argument
    );
}

TEST_CASE("StaticHashChainedTable insert stores one key") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(3);

    dsa::data_structures::Node* result = table.chained_hash_search(3);

    REQUIRE(result != nullptr);
    REQUIRE(result->key == 3);
}

TEST_CASE("StaticHashChainedTable search returns nullptr for a missing key in an empty bucket") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(3);

    REQUIRE(table.chained_hash_search(1) == nullptr);
    REQUIRE(table.chained_hash_search(4) == nullptr);
}

TEST_CASE("StaticHashChainedTable search returns nullptr for a missing key in a non-empty bucket") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);

    REQUIRE(table.chained_hash_search(11) == nullptr);
}

TEST_CASE("StaticHashChainedTable insert supports key zero") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(0);

    dsa::data_structures::Node* result = table.chained_hash_search(0);

    REQUIRE(result != nullptr);
    REQUIRE(result->key == 0);
}

TEST_CASE("StaticHashChainedTable insert handles collisions with chaining") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);
    table.chained_hash_insert(11);

    REQUIRE(table.chained_hash_search(1) != nullptr);
    REQUIRE(table.chained_hash_search(6) != nullptr);
    REQUIRE(table.chained_hash_search(11) != nullptr);

    REQUIRE(table.chained_hash_search(1)->key == 1);
    REQUIRE(table.chained_hash_search(6)->key == 6);
    REQUIRE(table.chained_hash_search(11)->key == 11);
}

TEST_CASE("StaticHashChainedTable delete removes an existing key") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(3);

    REQUIRE(table.chained_hash_search(3) != nullptr);

    table.chained_hash_delete(3);

    REQUIRE(table.chained_hash_search(3) == nullptr);
}

TEST_CASE("StaticHashChainedTable delete removes the first key from a collision chain") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);
    table.chained_hash_insert(11);

    table.chained_hash_delete(1);

    REQUIRE(table.chained_hash_search(1) == nullptr);
    REQUIRE(table.chained_hash_search(6) != nullptr);
    REQUIRE(table.chained_hash_search(11) != nullptr);

    REQUIRE(table.chained_hash_search(6)->key == 6);
    REQUIRE(table.chained_hash_search(11)->key == 11);
}

TEST_CASE("StaticHashChainedTable delete removes a middle key from a collision chain") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);
    table.chained_hash_insert(11);

    table.chained_hash_delete(6);

    REQUIRE(table.chained_hash_search(1) != nullptr);
    REQUIRE(table.chained_hash_search(6) == nullptr);
    REQUIRE(table.chained_hash_search(11) != nullptr);

    REQUIRE(table.chained_hash_search(1)->key == 1);
    REQUIRE(table.chained_hash_search(11)->key == 11);
}

TEST_CASE("StaticHashChainedTable delete removes the last key from a collision chain") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);
    table.chained_hash_insert(11);

    table.chained_hash_delete(11);

    REQUIRE(table.chained_hash_search(1) != nullptr);
    REQUIRE(table.chained_hash_search(6) != nullptr);
    REQUIRE(table.chained_hash_search(11) == nullptr);

    REQUIRE(table.chained_hash_search(1)->key == 1);
    REQUIRE(table.chained_hash_search(6)->key == 6);
}

TEST_CASE("StaticHashChainedTable delete missing key leaves table unchanged") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);

    table.chained_hash_delete(11);

    REQUIRE(table.chained_hash_search(1) != nullptr);
    REQUIRE(table.chained_hash_search(6) != nullptr);
    REQUIRE(table.chained_hash_search(11) == nullptr);

    REQUIRE(table.chained_hash_search(1)->key == 1);
    REQUIRE(table.chained_hash_search(6)->key == 6);
}

TEST_CASE("StaticHashChainedTable supports multiple buckets") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(0);
    table.chained_hash_insert(1);
    table.chained_hash_insert(2);
    table.chained_hash_insert(3);
    table.chained_hash_insert(4);

    REQUIRE(table.chained_hash_search(0)->key == 0);
    REQUIRE(table.chained_hash_search(1)->key == 1);
    REQUIRE(table.chained_hash_search(2)->key == 2);
    REQUIRE(table.chained_hash_search(3)->key == 3);
    REQUIRE(table.chained_hash_search(4)->key == 4);
}

TEST_CASE("StaticHashChainedTable copy constructor creates an independent copy") {
    dsa::data_structures::StaticHashChainedTable original(5, HashFunctionType::Division);

    original.chained_hash_insert(1);
    original.chained_hash_insert(6);
    original.chained_hash_insert(2);

    dsa::data_structures::StaticHashChainedTable copy(original);

    REQUIRE(copy.chained_hash_search(1) != nullptr);
    REQUIRE(copy.chained_hash_search(6) != nullptr);
    REQUIRE(copy.chained_hash_search(2) != nullptr);
    REQUIRE(copy.chained_hash_search(3) == nullptr);

    REQUIRE(copy.chained_hash_search(1)->key == 1);
    REQUIRE(copy.chained_hash_search(6)->key == 6);
    REQUIRE(copy.chained_hash_search(2)->key == 2);

    copy.chained_hash_delete(6);

    REQUIRE(copy.chained_hash_search(6) == nullptr);
    REQUIRE(original.chained_hash_search(6) != nullptr);
    REQUIRE(original.chained_hash_search(6)->key == 6);
}

TEST_CASE("StaticHashChainedTable copy constructor works with an empty table") {
    dsa::data_structures::StaticHashChainedTable original(5, HashFunctionType::Division);

    dsa::data_structures::StaticHashChainedTable copy(original);

    REQUIRE(copy.chained_hash_search(0) == nullptr);
    REQUIRE(copy.chained_hash_search(1) == nullptr);
    REQUIRE(copy.chained_hash_search(2) == nullptr);
    REQUIRE(copy.chained_hash_search(3) == nullptr);
    REQUIRE(copy.chained_hash_search(4) == nullptr);
}

TEST_CASE("StaticHashChainedTable copy assignment creates an independent copy") {
    dsa::data_structures::StaticHashChainedTable original(5, HashFunctionType::Division);

    original.chained_hash_insert(1);
    original.chained_hash_insert(6);
    original.chained_hash_insert(2);

    dsa::data_structures::StaticHashChainedTable copy(3, HashFunctionType::Division);
    copy.chained_hash_insert(0);

    copy = original;

    REQUIRE(copy.chained_hash_search(1) != nullptr);
    REQUIRE(copy.chained_hash_search(6) != nullptr);
    REQUIRE(copy.chained_hash_search(2) != nullptr);
    REQUIRE(copy.chained_hash_search(3) == nullptr);

    REQUIRE(copy.chained_hash_search(1)->key == 1);
    REQUIRE(copy.chained_hash_search(6)->key == 6);
    REQUIRE(copy.chained_hash_search(2)->key == 2);

    copy.chained_hash_delete(6);

    REQUIRE(copy.chained_hash_search(6) == nullptr);
    REQUIRE(original.chained_hash_search(6) != nullptr);
    REQUIRE(original.chained_hash_search(6)->key == 6);
}

TEST_CASE("StaticHashChainedTable copy assignment handles self-assignment") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);

    table = table;

    REQUIRE(table.chained_hash_search(1) != nullptr);
    REQUIRE(table.chained_hash_search(6) != nullptr);

    REQUIRE(table.chained_hash_search(1)->key == 1);
    REQUIRE(table.chained_hash_search(6)->key == 6);
}

TEST_CASE("StaticHashChainedTable move constructor transfers ownership") {
    dsa::data_structures::StaticHashChainedTable original(5, HashFunctionType::Division);

    original.chained_hash_insert(1);
    original.chained_hash_insert(6);
    original.chained_hash_insert(2);

    dsa::data_structures::StaticHashChainedTable moved(std::move(original));

    REQUIRE(moved.chained_hash_search(1) != nullptr);
    REQUIRE(moved.chained_hash_search(6) != nullptr);
    REQUIRE(moved.chained_hash_search(2) != nullptr);
    REQUIRE(moved.chained_hash_search(3) == nullptr);

    REQUIRE(moved.chained_hash_search(1)->key == 1);
    REQUIRE(moved.chained_hash_search(6)->key == 6);
    REQUIRE(moved.chained_hash_search(2)->key == 2);
}

TEST_CASE("StaticHashChainedTable move assignment transfers ownership") {
    dsa::data_structures::StaticHashChainedTable original(5, HashFunctionType::Division);

    original.chained_hash_insert(1);
    original.chained_hash_insert(6);
    original.chained_hash_insert(2);

    dsa::data_structures::StaticHashChainedTable moved(3, HashFunctionType::Division);
    moved.chained_hash_insert(0);

    moved = std::move(original);

    REQUIRE(moved.chained_hash_search(1) != nullptr);
    REQUIRE(moved.chained_hash_search(6) != nullptr);
    REQUIRE(moved.chained_hash_search(2) != nullptr);
    REQUIRE(moved.chained_hash_search(3) == nullptr);

    REQUIRE(moved.chained_hash_search(1)->key == 1);
    REQUIRE(moved.chained_hash_search(6)->key == 6);
    REQUIRE(moved.chained_hash_search(2)->key == 2);
}

TEST_CASE("StaticHashChainedTable move assignment handles self-move-assignment") {
    dsa::data_structures::StaticHashChainedTable table(5, HashFunctionType::Division);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);

    table = std::move(table);

    REQUIRE(table.chained_hash_search(1) != nullptr);
    REQUIRE(table.chained_hash_search(6) != nullptr);

    REQUIRE(table.chained_hash_search(1)->key == 1);
    REQUIRE(table.chained_hash_search(6)->key == 6);
}
TEST_CASE("StaticHashChainedTable multiplication hash works with power-of-two capacity") {
    dsa::data_structures::StaticHashChainedTable table(8, HashFunctionType::Multiplication);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);
    table.chained_hash_insert(11);

    REQUIRE(table.chained_hash_search(1) != nullptr);
    REQUIRE(table.chained_hash_search(6) != nullptr);
    REQUIRE(table.chained_hash_search(11) != nullptr);

    REQUIRE(table.chained_hash_search(1)->key == 1);
    REQUIRE(table.chained_hash_search(6)->key == 6);
    REQUIRE(table.chained_hash_search(11)->key == 11);
}

TEST_CASE("StaticHashChainedTable multiply-shift hash works with power-of-two capacity") {
    dsa::data_structures::StaticHashChainedTable table(8, HashFunctionType::MultiplyShift);

    table.chained_hash_insert(1);
    table.chained_hash_insert(6);
    table.chained_hash_insert(11);

    REQUIRE(table.chained_hash_search(1) != nullptr);
    REQUIRE(table.chained_hash_search(6) != nullptr);
    REQUIRE(table.chained_hash_search(11) != nullptr);

    REQUIRE(table.chained_hash_search(1)->key == 1);
    REQUIRE(table.chained_hash_search(6)->key == 6);
    REQUIRE(table.chained_hash_search(11)->key == 11);
}

TEST_CASE("StaticHashChainedTable multiplication-based hashes require power-of-two capacity") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::StaticHashChainedTable(5, HashFunctionType::Multiplication),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        dsa::data_structures::StaticHashChainedTable(5, HashFunctionType::MultiplyShift),
        std::invalid_argument
    );
}

TEST_CASE("StaticHashChainedTable copy preserves hash function type") {
    dsa::data_structures::StaticHashChainedTable original(8, HashFunctionType::MultiplyShift);

    original.chained_hash_insert(1);
    original.chained_hash_insert(6);
    original.chained_hash_insert(11);

    dsa::data_structures::StaticHashChainedTable copy(original);

    REQUIRE(copy.chained_hash_search(1) != nullptr);
    REQUIRE(copy.chained_hash_search(6) != nullptr);
    REQUIRE(copy.chained_hash_search(11) != nullptr);

    copy.chained_hash_delete(6);

    REQUIRE(copy.chained_hash_search(6) == nullptr);
    REQUIRE(original.chained_hash_search(6) != nullptr);
}

TEST_CASE("StaticHashChainedTable copy assignment preserves hash function type") {
    dsa::data_structures::StaticHashChainedTable original(8, HashFunctionType::Multiplication);

    original.chained_hash_insert(1);
    original.chained_hash_insert(6);
    original.chained_hash_insert(11);

    dsa::data_structures::StaticHashChainedTable copy(5, HashFunctionType::Division);
    copy.chained_hash_insert(3);

    copy = original;

    REQUIRE(copy.chained_hash_search(1) != nullptr);
    REQUIRE(copy.chained_hash_search(6) != nullptr);
    REQUIRE(copy.chained_hash_search(11) != nullptr);

    copy.chained_hash_delete(6);

    REQUIRE(copy.chained_hash_search(6) == nullptr);
    REQUIRE(original.chained_hash_search(6) != nullptr);
}