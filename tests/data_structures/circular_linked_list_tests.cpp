#include <catch2/catch_test_macros.hpp>

#include "data_structures/circular_linked_list.hpp"

#include <utility>

TEST_CASE("CircularLinkedList constructor creates an empty list") {
    dsa::data_structures::CircularLinkedList list;

    REQUIRE(list.empty());
    REQUIRE(list.size() == 0);
}

TEST_CASE("CircularLinkedList push_front inserts one element") {
    dsa::data_structures::CircularLinkedList list;

    list.push_front(10);

    REQUIRE_FALSE(list.empty());
    REQUIRE(list.size() == 1);

    dsa::data_structures::Node* node = list.list_search(10);

    REQUIRE(node != nullptr);
    REQUIRE(node->key == 10);
}

TEST_CASE("CircularLinkedList push_front inserts elements at the beginning") {
    dsa::data_structures::CircularLinkedList list;

    list.push_front(10);
    list.push_front(20);
    list.push_front(30);

    REQUIRE(list.size() == 3);

    dsa::data_structures::Node* first = list.list_search(30);
    dsa::data_structures::Node* second = first->next;
    dsa::data_structures::Node* third = second->next;

    REQUIRE(first->key == 30);
    REQUIRE(second->key == 20);
    REQUIRE(third->key == 10);

    REQUIRE(second->prev == first);
    REQUIRE(third->prev == second);
}

TEST_CASE("CircularLinkedList push_back inserts one element") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);

    REQUIRE_FALSE(list.empty());
    REQUIRE(list.size() == 1);

    dsa::data_structures::Node* node = list.list_search(10);

    REQUIRE(node != nullptr);
    REQUIRE(node->key == 10);
}

TEST_CASE("CircularLinkedList push_back inserts elements at the end") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    REQUIRE(list.size() == 3);

    dsa::data_structures::Node* first = list.list_search(10);
    dsa::data_structures::Node* second = first->next;
    dsa::data_structures::Node* third = second->next;

    REQUIRE(first->key == 10);
    REQUIRE(second->key == 20);
    REQUIRE(third->key == 30);

    REQUIRE(second->prev == first);
    REQUIRE(third->prev == second);
}

TEST_CASE("CircularLinkedList supports mixed push_front and push_back operations") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(20);
    list.push_front(10);
    list.push_back(30);
    list.push_front(5);

    REQUIRE(list.size() == 4);

    dsa::data_structures::Node* first = list.list_search(5);
    dsa::data_structures::Node* second = first->next;
    dsa::data_structures::Node* third = second->next;
    dsa::data_structures::Node* fourth = third->next;

    REQUIRE(first->key == 5);
    REQUIRE(second->key == 10);
    REQUIRE(third->key == 20);
    REQUIRE(fourth->key == 30);

    REQUIRE(second->prev == first);
    REQUIRE(third->prev == second);
    REQUIRE(fourth->prev == third);
}

TEST_CASE("CircularLinkedList list_search finds an existing key") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    dsa::data_structures::Node* node = list.list_search(20);

    REQUIRE(node != nullptr);
    REQUIRE(node->key == 20);
    REQUIRE(node->prev->key == 10);
    REQUIRE(node->next->key == 30);
}

TEST_CASE("CircularLinkedList list_search returns sentinel when key does not exist") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    dsa::data_structures::Node* result = list.list_search(99);

    REQUIRE(result != nullptr);

    // Because list_search returns nil_ when not found.
    // In this implementation, nil_->key is a dummy value.
    REQUIRE(result->key == 0);
    REQUIRE(result->next->key == 10);
    REQUIRE(result->prev->key == 30);
}

TEST_CASE("CircularLinkedList remove deletes the only node") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);
    list.remove(10);

    REQUIRE(list.empty());
    REQUIRE(list.size() == 0);
}

TEST_CASE("CircularLinkedList remove deletes the first node") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.remove(10);

    REQUIRE(list.size() == 2);

    dsa::data_structures::Node* first = list.list_search(20);
    dsa::data_structures::Node* second = first->next;

    REQUIRE(first->key == 20);
    REQUIRE(second->key == 30);
    REQUIRE(second->prev == first);
}

TEST_CASE("CircularLinkedList remove deletes the last node") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    list.remove(30);

    REQUIRE(list.size() == 2);

    dsa::data_structures::Node* first = list.list_search(10);
    dsa::data_structures::Node* second = first->next;

    REQUIRE(first->key == 10);
    REQUIRE(second->key == 20);
    REQUIRE(second->prev == first);
}

TEST_CASE("CircularLinkedList remove deletes a middle node") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);

    list.remove(20);

    REQUIRE(list.size() == 3);

    dsa::data_structures::Node* first = list.list_search(10);
    dsa::data_structures::Node* second = first->next;
    dsa::data_structures::Node* third = second->next;

    REQUIRE(first->key == 10);
    REQUIRE(second->key == 30);
    REQUIRE(third->key == 40);

    REQUIRE(second->prev == first);
    REQUIRE(third->prev == second);
}

// TEST_CASE("CircularLinkedList list_delete handles nullptr") {
//     dsa::data_structures::CircularLinkedList list;

//     list.push_back(10);
//     list.push_back(20);

//     list.list_delete(nullptr);

//     REQUIRE(list.size() == 2);
//     REQUIRE(list.list_search(10)->key == 10);
//     REQUIRE(list.list_search(20)->key == 20);
// }

TEST_CASE("CircularLinkedList copy constructor creates an independent copy") {
    dsa::data_structures::CircularLinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    dsa::data_structures::CircularLinkedList copy(original);

    REQUIRE(copy.size() == original.size());

    dsa::data_structures::Node* original_first = original.list_search(10);
    dsa::data_structures::Node* copy_first = copy.list_search(10);

    REQUIRE(copy_first != nullptr);
    REQUIRE(original_first != copy_first);

    REQUIRE(copy_first->key == 10);
    REQUIRE(copy_first->next->key == 20);
    REQUIRE(copy_first->next->next->key == 30);

    copy.push_back(40);

    REQUIRE(copy.size() == 4);
    REQUIRE(original.size() == 3);

    REQUIRE(original.list_search(40)->key == 0);
}

TEST_CASE("CircularLinkedList copy constructor works with an empty list") {
    dsa::data_structures::CircularLinkedList original;

    dsa::data_structures::CircularLinkedList copy(original);

    REQUIRE(copy.empty());
    REQUIRE(copy.size() == 0);
}

TEST_CASE("CircularLinkedList copy assignment creates an independent copy") {
    dsa::data_structures::CircularLinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    dsa::data_structures::CircularLinkedList copy;
    copy.push_back(99);

    copy = original;

    REQUIRE(copy.size() == original.size());

    dsa::data_structures::Node* original_first = original.list_search(10);
    dsa::data_structures::Node* copy_first = copy.list_search(10);

    REQUIRE(copy_first != nullptr);
    REQUIRE(original_first != copy_first);

    REQUIRE(copy_first->key == 10);
    REQUIRE(copy_first->next->key == 20);
    REQUIRE(copy_first->next->next->key == 30);

    copy.push_front(5);

    REQUIRE(copy.size() == 4);
    REQUIRE(original.size() == 3);

    REQUIRE(original.list_search(5)->key == 0);
}

TEST_CASE("CircularLinkedList copy assignment handles self-assignment") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);
    list.push_back(20);

    list = list;

    REQUIRE(list.size() == 2);
    REQUIRE(list.list_search(10)->key == 10);
    REQUIRE(list.list_search(20)->key == 20);
}

TEST_CASE("CircularLinkedList move constructor transfers ownership") {
    dsa::data_structures::CircularLinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    dsa::data_structures::Node* original_first = original.list_search(10);

    dsa::data_structures::CircularLinkedList moved(std::move(original));

    REQUIRE(moved.size() == 3);
    REQUIRE(moved.list_search(10) == original_first);

    REQUIRE(moved.list_search(10)->key == 10);
    REQUIRE(moved.list_search(20)->key == 20);
    REQUIRE(moved.list_search(30)->key == 30);

    REQUIRE(original.empty());
    REQUIRE(original.size() == 0);
}

TEST_CASE("CircularLinkedList move assignment transfers ownership") {
    dsa::data_structures::CircularLinkedList original;

    original.push_back(10);
    original.push_back(20);
    original.push_back(30);

    dsa::data_structures::Node* original_first = original.list_search(10);

    dsa::data_structures::CircularLinkedList moved;
    moved.push_back(99);

    moved = std::move(original);

    REQUIRE(moved.size() == 3);
    REQUIRE(moved.list_search(10) == original_first);

    REQUIRE(moved.list_search(10)->key == 10);
    REQUIRE(moved.list_search(20)->key == 20);
    REQUIRE(moved.list_search(30)->key == 30);

    REQUIRE(original.empty());
    REQUIRE(original.size() == 0);
}

TEST_CASE("CircularLinkedList move assignment handles self-move-assignment") {
    dsa::data_structures::CircularLinkedList list;

    list.push_back(10);
    list.push_back(20);

    list = std::move(list);

    REQUIRE(list.size() == 2);
    REQUIRE(list.list_search(10)->key == 10);
    REQUIRE(list.list_search(20)->key == 20);
}