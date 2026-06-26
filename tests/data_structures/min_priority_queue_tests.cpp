#include <catch2/catch_test_macros.hpp>

#include "data_structures/min_priority_queue.hpp"

#include <stdexcept>
#include <utility>
#include <vector>

namespace {

bool is_valid_min_priority_queue_order(
    dsa::data_structures::MinPriorityQueue& queue,
    const std::vector<std::size_t>& expected_keys
) {
    for (std::size_t expected_key : expected_keys) {
        dsa::data_structures::Node* node = queue.extract_min();

        if (node == nullptr || node->key != expected_key) {
            return false;
        }
    }

    return queue.heap_size() == 0;
}

}  // namespace

TEST_CASE("MinPriorityQueue constructor initializes capacity and heap size") {
    dsa::data_structures::MinPriorityQueue queue(10);

    REQUIRE(queue.capacity() == 10);
    REQUIRE(queue.heap_size() == 0);
}

TEST_CASE("MinPriorityQueue constructor throws when capacity is zero") {
    REQUIRE_THROWS_AS(
        dsa::data_structures::MinPriorityQueue(0),
        std::underflow_error
    );
}

TEST_CASE("MinPriorityQueue minimum throws when queue is empty") {
    dsa::data_structures::MinPriorityQueue queue(10);

    REQUIRE_THROWS_AS(queue.minimum(), std::underflow_error);
}

TEST_CASE("MinPriorityQueue extract_min throws when queue is empty") {
    dsa::data_structures::MinPriorityQueue queue(10);

    REQUIRE_THROWS_AS(queue.extract_min(), std::underflow_error);
}

TEST_CASE("MinPriorityQueue insert stores one node") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node node{10, 100};

    queue.insert(&node);

    REQUIRE(queue.heap_size() == 1);
    REQUIRE(queue.minimum() == &node);
    REQUIRE(queue.minimum()->key == 10);
    REQUIRE(queue.minimum()->data == 100);
    REQUIRE(node.heap_index == 0);
}

TEST_CASE("MinPriorityQueue insert throws when node is null") {
    dsa::data_structures::MinPriorityQueue queue(10);

    REQUIRE_THROWS_AS(queue.insert(nullptr), std::invalid_argument);
}

TEST_CASE("MinPriorityQueue insert throws when queue is full") {
    dsa::data_structures::MinPriorityQueue queue(2);

    dsa::data_structures::Node first{10, 100};
    dsa::data_structures::Node second{20, 200};
    dsa::data_structures::Node third{30, 300};

    queue.insert(&first);
    queue.insert(&second);

    REQUIRE(queue.heap_size() == 2);

    REQUIRE_THROWS_AS(queue.insert(&third), std::overflow_error);
}

TEST_CASE("MinPriorityQueue minimum returns node with smallest key") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node low{10, 100};
    dsa::data_structures::Node high{50, 500};
    dsa::data_structures::Node mid{30, 300};

    queue.insert(&low);
    queue.insert(&high);
    queue.insert(&mid);

    REQUIRE(queue.heap_size() == 3);
    REQUIRE(queue.minimum() == &low);
    REQUIRE(queue.minimum()->key == 10);
    REQUIRE(queue.minimum()->data == 100);
}

TEST_CASE("MinPriorityQueue extract_min removes nodes in ascending key order") {
    dsa::data_structures::MinPriorityQueue queue(10);

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

    REQUIRE(queue.extract_min() == &a);
    REQUIRE(queue.heap_size() == 4);

    REQUIRE(queue.extract_min() == &e);
    REQUIRE(queue.heap_size() == 3);

    REQUIRE(queue.extract_min() == &c);
    REQUIRE(queue.heap_size() == 2);

    REQUIRE(queue.extract_min() == &b);
    REQUIRE(queue.heap_size() == 1);

    REQUIRE(queue.extract_min() == &d);
    REQUIRE(queue.heap_size() == 0);
}

TEST_CASE("MinPriorityQueue extract_min preserves node data association") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    queue.insert(&a);
    queue.insert(&b);
    queue.insert(&c);

    dsa::data_structures::Node* min = queue.extract_min();

    REQUIRE(min == &a);
    REQUIRE(min->key == 10);
    REQUIRE(min->data == 100);
}

TEST_CASE("MinPriorityQueue extract_min handles one element") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node node{42, 420};

    queue.insert(&node);

    REQUIRE(queue.heap_size() == 1);

    dsa::data_structures::Node* result = queue.extract_min();

    REQUIRE(result == &node);
    REQUIRE(result->key == 42);
    REQUIRE(result->data == 420);
    REQUIRE(queue.heap_size() == 0);
}

TEST_CASE("MinPriorityQueue decrease_key moves node upward") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{20, 200};
    dsa::data_structures::Node c{30, 300};

    queue.insert(&a);
    queue.insert(&b);
    queue.insert(&c);

    REQUIRE(queue.minimum() == &a);

    queue.decrease_key(&c, 1);

    REQUIRE(queue.minimum() == &c);
    REQUIRE(queue.minimum()->key == 1);
    REQUIRE(queue.minimum()->data == 300);
}

TEST_CASE("MinPriorityQueue decrease_key throws when node is null") {
    dsa::data_structures::MinPriorityQueue queue(10);

    REQUIRE_THROWS_AS(
        queue.decrease_key(nullptr, 1),
        std::invalid_argument
    );
}

TEST_CASE("MinPriorityQueue decrease_key throws when new key is greater") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node node{50, 500};

    queue.insert(&node);

    REQUIRE_THROWS_AS(
        queue.decrease_key(&node, 100),
        std::invalid_argument
    );
}

TEST_CASE("MinPriorityQueue decrease_key throws when node is not in queue") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node inside{10, 100};
    dsa::data_structures::Node outside{20, 200};

    queue.insert(&inside);

    REQUIRE_THROWS_AS(
        queue.decrease_key(&outside, 1),
        std::invalid_argument
    );
}

TEST_CASE("MinPriorityQueue supports duplicate keys") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node a{20, 100};
    dsa::data_structures::Node b{20, 200};
    dsa::data_structures::Node c{10, 300};

    queue.insert(&a);
    queue.insert(&b);
    queue.insert(&c);

    REQUIRE(queue.heap_size() == 3);

    dsa::data_structures::Node* first = queue.extract_min();
    dsa::data_structures::Node* second = queue.extract_min();
    dsa::data_structures::Node* third = queue.extract_min();

    REQUIRE(first->key == 10);
    REQUIRE(second->key == 20);
    REQUIRE(third->key == 20);
}

TEST_CASE("MinPriorityQueue handles key zero") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node zero{0, 100};
    dsa::data_structures::Node high{10, 200};

    queue.insert(&zero);
    queue.insert(&high);

    REQUIRE(queue.heap_size() == 2);
    REQUIRE(queue.extract_min() == &zero);
    REQUIRE(queue.extract_min() == &high);
}

TEST_CASE("MinPriorityQueue copy constructor copies queue state") {
    dsa::data_structures::MinPriorityQueue original(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    original.insert(&a);
    original.insert(&b);
    original.insert(&c);

    dsa::data_structures::MinPriorityQueue copy(original);

    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.heap_size() == original.heap_size());

    REQUIRE(copy.extract_min() == &a);
    REQUIRE(copy.extract_min() == &c);
    REQUIRE(copy.extract_min() == &b);

    REQUIRE(original.heap_size() == 3);
    REQUIRE(original.minimum() == &a);
}

TEST_CASE("MinPriorityQueue copy assignment copies queue state") {
    dsa::data_structures::MinPriorityQueue original(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    original.insert(&a);
    original.insert(&b);
    original.insert(&c);

    dsa::data_structures::MinPriorityQueue copy(2);

    dsa::data_structures::Node old_node{99, 999};
    copy.insert(&old_node);

    copy = original;

    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.heap_size() == original.heap_size());

    REQUIRE(copy.extract_min() == &a);
    REQUIRE(copy.extract_min() == &c);
    REQUIRE(copy.extract_min() == &b);

    REQUIRE(original.heap_size() == 3);
    REQUIRE(original.minimum() == &a);
}

TEST_CASE("MinPriorityQueue copy assignment handles self-assignment") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};

    queue.insert(&a);
    queue.insert(&b);

    queue = queue;

    REQUIRE(queue.heap_size() == 2);
    REQUIRE(queue.minimum() == &a);
}

TEST_CASE("MinPriorityQueue move constructor transfers queue state") {
    dsa::data_structures::MinPriorityQueue original(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    original.insert(&a);
    original.insert(&b);
    original.insert(&c);

    dsa::data_structures::MinPriorityQueue moved(std::move(original));

    REQUIRE(moved.capacity() == 10);
    REQUIRE(moved.heap_size() == 3);

    REQUIRE(moved.extract_min() == &a);
    REQUIRE(moved.extract_min() == &c);
    REQUIRE(moved.extract_min() == &b);
}

TEST_CASE("MinPriorityQueue move assignment transfers queue state") {
    dsa::data_structures::MinPriorityQueue original(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};
    dsa::data_structures::Node c{30, 300};

    original.insert(&a);
    original.insert(&b);
    original.insert(&c);

    dsa::data_structures::MinPriorityQueue moved(2);

    dsa::data_structures::Node old_node{99, 999};
    moved.insert(&old_node);

    moved = std::move(original);

    REQUIRE(moved.capacity() == 10);
    REQUIRE(moved.heap_size() == 3);

    REQUIRE(moved.extract_min() == &a);
    REQUIRE(moved.extract_min() == &c);
    REQUIRE(moved.extract_min() == &b);
}

TEST_CASE("MinPriorityQueue move assignment handles self-move-assignment") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{50, 500};

    queue.insert(&a);
    queue.insert(&b);

    queue = std::move(queue);

    REQUIRE(queue.heap_size() == 2);
    REQUIRE(queue.minimum() == &a);
}

TEST_CASE("MinPriorityQueue heap_index is updated after decrease_key") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{20, 200};
    dsa::data_structures::Node c{30, 300};

    queue.insert(&a);
    queue.insert(&b);
    queue.insert(&c);

    queue.decrease_key(&c, 1);

    REQUIRE(c.heap_index == 0);
    REQUIRE(queue.minimum() == &c);

    REQUIRE(queue.extract_min() == &c);
    REQUIRE(queue.extract_min() == &a);
    REQUIRE(queue.extract_min() == &b);
}

TEST_CASE("MinPriorityQueue heap_index is updated after extract_min and heapify") {
    dsa::data_structures::MinPriorityQueue queue(10);

    dsa::data_structures::Node a{10, 100};
    dsa::data_structures::Node b{20, 200};
    dsa::data_structures::Node c{30, 300};
    dsa::data_structures::Node d{40, 400};

    queue.insert(&a);
    queue.insert(&b);
    queue.insert(&c);
    queue.insert(&d);

    REQUIRE(queue.extract_min() == &a);

    queue.decrease_key(&d, 5);

    REQUIRE(queue.minimum() == &d);
    REQUIRE(queue.extract_min() == &d);
    REQUIRE(queue.extract_min() == &b);
    REQUIRE(queue.extract_min() == &c);
}