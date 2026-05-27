#include <catch2/catch_test_macros.hpp>

#include "data_structures/queue.hpp"

#include <stdexcept>
#include <utility>

TEST_CASE("Queue constructor creates an empty queue") {
    dsa::data_structures::Queue queue(4);

    REQUIRE(queue.empty());
    REQUIRE_FALSE(queue.full());
    REQUIRE(queue.size() == 0);
    REQUIRE(queue.capacity() == 4);
}

TEST_CASE("Queue constructor throws when capacity is zero") {
    REQUIRE_THROWS_AS(dsa::data_structures::Queue(0), std::underflow_error);
}

TEST_CASE("Queue enqueue adds one element") {
    dsa::data_structures::Queue queue(4);

    queue.enqueue(10);

    REQUIRE_FALSE(queue.empty());
    REQUIRE(queue.size() == 1);
    REQUIRE(queue.head() == 10);
    REQUIRE(queue.tail() == 10);
}

TEST_CASE("Queue enqueue adds several elements") {
    dsa::data_structures::Queue queue(4);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    REQUIRE(queue.size() == 3);
    REQUIRE(queue.full());
    REQUIRE(queue.head() == 10);
    REQUIRE(queue.tail() == 30);
}

TEST_CASE("Queue dequeue returns the first inserted element") {
    dsa::data_structures::Queue queue(4);

    queue.enqueue(10);
    queue.enqueue(20);

    REQUIRE(queue.dequeue() == 10);
    REQUIRE(queue.size() == 1);
    REQUIRE(queue.head() == 20);
    REQUIRE(queue.tail() == 20);
}

TEST_CASE("Queue follows FIFO order") {
    dsa::data_structures::Queue queue(5);

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);

    REQUIRE(queue.dequeue() == 1);
    REQUIRE(queue.dequeue() == 2);
    REQUIRE(queue.dequeue() == 3);
    REQUIRE(queue.dequeue() == 4);
    REQUIRE(queue.empty());
}

TEST_CASE("Queue head returns the first element without removing it") {
    dsa::data_structures::Queue queue(4);

    queue.enqueue(42);

    REQUIRE(queue.head() == 42);
    REQUIRE(queue.size() == 1);

    REQUIRE(queue.head() == 42);
    REQUIRE(queue.size() == 1);
}

TEST_CASE("Queue tail returns the last inserted element without removing it") {
    dsa::data_structures::Queue queue(4);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    REQUIRE(queue.tail() == 30);
    REQUIRE(queue.size() == 3);

    REQUIRE(queue.tail() == 30);
    REQUIRE(queue.size() == 3);
}

TEST_CASE("Queue dequeue throws underflow when queue is empty") {
    dsa::data_structures::Queue queue(4);

    REQUIRE_THROWS_AS(queue.dequeue(), std::underflow_error);
}

TEST_CASE("Queue head throws underflow when queue is empty") {
    dsa::data_structures::Queue queue(4);

    REQUIRE_THROWS_AS(queue.head(), std::underflow_error);
}

TEST_CASE("Queue tail throws underflow when queue is empty") {
    dsa::data_structures::Queue queue(4);

    REQUIRE_THROWS_AS(queue.tail(), std::underflow_error);
}

TEST_CASE("Queue enqueue throws overflow when queue is full") {
    dsa::data_structures::Queue queue(4);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    REQUIRE(queue.full());
    REQUIRE_THROWS_AS(queue.enqueue(40), std::overflow_error);
}

TEST_CASE("Queue size updates correctly after enqueue and dequeue") {
    dsa::data_structures::Queue queue(5);

    REQUIRE(queue.size() == 0);

    queue.enqueue(10);
    REQUIRE(queue.size() == 1);

    queue.enqueue(20);
    REQUIRE(queue.size() == 2);

    queue.dequeue();
    REQUIRE(queue.size() == 1);

    queue.dequeue();
    REQUIRE(queue.size() == 0);
    REQUIRE(queue.empty());
}

TEST_CASE("Queue supports circular wrap-around after dequeue") {
    dsa::data_structures::Queue queue(5);

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);

    REQUIRE(queue.full());

    REQUIRE(queue.dequeue() == 1);
    REQUIRE(queue.dequeue() == 2);

    REQUIRE(queue.size() == 2);
    REQUIRE_FALSE(queue.full());

    queue.enqueue(5);
    queue.enqueue(6);

    REQUIRE(queue.full());
    REQUIRE(queue.size() == 4);

    REQUIRE(queue.dequeue() == 3);
    REQUIRE(queue.dequeue() == 4);
    REQUIRE(queue.dequeue() == 5);
    REQUIRE(queue.dequeue() == 6);

    REQUIRE(queue.empty());
}

TEST_CASE("Queue head and tail work correctly after circular wrap-around") {
    dsa::data_structures::Queue queue(5);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);

    REQUIRE(queue.dequeue() == 10);
    REQUIRE(queue.dequeue() == 20);

    queue.enqueue(50);
    queue.enqueue(60);

    REQUIRE(queue.head() == 30);
    REQUIRE(queue.tail() == 60);
    REQUIRE(queue.full());
}

TEST_CASE("Queue can become empty after wrap-around") {
    dsa::data_structures::Queue queue(4);

    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    REQUIRE(queue.full());

    REQUIRE(queue.dequeue() == 1);
    REQUIRE(queue.dequeue() == 2);

    queue.enqueue(4);
    queue.enqueue(5);

    REQUIRE(queue.full());

    REQUIRE(queue.dequeue() == 3);
    REQUIRE(queue.dequeue() == 4);
    REQUIRE(queue.dequeue() == 5);

    REQUIRE(queue.empty());
    REQUIRE(queue.size() == 0);
}

TEST_CASE("Queue copy constructor creates an independent copy") {
    dsa::data_structures::Queue original(5);

    original.enqueue(10);
    original.enqueue(20);
    original.enqueue(30);

    dsa::data_structures::Queue copy(original);

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.head() == 10);
    REQUIRE(copy.tail() == 30);

    copy.dequeue();
    copy.enqueue(40);

    REQUIRE(copy.head() == 20);
    REQUIRE(copy.tail() == 40);
    REQUIRE(original.head() == 10);
    REQUIRE(original.tail() == 30);
}

TEST_CASE("Queue copy constructor works after wrap-around") {
    dsa::data_structures::Queue original(5);

    original.enqueue(1);
    original.enqueue(2);
    original.enqueue(3);
    original.enqueue(4);

    REQUIRE(original.dequeue() == 1);
    REQUIRE(original.dequeue() == 2);

    original.enqueue(5);
    original.enqueue(6);

    dsa::data_structures::Queue copy(original);

    REQUIRE(copy.size() == 4);
    REQUIRE(copy.full());
    REQUIRE(copy.dequeue() == 3);
    REQUIRE(copy.dequeue() == 4);
    REQUIRE(copy.dequeue() == 5);
    REQUIRE(copy.dequeue() == 6);
    REQUIRE(copy.empty());

    REQUIRE(original.size() == 4);
    REQUIRE(original.head() == 3);
    REQUIRE(original.tail() == 6);
}

TEST_CASE("Queue copy assignment creates an independent copy") {
    dsa::data_structures::Queue original(5);

    original.enqueue(10);
    original.enqueue(20);
    original.enqueue(30);

    dsa::data_structures::Queue copy(4);
    copy.enqueue(99);

    copy = original;

    REQUIRE(copy.size() == original.size());
    REQUIRE(copy.capacity() == original.capacity());
    REQUIRE(copy.head() == 10);
    REQUIRE(copy.tail() == 30);

    copy.dequeue();
    copy.enqueue(40);

    REQUIRE(copy.head() == 20);
    REQUIRE(copy.tail() == 40);
    REQUIRE(original.head() == 10);
    REQUIRE(original.tail() == 30);
}

TEST_CASE("Queue copy assignment handles self-assignment") {
    dsa::data_structures::Queue queue(5);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    queue = queue;

    REQUIRE(queue.size() == 3);
    REQUIRE(queue.capacity() == 5);
    REQUIRE(queue.head() == 10);
    REQUIRE(queue.tail() == 30);
}

TEST_CASE("Queue move constructor transfers ownership") {
    dsa::data_structures::Queue original(5);

    original.enqueue(10);
    original.enqueue(20);
    original.enqueue(30);

    dsa::data_structures::Queue moved(std::move(original));

    REQUIRE(moved.size() == 3);
    REQUIRE(moved.capacity() == 5);
    REQUIRE(moved.head() == 10);
    REQUIRE(moved.tail() == 30);
}

TEST_CASE("Queue move assignment transfers ownership") {
    dsa::data_structures::Queue original(5);

    original.enqueue(10);
    original.enqueue(20);
    original.enqueue(30);

    dsa::data_structures::Queue moved(4);
    moved.enqueue(99);

    moved = std::move(original);

    REQUIRE(moved.size() == 3);
    REQUIRE(moved.capacity() == 5);
    REQUIRE(moved.head() == 10);
    REQUIRE(moved.tail() == 30);
}

TEST_CASE("Queue move assignment handles self-move-assignment") {
    dsa::data_structures::Queue queue(5);

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);

    queue = std::move(queue);

    REQUIRE(queue.size() == 3);
    REQUIRE(queue.capacity() == 5);
    REQUIRE(queue.head() == 10);
    REQUIRE(queue.tail() == 30);
}