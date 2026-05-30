#include <catch2/catch_test_macros.hpp>

#include "data_structures/open_addressing_hash_table.hpp"

#include <stdexcept>
#include <utility>

using dsa::data_structures::Entry;
using dsa::data_structures::OpenAddressingHashTable;
using dsa::data_structures::ProbingType;
using dsa::data_structures::SlotState;

TEST_CASE("OpenAddressingHashTable constructor creates an empty table with linear probing") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    REQUIRE(table.capacity() == 5);
    REQUIRE(table.size() == 0);

    REQUIRE(table.hash_search(0) == nullptr);
    REQUIRE(table.hash_search(1) == nullptr);
    REQUIRE(table.hash_search(2) == nullptr);
    REQUIRE(table.hash_search(3) == nullptr);
    REQUIRE(table.hash_search(4) == nullptr);
}

TEST_CASE("OpenAddressingHashTable constructor throws when capacity is zero") {
    REQUIRE_THROWS_AS(
        OpenAddressingHashTable(0, ProbingType::Linear_probing),
        std::invalid_argument
    );
}

TEST_CASE("OpenAddressingHashTable double hashing requires prime capacity greater than two") {
    REQUIRE_THROWS_AS(
        OpenAddressingHashTable(0, ProbingType::Double_hashing),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        OpenAddressingHashTable(1, ProbingType::Double_hashing),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        OpenAddressingHashTable(2, ProbingType::Double_hashing),
        std::invalid_argument
    );

    REQUIRE_THROWS_AS(
        OpenAddressingHashTable(6, ProbingType::Double_hashing),
        std::invalid_argument
    );

    REQUIRE_NOTHROW(
        OpenAddressingHashTable(5, ProbingType::Double_hashing)
    );

    REQUIRE_NOTHROW(
        OpenAddressingHashTable(7, ProbingType::Double_hashing)
    );
}

TEST_CASE("OpenAddressingHashTable hash_insert stores one key with linear probing") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    const std::size_t index = table.hash_insert(3);

    REQUIRE(index == 3);
    REQUIRE(table.size() == 1);

    Entry* result = table.hash_search(3);

    REQUIRE(result != nullptr);
    REQUIRE(result->key == 3);
    REQUIRE(result->data == 3);
    REQUIRE(result->state == SlotState::Occupied);
}

TEST_CASE("OpenAddressingHashTable hash_search returns nullptr for missing key") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    table.hash_insert(3);

    REQUIRE(table.hash_search(1) == nullptr);
    REQUIRE(table.hash_search(4) == nullptr);
}

TEST_CASE("OpenAddressingHashTable linear probing resolves collisions") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    const std::size_t index1 = table.hash_insert(1);
    const std::size_t index2 = table.hash_insert(6);
    const std::size_t index3 = table.hash_insert(11);

    REQUIRE(index1 == 1);
    REQUIRE(index2 == 2);
    REQUIRE(index3 == 3);

    REQUIRE(table.size() == 3);

    REQUIRE(table.hash_search(1) != nullptr);
    REQUIRE(table.hash_search(6) != nullptr);
    REQUIRE(table.hash_search(11) != nullptr);

    REQUIRE(table.hash_search(1)->key == 1);
    REQUIRE(table.hash_search(6)->key == 6);
    REQUIRE(table.hash_search(11)->key == 11);
}

TEST_CASE("OpenAddressingHashTable insert throws when key already exists") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    table.hash_insert(3);

    REQUIRE_THROWS_AS(
        table.hash_insert(3),
        std::invalid_argument
    );

    REQUIRE(table.size() == 1);
}

TEST_CASE("OpenAddressingHashTable insert throws when table is full") {
    OpenAddressingHashTable table(3, ProbingType::Linear_probing);

    table.hash_insert(0);
    table.hash_insert(1);
    table.hash_insert(2);

    REQUIRE(table.size() == 3);

    REQUIRE_THROWS_AS(
        table.hash_insert(3),
        std::overflow_error
    );
}

TEST_CASE("OpenAddressingHashTable hash_delete removes an existing key") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    table.hash_insert(3);

    REQUIRE(table.hash_search(3) != nullptr);
    REQUIRE(table.size() == 1);

    table.hash_delete(3);

    REQUIRE(table.hash_search(3) == nullptr);
    REQUIRE(table.size() == 0);
}

TEST_CASE("OpenAddressingHashTable hash_delete leaves table unchanged for missing key") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    table.hash_insert(1);
    table.hash_insert(6);

    table.hash_delete(11);

    REQUIRE(table.size() == 2);

    REQUIRE(table.hash_search(1) != nullptr);
    REQUIRE(table.hash_search(6) != nullptr);
    REQUIRE(table.hash_search(11) == nullptr);
}

TEST_CASE("OpenAddressingHashTable search continues past deleted slots") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    table.hash_insert(1);
    table.hash_insert(6);
    table.hash_insert(11);

    table.hash_delete(1);

    REQUIRE(table.hash_search(1) == nullptr);
    REQUIRE(table.hash_search(6) != nullptr);
    REQUIRE(table.hash_search(11) != nullptr);

    REQUIRE(table.hash_search(6)->key == 6);
    REQUIRE(table.hash_search(11)->key == 11);
}

TEST_CASE("OpenAddressingHashTable insert reuses deleted slots") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    table.hash_insert(1);
    table.hash_insert(6);

    table.hash_delete(1);

    REQUIRE(table.size() == 1);

    const std::size_t index = table.hash_insert(11);

    REQUIRE(index == 1);
    REQUIRE(table.size() == 2);

    REQUIRE(table.hash_search(11) != nullptr);
    REQUIRE(table.hash_search(11)->key == 11);
}

TEST_CASE("OpenAddressingHashTable deleting the same key twice does not decrement size twice") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    table.hash_insert(1);

    REQUIRE(table.size() == 1);

    table.hash_delete(1);
    table.hash_delete(1);

    REQUIRE(table.size() == 0);
    REQUIRE(table.hash_search(1) == nullptr);
}

TEST_CASE("OpenAddressingHashTable copy constructor creates an independent copy") {
    OpenAddressingHashTable original(5, ProbingType::Linear_probing);

    original.hash_insert(1);
    original.hash_insert(6);
    original.hash_insert(11);

    OpenAddressingHashTable copy(original);

    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.size() == original.size());

    REQUIRE(copy.hash_search(1) != nullptr);
    REQUIRE(copy.hash_search(6) != nullptr);
    REQUIRE(copy.hash_search(11) != nullptr);

    copy.hash_delete(6);

    REQUIRE(copy.hash_search(6) == nullptr);
    REQUIRE(original.hash_search(6) != nullptr);
    REQUIRE(original.hash_search(6)->key == 6);
}

TEST_CASE("OpenAddressingHashTable copy assignment creates an independent copy") {
    OpenAddressingHashTable original(5, ProbingType::Linear_probing);

    original.hash_insert(1);
    original.hash_insert(6);
    original.hash_insert(11);

    OpenAddressingHashTable copy(3, ProbingType::Linear_probing);
    copy.hash_insert(0);

    copy = original;

    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.size() == original.size());

    REQUIRE(copy.hash_search(1) != nullptr);
    REQUIRE(copy.hash_search(6) != nullptr);
    REQUIRE(copy.hash_search(11) != nullptr);

    copy.hash_delete(6);

    REQUIRE(copy.hash_search(6) == nullptr);
    REQUIRE(original.hash_search(6) != nullptr);
    REQUIRE(original.hash_search(6)->key == 6);
}

TEST_CASE("OpenAddressingHashTable copy assignment handles self-assignment") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    table.hash_insert(1);
    table.hash_insert(6);

    table = table;

    REQUIRE(table.size() == 2);

    REQUIRE(table.hash_search(1) != nullptr);
    REQUIRE(table.hash_search(6) != nullptr);

    REQUIRE(table.hash_search(1)->key == 1);
    REQUIRE(table.hash_search(6)->key == 6);
}

TEST_CASE("OpenAddressingHashTable move constructor transfers ownership") {
    OpenAddressingHashTable original(5, ProbingType::Linear_probing);

    original.hash_insert(1);
    original.hash_insert(6);

    OpenAddressingHashTable moved(std::move(original));

    REQUIRE(moved.capacity() == 5);
    REQUIRE(moved.size() == 2);

    REQUIRE(moved.hash_search(1) != nullptr);
    REQUIRE(moved.hash_search(6) != nullptr);

    REQUIRE(moved.hash_search(1)->key == 1);
    REQUIRE(moved.hash_search(6)->key == 6);
}

TEST_CASE("OpenAddressingHashTable move assignment transfers ownership") {
    OpenAddressingHashTable original(5, ProbingType::Linear_probing);

    original.hash_insert(1);
    original.hash_insert(6);

    OpenAddressingHashTable moved(3, ProbingType::Linear_probing);
    moved.hash_insert(0);

    moved = std::move(original);

    REQUIRE(moved.capacity() == 5);
    REQUIRE(moved.size() == 2);

    REQUIRE(moved.hash_search(1) != nullptr);
    REQUIRE(moved.hash_search(6) != nullptr);

    REQUIRE(moved.hash_search(1)->key == 1);
    REQUIRE(moved.hash_search(6)->key == 6);
}

TEST_CASE("OpenAddressingHashTable move assignment handles self-move-assignment") {
    OpenAddressingHashTable table(5, ProbingType::Linear_probing);

    table.hash_insert(1);
    table.hash_insert(6);

    table = std::move(table);

    REQUIRE(table.capacity() == 5);
    REQUIRE(table.size() == 2);

    REQUIRE(table.hash_search(1) != nullptr);
    REQUIRE(table.hash_search(6) != nullptr);

    REQUIRE(table.hash_search(1)->key == 1);
    REQUIRE(table.hash_search(6)->key == 6);
}

TEST_CASE("OpenAddressingHashTable double hashing inserts and searches keys") {
    OpenAddressingHashTable table(5, ProbingType::Double_hashing);

    table.hash_insert(1);
    table.hash_insert(6);
    table.hash_insert(11);

    REQUIRE(table.size() == 3);

    REQUIRE(table.hash_search(1) != nullptr);
    REQUIRE(table.hash_search(6) != nullptr);
    REQUIRE(table.hash_search(11) != nullptr);

    REQUIRE(table.hash_search(1)->key == 1);
    REQUIRE(table.hash_search(6)->key == 6);
    REQUIRE(table.hash_search(11)->key == 11);
}

TEST_CASE("OpenAddressingHashTable double hashing handles problematic step sizes") {
    OpenAddressingHashTable table(5, ProbingType::Double_hashing);

    table.hash_insert(7);
    table.hash_insert(2);

    REQUIRE(table.size() == 2);

    REQUIRE(table.hash_search(7) != nullptr);
    REQUIRE(table.hash_search(2) != nullptr);

    REQUIRE(table.hash_search(7)->key == 7);
    REQUIRE(table.hash_search(2)->key == 2);
}

TEST_CASE("OpenAddressingHashTable double hashing deletion works") {
    OpenAddressingHashTable table(5, ProbingType::Double_hashing);

    table.hash_insert(1);
    table.hash_insert(6);
    table.hash_insert(11);

    table.hash_delete(6);

    REQUIRE(table.size() == 2);

    REQUIRE(table.hash_search(1) != nullptr);
    REQUIRE(table.hash_search(6) == nullptr);
    REQUIRE(table.hash_search(11) != nullptr);

    REQUIRE(table.hash_search(1)->key == 1);
    REQUIRE(table.hash_search(11)->key == 11);
}