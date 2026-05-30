#include <catch2/catch_test_macros.hpp>

#include "data_structures/universal_hash_chained_table.hpp"

#include <stdexcept>
#include <utility>

TEST_CASE("UniversalHashChainedTable constructor creates an empty table") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    REQUIRE(table.chained_hash_search(0) == nullptr);
    REQUIRE(table.chained_hash_search(1) == nullptr);
    REQUIRE(table.chained_hash_search(2) == nullptr);
    REQUIRE(table.chained_hash_search(3) == nullptr);
    REQUIRE(table.chained_hash_search(4) == nullptr);
    REQUIRE(table.chained_hash_search(5) == nullptr);
}

TEST_CASE("UniversalHashChainedTable constructor throws when m is zero") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::UniversalHashChainedTable(0, 17, 3, 4),
        std::invalid_argument
    );
}

TEST_CASE("UniversalHashChainedTable constructor throws when p is not greater than m") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::UniversalHashChainedTable(6, 6, 3, 4),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        dsa::data_structures::UniversalHashChainedTable(6, 5, 3, 4),
        std::invalid_argument
    );
}

TEST_CASE("UniversalHashChainedTable constructor throws when a is zero") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::UniversalHashChainedTable(6, 17, 0, 4),
        std::invalid_argument
    );
}

TEST_CASE("UniversalHashChainedTable constructor throws when a is greater than or equal to p") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::UniversalHashChainedTable(6, 17, 17, 4),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        dsa::data_structures::UniversalHashChainedTable(6, 17, 18, 4),
        std::invalid_argument
    );
}

TEST_CASE("UniversalHashChainedTable constructor throws when b is greater than or equal to p") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::UniversalHashChainedTable(6, 17, 3, 17),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        dsa::data_structures::UniversalHashChainedTable(6, 17, 3, 18),
        std::invalid_argument
    );
}

TEST_CASE("UniversalHashChainedTable insert stores one key") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(8);

    dsa::data_structures::Node* result = table.chained_hash_search(8);

    REQUIRE(result != nullptr);
    REQUIRE(result->key == 8);
}

TEST_CASE("UniversalHashChainedTable search returns nullptr for a missing key in an empty bucket") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(8);

    REQUIRE(table.chained_hash_search(0) == nullptr);
}

TEST_CASE("UniversalHashChainedTable search returns nullptr for a missing key in a non-empty bucket") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    // h(8)  = ((3 * 8  + 4) mod 17) mod 6 = 5
    // h(14) = ((3 * 14 + 4) mod 17) mod 6 = 5
    table.chained_hash_insert(8);

    REQUIRE(table.chained_hash_search(14) == nullptr);
}

TEST_CASE("UniversalHashChainedTable insert supports key zero") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(0);

    dsa::data_structures::Node* result = table.chained_hash_search(0);

    REQUIRE(result != nullptr);
    REQUIRE(result->key == 0);
}

TEST_CASE("UniversalHashChainedTable insert handles collisions with chaining") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    // h(8)  = ((3 * 8  + 4) mod 17) mod 6 = 5
    // h(14) = ((3 * 14 + 4) mod 17) mod 6 = 5
    // h(25) = ((3 * 25 + 4) mod 17) mod 6 = 5
    table.chained_hash_insert(8);
    table.chained_hash_insert(14);
    table.chained_hash_insert(25);

    REQUIRE(table.chained_hash_search(8) != nullptr);
    REQUIRE(table.chained_hash_search(14) != nullptr);
    REQUIRE(table.chained_hash_search(25) != nullptr);

    REQUIRE(table.chained_hash_search(8)->key == 8);
    REQUIRE(table.chained_hash_search(14)->key == 14);
    REQUIRE(table.chained_hash_search(25)->key == 25);
}

TEST_CASE("UniversalHashChainedTable delete removes an existing key") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(8);

    REQUIRE(table.chained_hash_search(8) != nullptr);

    table.chained_hash_delete(8);

    REQUIRE(table.chained_hash_search(8) == nullptr);
}

TEST_CASE("UniversalHashChainedTable delete removes the first key from a collision chain") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(8);
    table.chained_hash_insert(14);
    table.chained_hash_insert(25);

    table.chained_hash_delete(8);

    REQUIRE(table.chained_hash_search(8) == nullptr);
    REQUIRE(table.chained_hash_search(14) != nullptr);
    REQUIRE(table.chained_hash_search(25) != nullptr);

    REQUIRE(table.chained_hash_search(14)->key == 14);
    REQUIRE(table.chained_hash_search(25)->key == 25);
}

TEST_CASE("UniversalHashChainedTable delete removes a middle key from a collision chain") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(8);
    table.chained_hash_insert(14);
    table.chained_hash_insert(25);

    table.chained_hash_delete(14);

    REQUIRE(table.chained_hash_search(8) != nullptr);
    REQUIRE(table.chained_hash_search(14) == nullptr);
    REQUIRE(table.chained_hash_search(25) != nullptr);

    REQUIRE(table.chained_hash_search(8)->key == 8);
    REQUIRE(table.chained_hash_search(25)->key == 25);
}

TEST_CASE("UniversalHashChainedTable delete removes the last key from a collision chain") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(8);
    table.chained_hash_insert(14);
    table.chained_hash_insert(25);

    table.chained_hash_delete(25);

    REQUIRE(table.chained_hash_search(8) != nullptr);
    REQUIRE(table.chained_hash_search(14) != nullptr);
    REQUIRE(table.chained_hash_search(25) == nullptr);

    REQUIRE(table.chained_hash_search(8)->key == 8);
    REQUIRE(table.chained_hash_search(14)->key == 14);
}

TEST_CASE("UniversalHashChainedTable delete missing key leaves table unchanged") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(8);
    table.chained_hash_insert(14);

    table.chained_hash_delete(25);

    REQUIRE(table.chained_hash_search(8) != nullptr);
    REQUIRE(table.chained_hash_search(14) != nullptr);
    REQUIRE(table.chained_hash_search(25) == nullptr);

    REQUIRE(table.chained_hash_search(8)->key == 8);
    REQUIRE(table.chained_hash_search(14)->key == 14);
}

TEST_CASE("UniversalHashChainedTable supports multiple buckets") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

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

TEST_CASE("UniversalHashChainedTable copy constructor creates an independent copy") {
    dsa::data_structures::UniversalHashChainedTable original(6, 17, 3, 4);

    original.chained_hash_insert(8);
    original.chained_hash_insert(14);
    original.chained_hash_insert(2);

    dsa::data_structures::UniversalHashChainedTable copy(original);

    REQUIRE(copy.chained_hash_search(8) != nullptr);
    REQUIRE(copy.chained_hash_search(14) != nullptr);
    REQUIRE(copy.chained_hash_search(2) != nullptr);
    REQUIRE(copy.chained_hash_search(3) == nullptr);

    REQUIRE(copy.chained_hash_search(8)->key == 8);
    REQUIRE(copy.chained_hash_search(14)->key == 14);
    REQUIRE(copy.chained_hash_search(2)->key == 2);

    copy.chained_hash_delete(14);

    REQUIRE(copy.chained_hash_search(14) == nullptr);
    REQUIRE(original.chained_hash_search(14) != nullptr);
    REQUIRE(original.chained_hash_search(14)->key == 14);
}

TEST_CASE("UniversalHashChainedTable copy constructor works with an empty table") {
    dsa::data_structures::UniversalHashChainedTable original(6, 17, 3, 4);

    dsa::data_structures::UniversalHashChainedTable copy(original);

    REQUIRE(copy.chained_hash_search(0) == nullptr);
    REQUIRE(copy.chained_hash_search(1) == nullptr);
    REQUIRE(copy.chained_hash_search(2) == nullptr);
    REQUIRE(copy.chained_hash_search(3) == nullptr);
    REQUIRE(copy.chained_hash_search(4) == nullptr);
    REQUIRE(copy.chained_hash_search(5) == nullptr);
}

TEST_CASE("UniversalHashChainedTable copy assignment creates an independent copy") {
    dsa::data_structures::UniversalHashChainedTable original(6, 17, 3, 4);

    original.chained_hash_insert(8);
    original.chained_hash_insert(14);
    original.chained_hash_insert(2);

    dsa::data_structures::UniversalHashChainedTable copy(5, 11, 2, 3);
    copy.chained_hash_insert(0);

    copy = original;

    REQUIRE(copy.chained_hash_search(8) != nullptr);
    REQUIRE(copy.chained_hash_search(14) != nullptr);
    REQUIRE(copy.chained_hash_search(2) != nullptr);
    REQUIRE(copy.chained_hash_search(3) == nullptr);

    REQUIRE(copy.chained_hash_search(8)->key == 8);
    REQUIRE(copy.chained_hash_search(14)->key == 14);
    REQUIRE(copy.chained_hash_search(2)->key == 2);

    copy.chained_hash_delete(14);

    REQUIRE(copy.chained_hash_search(14) == nullptr);
    REQUIRE(original.chained_hash_search(14) != nullptr);
    REQUIRE(original.chained_hash_search(14)->key == 14);
}

TEST_CASE("UniversalHashChainedTable copy assignment handles self-assignment") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(8);
    table.chained_hash_insert(14);

    table = table;

    REQUIRE(table.chained_hash_search(8) != nullptr);
    REQUIRE(table.chained_hash_search(14) != nullptr);

    REQUIRE(table.chained_hash_search(8)->key == 8);
    REQUIRE(table.chained_hash_search(14)->key == 14);
}

TEST_CASE("UniversalHashChainedTable move constructor transfers ownership") {
    dsa::data_structures::UniversalHashChainedTable original(6, 17, 3, 4);

    original.chained_hash_insert(8);
    original.chained_hash_insert(14);
    original.chained_hash_insert(2);

    dsa::data_structures::UniversalHashChainedTable moved(std::move(original));

    REQUIRE(moved.chained_hash_search(8) != nullptr);
    REQUIRE(moved.chained_hash_search(14) != nullptr);
    REQUIRE(moved.chained_hash_search(2) != nullptr);
    REQUIRE(moved.chained_hash_search(3) == nullptr);

    REQUIRE(moved.chained_hash_search(8)->key == 8);
    REQUIRE(moved.chained_hash_search(14)->key == 14);
    REQUIRE(moved.chained_hash_search(2)->key == 2);
}

TEST_CASE("UniversalHashChainedTable move assignment transfers ownership") {
    dsa::data_structures::UniversalHashChainedTable original(6, 17, 3, 4);

    original.chained_hash_insert(8);
    original.chained_hash_insert(14);
    original.chained_hash_insert(2);

    dsa::data_structures::UniversalHashChainedTable moved(5, 11, 2, 3);
    moved.chained_hash_insert(0);

    moved = std::move(original);

    REQUIRE(moved.chained_hash_search(8) != nullptr);
    REQUIRE(moved.chained_hash_search(14) != nullptr);
    REQUIRE(moved.chained_hash_search(2) != nullptr);
    REQUIRE(moved.chained_hash_search(3) == nullptr);

    REQUIRE(moved.chained_hash_search(8)->key == 8);
    REQUIRE(moved.chained_hash_search(14)->key == 14);
    REQUIRE(moved.chained_hash_search(2)->key == 2);
}

TEST_CASE("UniversalHashChainedTable move assignment handles self-move-assignment") {
    dsa::data_structures::UniversalHashChainedTable table(6, 17, 3, 4);

    table.chained_hash_insert(8);
    table.chained_hash_insert(14);

    table = std::move(table);

    REQUIRE(table.chained_hash_search(8) != nullptr);
    REQUIRE(table.chained_hash_search(14) != nullptr);

    REQUIRE(table.chained_hash_search(8)->key == 8);
    REQUIRE(table.chained_hash_search(14)->key == 14);
}