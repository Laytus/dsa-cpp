#include <catch2/catch_test_macros.hpp>

#include "data_structures/linked_list.hpp"

#include <utility>

TEST_CASE("LinkedList constructor creates an empty list") {
    dsa::data_structures::LinkedList list;

    REQUIRE(list.empty());
    REQUIRE(list.size() == 0);
    REQUIRE(list.head() == nullptr);
    REQUIRE(list.tail() == nullptr);
}

TEST_CASE("LinkedList push_front inserts one node into an empty list") {
    dsa::data_structures::LinkedList list;

    list.push_front(10);

    REQUIRE_FALSE(list.empty());
    REQUIRE(list.size() == 1);
    REQUIRE(list.head() != nullptr);
    REQUIRE(list.tail() != nullptr);
    REQUIRE(list.head() == list.tail());
    REQUIRE(list.head()->key == 10);
    REQUIRE(list.head()->prev == nullptr);
    REQUIRE(list.head()->next == nullptr);
}

TEST_CASE("LinkedList push_front inserts nodes at the beginning") {
    dsa::data_structures::LinkedList list;

    list.push_front(10);
    list.push_front(20);
    list.push_front(30);

    REQUIRE(list.size() == 3);

    REQUIRE(list.head()->key == 30);
    REQUIRE(list.head()->next->key == 20);
    REQUIRE(list.head()->next->next->key == 10);
    REQUIRE(list.tail()->key == 10);

    REQUIRE(list.head()->prev == nullptr);
    REQUIRE(list.tail()->next == nullptr);

    REQUIRE(list.head()->next->prev == list.head());
    REQUIRE(list.tail()->prev->key == 20);
}

TEST_CASE("LinkedList push_back inserts one node into an empty list") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);

    REQUIRE_FALSE(list.empty());
    REQUIRE(list.size() == 1);
    REQUIRE(list.head() != nullptr);
    REQUIRE(list.tail() != nullptr);
    REQUIRE(list.head() == list.tail());
    REQUIRE(list.head()->key == 10);
    REQUIRE(list.head()->prev == nullptr);
    REQUIRE(list.head()->next == nullptr);
}

TEST_CASE("LinkedList push_back inserts nodes at the end") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    REQUIRE(list.size() == 3);

    REQUIRE(list.head()->key == 10);
    REQUIRE(list.head()->next->key == 20);
    REQUIRE(list.head()->next->next->key == 30);
    REQUIRE(list.tail()->key == 30);

    REQUIRE(list.head()->prev == nullptr);
    REQUIRE(list.tail()->next == nullptr);

    REQUIRE(list.head()->next->prev == list.head());
    REQUIRE(list.tail()->prev->key == 20);
}

TEST_CASE("LinkedList supports mixed push_front and push_back operations") {
    dsa::data_structures::LinkedList list;

    list.push_back(20);
    list.push_front(10);
    list.push_back(30);
    list.push_front(5);

    REQUIRE(list.size() == 4);

    REQUIRE(list.head()->key == 5);
    REQUIRE(list.head()->next->key == 10);
    REQUIRE(list.head()->next->next->key == 20);
    REQUIRE(list.head()->next->next->next->key == 30);
    REQUIRE(list.tail()->key == 30);

    REQUIRE(list.head()->prev == nullptr);
    REQUIRE(list.tail()->next == nullptr);
}

TEST_CASE("LinkedList list_search finds an existing key") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    dsa::data_structures::Node* node = list.list_search(20);

    REQUIRE(node != nullptr);
    REQUIRE(node->key == 20);
    REQUIRE(node->prev != nullptr);
    REQUIRE(node->prev->key == 10);
    REQUIRE(node->next != nullptr);
    REQUIRE(node->next->key == 30);
}

TEST_CASE("LinkedList list_search returns nullptr when key does not exist") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    REQUIRE(list.list_search(99) == nullptr);
}

TEST_CASE("LinkedList list_delete removes the only node") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);

    dsa::data_structures::Node* node = list.list_search(10);
    list.list_delete(node);

    REQUIRE(list.empty());
    REQUIRE(list.size() == 0);
    REQUIRE(list.head() == nullptr);
    REQUIRE(list.tail() == nullptr);
}

TEST_CASE("LinkedList list_delete removes the head node") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    dsa::data_structures::Node* node = list.list_search(10);
    list.list_delete(node);

    REQUIRE(list.size() == 2);
    REQUIRE(list.head() != nullptr);
    REQUIRE(list.head()->key == 20);
    REQUIRE(list.head()->prev == nullptr);
    REQUIRE(list.head()->next->key == 30);
    REQUIRE(list.tail()->key == 30);
}

TEST_CASE("LinkedList list_delete removes the tail node") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    dsa::data_structures::Node* node = list.list_search(30);
    list.list_delete(node);

    REQUIRE(list.size() == 2);
    REQUIRE(list.head()->key == 10);
    REQUIRE(list.tail() != nullptr);
    REQUIRE(list.tail()->key == 20);
    REQUIRE(list.tail()->next == nullptr);
    REQUIRE(list.tail()->prev->key == 10);
}

TEST_CASE("LinkedList list_delete removes a middle node") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    dsa::data_structures::Node* node = list.list_search(20);
    list.list_delete(node);

    REQUIRE(list.size() == 3);

    REQUIRE(list.head()->key == 10);
    REQUIRE(list.head()->next->key == 30);
    REQUIRE(list.head()->next->prev == list.head());
    REQUIRE(list.head()->next->next->key == 40);
    REQUIRE(list.tail()->key == 40);
}

TEST_CASE("LinkedList list_delete handles nullptr") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);
    list.push_back(20);

    list.list_delete(nullptr);

    REQUIRE(list.size() == 2);
    REQUIRE(list.head()->key == 10);
    REQUIRE(list.tail()->key == 20);
}

TEST_CASE("LinkedList copy constructor creates an independent copy") {
    dsa::data_structures::LinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    dsa::data_structures::LinkedList copy(original);

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.head() != original.head());
    REQUIRE(copy.tail() != original.tail());

    REQUIRE(copy.head()->key == 10);
    REQUIRE(copy.head()->next->key == 20);
    REQUIRE(copy.tail()->key == 30);

    copy.push_back(40);

    REQUIRE(copy.size() == 4);
    REQUIRE(copy.tail()->key == 40);

    REQUIRE(original.size() == 3);
    REQUIRE(original.tail()->key == 30);
}

TEST_CASE("LinkedList copy constructor works with an empty list") {
    dsa::data_structures::LinkedList original;

    dsa::data_structures::LinkedList copy(original);

    REQUIRE(copy.empty());
    REQUIRE(copy.size() == 0);
    REQUIRE(copy.head() == nullptr);
    REQUIRE(copy.tail() == nullptr);
}

TEST_CASE("LinkedList copy assignment creates an independent copy") {
    dsa::data_structures::LinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    dsa::data_structures::LinkedList copy;
    copy.push_back(99);

    copy = original;

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.head() != original.head());
    REQUIRE(copy.tail() != original.tail());

    REQUIRE(copy.head()->key == 10);
    REQUIRE(copy.head()->next->key == 20);
    REQUIRE(copy.tail()->key == 30);

    copy.push_front(5);

    REQUIRE(copy.size() == 4);
    REQUIRE(copy.head()->key == 5);

    REQUIRE(original.size() == 3);
    REQUIRE(original.head()->key == 10);
}

TEST_CASE("LinkedList copy assignment handles self-assignment") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);
    list.push_back(20);

    list = list;

    REQUIRE(list.size() == 2);
    REQUIRE(list.head()->key == 10);
    REQUIRE(list.tail()->key == 20);
}

TEST_CASE("LinkedList move constructor transfers ownership") {
    dsa::data_structures::LinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    dsa::data_structures::Node* original_head = original.head();
    dsa::data_structures::Node* original_tail = original.tail();

    dsa::data_structures::LinkedList moved(std::move(original));

    REQUIRE(moved.size() == 3);
    REQUIRE(moved.head() == original_head);
    REQUIRE(moved.tail() == original_tail);

    REQUIRE(moved.head()->key == 10);
    REQUIRE(moved.tail()->key == 30);

    REQUIRE(original.empty());
    REQUIRE(original.size() == 0);
    REQUIRE(original.head() == nullptr);
    REQUIRE(original.tail() == nullptr);
}

TEST_CASE("LinkedList move assignment transfers ownership") {
    dsa::data_structures::LinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    dsa::data_structures::Node* original_head = original.head();
    dsa::data_structures::Node* original_tail = original.tail();

    dsa::data_structures::LinkedList moved;
    moved.push_back(99);

    moved = std::move(original);

    REQUIRE(moved.size() == 3);
    REQUIRE(moved.head() == original_head);
    REQUIRE(moved.tail() == original_tail);

    REQUIRE(moved.head()->key == 10);
    REQUIRE(moved.tail()->key == 30);

    REQUIRE(original.empty());
    REQUIRE(original.size() == 0);
    REQUIRE(original.head() == nullptr);
    REQUIRE(original.tail() == nullptr);
}

TEST_CASE("LinkedList move assignment handles self-move-assignment") {
    dsa::data_structures::LinkedList list;

    list.push_back(10);
    list.push_back(20);

    list = std::move(list);

    REQUIRE(list.size() == 2);
    REQUIRE(list.head() != nullptr);
    REQUIRE(list.tail() != nullptr);
    REQUIRE(list.head()->key == 10);
    REQUIRE(list.tail()->key == 20);
}