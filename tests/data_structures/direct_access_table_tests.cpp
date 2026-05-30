#include <catch2/catch_test_macros.hpp>

#include "data_structures/direct_access_table.hpp"

#include <stdexcept>
#include <utility>

TEST_CASE("DirectAccessTable constructor creates an empty table") {
    dsa::data_structures::DirectAccessTable table(5);

    REQUIRE(table.direct_access_search(0) == nullptr);
    REQUIRE(table.direct_access_search(1) == nullptr);
    REQUIRE(table.direct_access_search(2) == nullptr);
    REQUIRE(table.direct_access_search(3) == nullptr);
    REQUIRE(table.direct_access_search(4) == nullptr);
}

TEST_CASE("DirectAccessTable constructor throws when capacity is zero") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::DirectAccessTable(0),
        std::invalid_argument
    );
}

TEST_CASE("DirectAccessTable search throws when key is outside table range") {
    dsa::data_structures::DirectAccessTable table(5);

    REQUIRE_THROWS_AS(table.direct_access_search(5), std::out_of_range);
    REQUIRE_THROWS_AS(table.direct_access_search(100), std::out_of_range);
}

TEST_CASE("DirectAccessTable insert stores a node at its key index") {
    dsa::data_structures::DirectAccessTable table(10);

    dsa::data_structures::Node node{3, 300};

    table.direct_access_insert(&node);

    dsa::data_structures::Node* result = table.direct_access_search(3);

    REQUIRE(result != nullptr);
    REQUIRE(result == &node);
    REQUIRE(result->key == 3);
    REQUIRE(result->data == 300);
}

TEST_CASE("DirectAccessTable insert allows key zero") {
    dsa::data_structures::DirectAccessTable table(10);

    dsa::data_structures::Node node{0, 100};

    table.direct_access_insert(&node);

    dsa::data_structures::Node* result = table.direct_access_search(0);

    REQUIRE(result != nullptr);
    REQUIRE(result == &node);
    REQUIRE(result->key == 0);
    REQUIRE(result->data == 100);
}

TEST_CASE("DirectAccessTable insert allows the last valid key") {
    dsa::data_structures::DirectAccessTable table(10);

    dsa::data_structures::Node node{9, 900};

    table.direct_access_insert(&node);

    dsa::data_structures::Node* result = table.direct_access_search(9);

    REQUIRE(result != nullptr);
    REQUIRE(result == &node);
    REQUIRE(result->key == 9);
    REQUIRE(result->data == 900);
}

TEST_CASE("DirectAccessTable insert throws when node is nullptr") {
    dsa::data_structures::DirectAccessTable table(10);

    REQUIRE_THROWS_AS(
        table.direct_access_insert(nullptr),
        std::invalid_argument
    );
}


TEST_CASE("DirectAccessTable insert throws when key is outside table range") {
    dsa::data_structures::DirectAccessTable table(10);

    dsa::data_structures::Node node{10, 100};

    REQUIRE_THROWS_AS(
        table.direct_access_insert(&node),
        std::out_of_range
    );
}

TEST_CASE("DirectAccessTable insert overwrites an existing node with the same key") {
    dsa::data_structures::DirectAccessTable table(10);

    dsa::data_structures::Node first{4, 100};
    dsa::data_structures::Node second{4, 200};

    table.direct_access_insert(&first);
    REQUIRE(table.direct_access_search(4) == &first);

    table.direct_access_insert(&second);
    REQUIRE(table.direct_access_search(4) == &second);
    REQUIRE(table.direct_access_search(4)->data == 200);
}

TEST_CASE("DirectAccessTable delete removes an existing node") {
    dsa::data_structures::DirectAccessTable table(10);

    dsa::data_structures::Node node{3, 300};

    table.direct_access_insert(&node);
    REQUIRE(table.direct_access_search(3) == &node);

    table.direct_access_delete(&node);

    REQUIRE(table.direct_access_search(3) == nullptr);
}

TEST_CASE("DirectAccessTable delete throws when node is nullptr") {
    dsa::data_structures::DirectAccessTable table(10);

    REQUIRE_THROWS_AS(
        table.direct_access_delete(nullptr),
        std::invalid_argument
    );
}


TEST_CASE("DirectAccessTable delete throws when key is outside table range") {
    dsa::data_structures::DirectAccessTable table(10);

    dsa::data_structures::Node node{10, 100};

    REQUIRE_THROWS_AS(
        table.direct_access_delete(&node),
        std::out_of_range
    );
}

TEST_CASE("DirectAccessTable copy constructor copies table entries") {
    dsa::data_structures::DirectAccessTable original(10);

    dsa::data_structures::Node first{2, 200};
    dsa::data_structures::Node second{7, 700};

    original.direct_access_insert(&first);
    original.direct_access_insert(&second);

    dsa::data_structures::DirectAccessTable copy(original);

    REQUIRE(copy.direct_access_search(2) == &first);
    REQUIRE(copy.direct_access_search(7) == &second);
    REQUIRE(copy.direct_access_search(0) == nullptr);
}

TEST_CASE("DirectAccessTable copy assignment copies table entries") {
    dsa::data_structures::DirectAccessTable original(10);

    dsa::data_structures::Node first{2, 200};
    dsa::data_structures::Node second{7, 700};

    original.direct_access_insert(&first);
    original.direct_access_insert(&second);

    dsa::data_structures::DirectAccessTable copy(3);

    dsa::data_structures::Node old_node{1, 100};
    copy.direct_access_insert(&old_node);

    copy = original;

    REQUIRE(copy.direct_access_search(2) == &first);
    REQUIRE(copy.direct_access_search(7) == &second);
    REQUIRE(copy.direct_access_search(0) == nullptr);
    REQUIRE_THROWS_AS(copy.direct_access_search(10), std::out_of_range);
}

TEST_CASE("DirectAccessTable copy assignment handles self-assignment") {
    dsa::data_structures::DirectAccessTable table(10);

    dsa::data_structures::Node node{4, 400};

    table.direct_access_insert(&node);

    table = table;

    REQUIRE(table.direct_access_search(4) == &node);
    REQUIRE(table.direct_access_search(4)->data == 400);
}

TEST_CASE("DirectAccessTable move constructor transfers ownership") {
    dsa::data_structures::DirectAccessTable original(10);

    dsa::data_structures::Node first{2, 200};
    dsa::data_structures::Node second{7, 700};

    original.direct_access_insert(&first);
    original.direct_access_insert(&second);

    dsa::data_structures::DirectAccessTable moved(std::move(original));

    REQUIRE(moved.direct_access_search(2) == &first);
    REQUIRE(moved.direct_access_search(7) == &second);
    REQUIRE(moved.direct_access_search(0) == nullptr);
}

TEST_CASE("DirectAccessTable move assignment transfers ownership") {
    dsa::data_structures::DirectAccessTable original(10);

    dsa::data_structures::Node first{2, 200};
    dsa::data_structures::Node second{7, 700};

    original.direct_access_insert(&first);
    original.direct_access_insert(&second);

    dsa::data_structures::DirectAccessTable moved(3);

    dsa::data_structures::Node old_node{1, 100};
    moved.direct_access_insert(&old_node);

    moved = std::move(original);

    REQUIRE(moved.direct_access_search(2) == &first);
    REQUIRE(moved.direct_access_search(7) == &second);
    REQUIRE(moved.direct_access_search(0) == nullptr);
    REQUIRE_THROWS_AS(moved.direct_access_search(10), std::out_of_range);
}

TEST_CASE("DirectAccessTable move assignment handles self-move-assignment") {
    dsa::data_structures::DirectAccessTable table(10);

    dsa::data_structures::Node node{4, 400};

    table.direct_access_insert(&node);

    table = std::move(table);

    REQUIRE(table.direct_access_search(4) == &node);
    REQUIRE(table.direct_access_search(4)->data == 400);
}