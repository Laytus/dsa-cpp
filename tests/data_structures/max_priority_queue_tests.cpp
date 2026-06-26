#include <catch2/catch_test_macros.hpp>

#include "data_structures/max_priority_queue.hpp"

#include <stdexcept>
#include <vector>
#include <utility>

namespace {

bool is_valid_max_priority_queue_order(
    dsa::data_structures::MaxPriorityQueue& queue,
    const std::vector<std::size_t>& expected_keys
) {
    for (std::size_t expected_key : expected_keys) {
        dsa::data_structures::Node* node = queue.extract_max();

        if (node == nullptr || node->key != expected_key) {
            return false;
        }
    }

    return queue.heap_size() == 0;
}

}  // namespace

TEST_CASE("MaxPriorityQueue constructor initializes capacity and heap size") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    REQUIRE(queue.capacity() == 10);
    REQUIRE(queue.heap_size() == 0);
}

TEST_CASE("MaxPriorityQueue constructor throws when capacity is zero") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::MaxPriorityQueue(0),
        std::underflow_error
    );
}

TEST_CASE("MaxPriorityQueue maximum throws when queue is empty") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    REQUIRE_THROWS_AS(queue.maximum(), std::underflow_error);
}

TEST_CASE("MaxPriorityQueue extract_max throws when queue is empty") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    REQUIRE_THROWS_AS(queue.extract_max(), std::underflow_error);
}

TEST_CASE("MaxPriorityQueue insert stores one node") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node node{10, 100};

    queue.insert(&node);

    REQUIRE(queue.heap_size() == 1);
    REQUIRE(queue.maximum() == &node);
    REQUIRE(queue.maximum()->key == 10);
    REQUIRE(queue.maximum()->data == 100);
}

TEST_CASE("MaxPriorityQueue insert throws when node is null") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    REQUIRE_THROWS_AS(queue.insert(nullptr), std::invalid_argument);
}

TEST_CASE("MaxPriorityQueue insert throws when queue is full") {
    dsa::data_structures::MaxPriorityQueue queue(2);

    dsa::data_structures::Node first{10, 100};
    dsa::data_structures::Node second{20, 200};
    dsa::data_structures::Node third{30, 300};

    queue.insert(&first);
    queue.insert(&second);

    REQUIRE(queue.heap_size() == 2);

    REQUIRE_THROWS_AS(queue.insert(&third), std::overflow_error);
}

TEST_CASE("MaxPriorityQueue maximum returns node with largest key") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node low{10, 100};
    dsa::data_structures::Node high{50, 500};
    dsa::data_structures::Node mid{30, 300};

    queue.insert(&low);
    queue.insert(&high);
    queue.insert(&mid);

    REQUIRE(queue.heap_size() == 3);
    REQUIRE(queue.maximum() == &high);
    REQUIRE(queue.maximum()->key == 50);
    REQUIRE(queue.maximum()->data == 500);
}

TEST_CASE("MaxPriorityQueue extract_max removes nodes in descending key order") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};
    dsa::data_structures::Node d{70, 700};
    dsa::data_structures::Node e{20, 200};

    queue.insert(&a);
    queue.insert(&b);
    queue.insert(&c);
    queue.insert(&d);
    queue.insert(&e);

    REQUIRE(queue.heap_size() == 5);

    REQUIRE(queue.extract_max() == &d);
    REQUIRE(queue.heap_size() == 4);

    REQUIRE(queue.extract_max() == &b);
    REQUIRE(queue.heap_size() == 3);

    REQUIRE(queue.extract_max() == &c);
    REQUIRE(queue.heap_size() == 2);

    REQUIRE(queue.extract_max() == &e);
    REQUIRE(queue.heap_size() == 1);

    REQUIRE(queue.extract_max() == &a);
    REQUIRE(queue.heap_size() == 0);
}

TEST_CASE("MaxPriorityQueue extract_max preserves node data association") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    queue.insert(&a);
    queue.insert(&b);
    queue.insert(&c);

    dsa::data_structures::Node* max = queue.extract_max();

    REQUIRE(max == &b);
    REQUIRE(max->key == 50);
    REQUIRE(max->data == 500);
}

TEST_CASE("MaxPriorityQueue extract_max handles one element") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node node{42, 420};

    queue.insert(&node);

    REQUIRE(queue.heap_size() == 1);

    dsa::data_structures::Node* result = queue.extract_max();

    REQUIRE(result == &node);
    REQUIRE(result->key == 42);
    REQUIRE(result->data == 420);
    REQUIRE(queue.heap_size() == 0);
}

TEST_CASE("MaxPriorityQueue increase_key moves node upward") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{20, 200};
    dsa::data_structures::Node c{30, 300};

    queue.insert(&a);
    queue.insert(&b);
    queue.insert(&c);

    REQUIRE(queue.maximum() == &c);

    queue.increase_key(&a, 100);

    REQUIRE(queue.maximum() == &a);
    REQUIRE(queue.maximum()->key == 100);
    REQUIRE(queue.maximum()->data == 100);
}

TEST_CASE("MaxPriorityQueue increase_key throws when node is null") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    REQUIRE_THROWS_AS(
        queue.increase_key(nullptr, 100),
        std::invalid_argument
    );
}

TEST_CASE("MaxPriorityQueue increase_key throws when new key is smaller") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node node{50, 500};

    queue.insert(&node);

    REQUIRE_THROWS_AS(
        queue.increase_key(&node, 10),
        std::invalid_argument
    );
}

TEST_CASE("MaxPriorityQueue increase_key throws when node is not in queue") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node inside{10, 100};
    dsa::data_structures::Node outside{20, 200};

    queue.insert(&inside);

    REQUIRE_THROWS_AS(
        queue.increase_key(&outside, 50),
        std::invalid_argument
    );
}

TEST_CASE("MaxPriorityQueue supports duplicate keys") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node a{20, 100};
    dsa::data_structures::Node b{20, 200};
    dsa::data_structures::Node c{10, 300};

    queue.insert(&a);
    queue.insert(&b);
    queue.insert(&c);

    REQUIRE(queue.heap_size() == 3);

    dsa::data_structures::Node* first = queue.extract_max();
    dsa::data_structures::Node* second = queue.extract_max();
    dsa::data_structures::Node* third = queue.extract_max();

    REQUIRE(first->key == 20);
    REQUIRE(second->key == 20);
    REQUIRE(third->key == 10);
}

TEST_CASE("MaxPriorityQueue handles key zero") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node zero{0, 100};
    dsa::data_structures::Node high{10, 200};

    queue.insert(&zero);
    queue.insert(&high);

    REQUIRE(queue.heap_size() == 2);
    REQUIRE(queue.extract_max() == &high);
    REQUIRE(queue.extract_max() == &zero);
}

TEST_CASE("MaxPriorityQueue copy constructor copies queue state") {
    dsa::data_structures::MaxPriorityQueue original(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    original.insert(&a);
    original.insert(&b);
    original.insert(&c);

    dsa::data_structures::MaxPriorityQueue copy(original);

    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.heap_size() == original.heap_size());

    REQUIRE(copy.extract_max() == &b);
    REQUIRE(copy.extract_max() == &c);
    REQUIRE(copy.extract_max() == &a);

    REQUIRE(original.heap_size() == 3);
    REQUIRE(original.maximum() == &b);
}

TEST_CASE("MaxPriorityQueue copy assignment copies queue state") {
    dsa::data_structures::MaxPriorityQueue original(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    original.insert(&a);
    original.insert(&b);
    original.insert(&c);

    dsa::data_structures::MaxPriorityQueue copy(2);

    dsa::data_structures::Node old_node{99, 999};
    copy.insert(&old_node);

    copy = original;

    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.heap_size() == original.heap_size());

    REQUIRE(copy.extract_max() == &b);
    REQUIRE(copy.extract_max() == &c);
    REQUIRE(copy.extract_max() == &a);

    REQUIRE(original.heap_size() == 3);
    REQUIRE(original.maximum() == &b);
}

TEST_CASE("MaxPriorityQueue copy assignment handles self-assignment") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};

    queue.insert(&a);
    queue.insert(&b);

    queue = queue;

    REQUIRE(queue.heap_size() == 2);
    REQUIRE(queue.maximum() == &b);
}

TEST_CASE("MaxPriorityQueue move constructor transfers queue state") {
    dsa::data_structures::MaxPriorityQueue original(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    original.insert(&a);
    original.insert(&b);
    original.insert(&c);

    dsa::data_structures::MaxPriorityQueue moved(std::move(original));

    REQUIRE(moved.capacity() == 10);
    REQUIRE(moved.heap_size() == 3);

    REQUIRE(moved.extract_max() == &b);
    REQUIRE(moved.extract_max() == &c);
    REQUIRE(moved.extract_max() == &a);
}

TEST_CASE("MaxPriorityQueue move assignment transfers queue state") {
    dsa::data_structures::MaxPriorityQueue original(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    original.insert(&a);
    original.insert(&b);
    original.insert(&c);

    dsa::data_structures::MaxPriorityQueue moved(2);

    dsa::data_structures::Node old_node{99, 999};
    moved.insert(&old_node);

    moved = std::move(original);

    REQUIRE(moved.capacity() == 10);
    REQUIRE(moved.heap_size() == 3);

    REQUIRE(moved.extract_max() == &b);
    REQUIRE(moved.extract_max() == &c);
    REQUIRE(moved.extract_max() == &a);
}

TEST_CASE("MaxPriorityQueue move assignment handles self-move-assignment") {
    dsa::data_structures::MaxPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};

    queue.insert(&a);
    queue.insert(&b);

    queue = std::move(queue);

    REQUIRE(queue.heap_size() == 2);
    REQUIRE(queue.maximum() == &b);
}